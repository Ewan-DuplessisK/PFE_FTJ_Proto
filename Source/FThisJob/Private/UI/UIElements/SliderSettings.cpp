// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/SliderSettings.h"

#include "CommonTextBlock.h"
#include "Components/RichTextBlock.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BaseHUD.h"

class USlider* USliderSettings::GetSlider() const
{
	return Slider;
}

class UCommonTextBlock* USliderSettings::GetValueCommonTextBlock() const
{
	return ValueCommonTextBlock;
}

void USliderSettings::NativeConstruct()
{
	Super::NativeConstruct();

	HUD = Cast<ABaseHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	if (ensure(CommonTextBlock))
	{
		CommonTextBlock->SetText(Text);
		CommonTextBlock->SetStyle(NormalTextStyle);
	}

	if (!ensure(Slider))
	{
		return;
	}

	Slider->SetMaxValue(SliderMax);
	Slider->SetMinValue(SliderMin);
	Slider->SetStepSize(SliderStepSize);

	check(ValueCommonTextBlock);
	ValueCommonTextBlock->SetStyle(NormalTextStyle);

	SetNumberSlider(Slider->GetValue());

	Slider->IsFocusable = false;
	Slider->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void USliderSettings::NativeOnHovered()
{
	bEnabled = true;

	ValueCommonTextBlock->SetStyle(HoveredTextStyle);
	CommonTextBlock->SetStyle(HoveredTextStyle);

	FLinearColor HoverColor = FLinearColor(0.745f,0.565f,0.054f,1.0f);
	Slider->SetSliderHandleColor(HoverColor);

	Super::NativeOnHovered();
}

void USliderSettings::NativeOnUnhovered()
{
	bEnabled = false;

	ValueCommonTextBlock->SetStyle(NormalTextStyle);
	CommonTextBlock->SetStyle(NormalTextStyle);
	
	Slider->SetSliderHandleColor(FLinearColor::White);

	Super::NativeOnUnhovered();
}

FReply USliderSettings::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Gamepad_DPad_Left)
	{
		Increment(-SliderStepSize);
	}

	if (InKeyEvent.GetKey() == EKeys::Gamepad_DPad_Right)
	{
		Increment(SliderStepSize);
	}
	
	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

FReply USliderSettings::NativeOnAnalogValueChanged(const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent)
{
	const float CurrentCall = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	constexpr float JitterTime = 0.2f;
	if (CurrentCall - LastCall < JitterTime)
	{
		return FReply::Unhandled();
	}

	if (InAnalogEvent.GetKey() == EKeys::Gamepad_LeftX)
	{
		constexpr float DeadZone = 0.4f;
		if (InAnalogEvent.GetAnalogValue() > DeadZone)
		{
			Increment(SliderStepSize);
			LastCall = CurrentCall;
		}
		else if (InAnalogEvent.GetAnalogValue() < -DeadZone)
		{
			Increment(-SliderStepSize);
			LastCall = CurrentCall;
		}
	}
	
	return Super::NativeOnAnalogValueChanged(InGeometry, InAnalogEvent);
}

void USliderSettings::SetNumberSlider(float Value) const
{
	Slider->SetValue(Value);

	FNumberFormattingOptions NumberFormat;
	NumberFormat.MinimumFractionalDigits = 0;

	if (FMath::IsNearlyEqual(Value, FMath::RoundToFloat(Value)))
	{
		NumberFormat.MaximumFractionalDigits = 0;
	}
	else
	{
		NumberFormat.MaximumFractionalDigits = 2;
	}

	check(ValueCommonTextBlock)
	ValueCommonTextBlock->SetText(
		FText::AsNumber(Value, &NumberFormat));
}

void USliderSettings::Increment(float StepAmount)
{
	if (!bEnabled)
	{
		return;
	}

	check(Slider)
	float Current = Slider->GetValue();
	Current += StepAmount;
	Current = FMath::Clamp(Current, SliderMin, SliderMax);
	SetNumberSlider(Current);
}
