//Header

#include"UI/UIElements/SliderSettings.h"

#include"UI/BaseHUD.h"

#include"CommonTextBlock.h"
#include"Components/RichTextBlock.h"
#include"Components/Slider.h"
#include"Kismet/GameplayStatics.h"

//Private

//Protected

void USliderSettings::NativePreConstruct()
{
    Super::NativePreConstruct();
    if(ensure(CommonTextBlock))
    {
        CommonTextBlock->SetText(Text);
        CommonTextBlock->SetStyle(NormalTextStyle);
    }
    if(!ensure(Slider))
    {
        return;
    }
    Slider->SetMaxValue(SliderMax);
    Slider->SetMinValue(SliderMin);
    Slider->SetStepSize(SliderStepSize);
    SetNumberSlider(Slider->GetValue());
    Slider->OnValueChanged.AddUniqueDynamic(this , &USliderSettings::OnSliderValueChanged);
    Slider->OnMouseCaptureBegin.AddUniqueDynamic(this , &USliderSettings::OnSliderMouseCaptureBegin);
    Slider->OnMouseCaptureEnd.AddUniqueDynamic(this , &USliderSettings::OnSliderMouseCaptureEnd);
    SetDesiredFocusWidget(Slider);
    check(ValueCommonTextBlock);
    ValueCommonTextBlock->SetStyle(NormalTextStyle);
}

void USliderSettings::NativeConstruct()
{
    Super::NativeConstruct();
    HUD = Cast<ABaseHUD>(UGameplayStatics::GetPlayerController(GetWorld() , 0)->GetHUD());
}

void USliderSettings::NativeOnMouseEnter(const FGeometry& InGeometry , const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry , InMouseEvent);
    bEnabled = true;
    Slider->SetIsEnabled(true);
    ValueCommonTextBlock->SetStyle(HoveredTextStyle);
    CommonTextBlock->SetStyle(HoveredTextStyle);
    OnHoveredSound();
}

void USliderSettings::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
    bEnabled = false;
    Slider->SetIsEnabled(false);
    Slider->SetRenderOpacity(1.0f);
    ValueCommonTextBlock->SetStyle(NormalTextStyle);
    CommonTextBlock->SetStyle(NormalTextStyle);
}

//

void USliderSettings::OnSliderValueChanged(float Value)
{
    SetNumberSlider(Value);
}

void USliderSettings::OnSliderMouseCaptureBegin()
{
    auto Style{Slider->GetWidgetStyle()};
    Style.HoveredThumbImage.TintColor = FSlateColor{FLinearColor{1.0 , 0.666667 , 0.0}};
    Slider->SetWidgetStyle(Style);
}

void USliderSettings::OnSliderMouseCaptureEnd()
{
    auto Style{Slider->GetWidgetStyle()};
    Style.HoveredThumbImage.TintColor = FSlateColor{FLinearColor{1.0 , 0.81175 , 0.0}};
    Slider->SetWidgetStyle(Style);
}

//Public

USlider * USliderSettings::GetSlider() const
{
    return(Slider);
}

UCommonTextBlock * USliderSettings::GetValueCommonTextBlock() const
{
    return(ValueCommonTextBlock);
}

//

void USliderSettings::SetNumberSlider(float Value) const
{
    Slider->SetValue(Value);
    FNumberFormattingOptions NumberFormat;
    NumberFormat.MinimumFractionalDigits = 0;
    if(FMath::IsNearlyEqual(Value, FMath::RoundToFloat(Value)))
    {
        NumberFormat.MaximumFractionalDigits = 0;
    }
    else
    {
        NumberFormat.MaximumFractionalDigits = 2;
    }
    check(ValueCommonTextBlock)
    ValueCommonTextBlock->SetText(FText::AsNumber(Value , &NumberFormat));
}

void USliderSettings::Increment(float StepAmount)
{
    if(!bEnabled)
    {
        return;
    }
    check(Slider)
    float Current = Slider->GetValue();
    Current += StepAmount;
    Current = FMath::Clamp(Current, SliderMin, SliderMax);
    SetNumberSlider(Current);
}