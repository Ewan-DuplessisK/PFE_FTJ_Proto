// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/SettingsTabs/SettingsGameplayWidget.h"

#include "BaseGameInstance.h"
#include "Components/Slider.h"
#include "UI/SettingsSave.h"
#include "UI/UIElements/SliderSettings.h"

void USettingsGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	check(GI);
	USettingsSave* SettingsSave = GI->GetSettingsSave();
	check(SettingsSave);

	check(VerticalSensibilitySlider);
	VerticalSensibilitySlider->SetNumberSlider(SettingsSave->GetVerticalSensitivity());
	VerticalSensibilitySlider->GetSlider()->OnValueChanged.AddDynamic(this, &USettingsGameplayWidget::OnVerticalSensitivitySliderValueChanged);

	check(HorizontalSensibilitySlider);
	HorizontalSensibilitySlider->SetNumberSlider(SettingsSave->GetHorizontalSensitivity());
	HorizontalSensibilitySlider->GetSlider()->OnValueChanged.AddDynamic(this, &USettingsGameplayWidget::OnHorizontalSensitivitySliderValueChanged);
}

void USettingsGameplayWidget::SetupSettingsValues(class USettingsSave* SettingSave)
{
	VerticalSensibilitySlider->GetSlider()->SetValue(SettingSave->GetVerticalSensitivity());
	HorizontalSensibilitySlider->GetSlider()->SetValue(SettingSave->GetHorizontalSensitivity());
}

void USettingsGameplayWidget::OnVerticalSensitivitySliderValueChanged(float Value)
{
	UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	check(GI);

	USettingsSave* SettingsSave = GI->GetSettingsSave();
	check(SettingsSave);

	SettingsSave->SetVerticalSensitivity(Value);
}

void USettingsGameplayWidget::OnHorizontalSensitivitySliderValueChanged(float Value)
{
	UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	check(GI);

	USettingsSave* SettingsSave = GI->GetSettingsSave();
	check(SettingsSave);

	SettingsSave->SetHorizontalSensitivity(Value);
}
