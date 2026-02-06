// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/SettingsTabs/SettingsTabBase.h"

#include "Components/VerticalBox.h"

void USettingsTabBase::SetupSettingsValues(class USettingsSave* SettingSave)
{
}

void USettingsTabBase::NativeOnActivated()
{
	Super::NativeOnActivated();

	UWidget* WidgetToFocus = VerticalBox->GetChildAt(0);
	if (WidgetToFocus)
	{
		WidgetToFocus->SetFocus();
	}
}

void USettingsTabBase::NativeConstruct()
{
	Super::NativeConstruct();

}

class UVerticalBox* USettingsTabBase::GetVerticalBox() const
{
	return VerticalBox;
}
