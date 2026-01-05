// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/SettingsTabs/SettingsAudioWidget.h"

#include "BaseGameInstance.h"
#include "Components/Slider.h"
#include "UI/SettingsSave.h"
#include "UI/UIElements/SliderSettings.h"

void USettingsAudioWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(MasterSlider);

	UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	check(GI);
	USettingsSave* SettingsSave = GI->GetSettingsSave();
	check(SettingsSave);

	MasterSlider->SetNumberSlider(SettingsSave->GetMasterVolume());
	MasterSlider->GetSlider()->OnValueChanged.AddDynamic(
		this, &USettingsAudioWidget::OnMasterSliderValueChanged);
}

void USettingsAudioWidget::OnMasterSliderValueChanged(float Value)
{
	UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
	check(GI);

	USettingsSave* SettingsSave = GI->GetSettingsSave();
	check(SettingsSave);

	SettingsSave->SetMasterVolume(Value);
}
