// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/SettingsTabs/SettingsTabBase.h"

void USettingsTabBase::SetupSettingsValues(class USettingsSave* SettingSave)
{
}

void USettingsTabBase::NativeConstruct()
{
	Super::NativeConstruct();
}

class UVerticalBox* USettingsTabBase::GetVerticalBox() const
{
	return VerticalBox;
}
