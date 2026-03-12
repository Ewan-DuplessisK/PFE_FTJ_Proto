// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/SettingsTabs/SettingsGraphicWidget.h"

#include "BaseGameInstance.h"
#include "SceneViewExtension.h"
#include "Components/CheckBox.h"
#include "UI/SettingsSave.h"
#include "UI/UIElements/CheckBoxSettings.h"

void USettingsGraphicWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	check(GI);
	USettingsSave* SettingsSave = GI->GetSettingsSave();
	check(SettingsSave);

	check(CameraMotionBlurCheckBox);
	CameraMotionBlurCheckBox->GetCheckBox()->SetIsChecked(SettingsSave->GetCameraMotionBlur());
	CameraMotionBlurCheckBox->GetCheckBox()->OnCheckStateChanged.AddDynamic(
		this, &USettingsGraphicWidget::OnMotionBlurChanged);
}

void USettingsGraphicWidget::SetupSettingsValues(class USettingsSave* SettingSave)
{
	CameraMotionBlurCheckBox->GetCheckBox()->SetIsChecked(SettingSave->GetCameraMotionBlur());
	
	Super::SetupSettingsValues(SettingSave);
}

void USettingsGraphicWidget::OnMotionBlurChanged(bool bValue)
{
	UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	check(GI);

	USettingsSave* SettingsSave = GI->GetSettingsSave();
	check(SettingsSave);
	SettingsSave->SetCameraMotionBlur(bValue);
}
