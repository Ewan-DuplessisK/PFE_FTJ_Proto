// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SettingsSave.h"

#include "Kismet/GameplayStatics.h"
#include "UI/SettingsDataAsset.h"

void USettingsSave::InitializeFromDefaults(class USettingsDataAsset* DefaultData)
{
	if (!ensure(DefaultData))
	{
		return;
	}
	HorizontalSensitivity = DefaultData->HorizontalSensitivity;
	VerticalSensitivity = DefaultData->VerticalSensitivity;
	MasterVolume = DefaultData->MasterVolume;
}

void USettingsSave::SetHorizontalSensitivity(float Value)
{
	HorizontalSensitivity = Value;
	OnSettingsChanged.Broadcast();
	UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetVerticalSensitivity(float Value)
{
	VerticalSensitivity = Value;
	OnSettingsChanged.Broadcast();
	UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetControllerHapticFeedback(bool bValue)
{
	ControllerHapticFeedback = bValue;
	OnSettingsChanged.Broadcast();
	UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetResolutionDropdownIndex(int32 Index)
{
	ResolutionDropdownIndex = Index;
	OnSettingsChanged.Broadcast();
	UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetDisplayDropdownIndex(int32 Index)
{
	DisplayDropdownIndex = Index;
	OnSettingsChanged.Broadcast();
	UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetMasterVolume(float Value)
{
	MasterVolume = Value;
	OnSettingsChanged.Broadcast();
	UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

float USettingsSave::GetHorizontalSensitivity() const
{
	return HorizontalSensitivity;
}

float USettingsSave::GetVerticalSensitivity() const
{
	return VerticalSensitivity;
}

bool USettingsSave::GetControllerHapticFeedback() const
{
	return ControllerHapticFeedback;
}

int32 USettingsSave::GetResolutionDropdownIndex() const
{
	return ResolutionDropdownIndex;
}

int32 USettingsSave::GetDisplayDropdownIndex() const
{
	return DisplayDropdownIndex;
}

float USettingsSave::GetMasterVolume() const
{
	return MasterVolume;
}
