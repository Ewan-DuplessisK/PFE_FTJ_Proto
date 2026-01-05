// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/CheckBoxSettings.h"

#include "CommonTextBlock.h"
#include "Components/RichTextBlock.h"

void UCheckBoxSettings::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensure(CommonTextBlock != nullptr))
	{
		CommonTextBlock->SetText(Text);
		CommonTextBlock->SetStyle(NormalTextStyle);
	}
}

void UCheckBoxSettings::NativeOnHovered()
{
	CommonTextBlock->SetStyle(HoveredTextStyle);
	
	Super::NativeOnHovered();
}

void UCheckBoxSettings::NativeOnUnhovered()
{
	CommonTextBlock->SetStyle(NormalTextStyle);

	Super::NativeOnUnhovered();
}

class UCheckBox* UCheckBoxSettings::GetCheckBox() const
{
	return CheckBox;
}
