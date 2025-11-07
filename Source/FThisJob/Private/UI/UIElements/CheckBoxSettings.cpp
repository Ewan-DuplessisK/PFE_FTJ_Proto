// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/CheckBoxSettings.h"

#include "Components/RichTextBlock.h"

void UCheckBoxSettings::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensure(RichTextBlock != nullptr))
	{
		RichTextBlock->SetText(Text);
	}
}
