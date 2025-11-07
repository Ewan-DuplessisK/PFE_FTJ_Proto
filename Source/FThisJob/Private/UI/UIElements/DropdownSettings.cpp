// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/DropdownSettings.h"

#include "Components/ComboBoxString.h"
#include "Components/RichTextBlock.h"

void UDropdownSettings::NativeConstruct()
{
	Super::NativeConstruct();

	for (FString Value : DropdownValues)
	{
		ComboBox->AddOption(Value);
	}
	
	if (ensure(RichTextBlock != nullptr))
	{
		RichTextBlock->SetText(Text);
	}
	
}
