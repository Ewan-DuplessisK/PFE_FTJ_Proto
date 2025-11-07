// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/SliderSettings.h"
#include "Components/RichTextBlock.h"
#include "Components/Slider.h"

void USliderSettings::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensure(RichTextBlock != nullptr))
	{
		RichTextBlock->SetText(Text);
	}

	if (ensure(Slider != nullptr))
	{
		return;
	}
	
	Slider->SetMaxValue(SliderMax);
	Slider->SetMinValue(SliderMin);
	Slider->SetStepSize(SliderStepSize);
	Slider->SetValue(SliderTempDefaultValue);

	if (ensure(ValueRichTextBlock != nullptr))
	{
		FNumberFormattingOptions NumberFormat;
		NumberFormat.MinimumFractionalDigits = 2;
		NumberFormat.MaximumFractionalDigits = 2;

		ValueRichTextBlock->SetText(FText::AsNumber(SliderTempDefaultValue, &NumberFormat));
	}
}
