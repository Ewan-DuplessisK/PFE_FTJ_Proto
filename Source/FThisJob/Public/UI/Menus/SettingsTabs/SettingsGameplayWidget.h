// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SettingsTabBase.h"
#include "SettingsGameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USettingsGameplayWidget : public USettingsTabBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SetupSettingsValues(class USettingsSave* SettingSave) override;

protected:
	UPROPERTY(meta=(BindWidget))
	class USliderSettings* VerticalSensibilitySlider;
	UPROPERTY(meta=(BindWidget))
	class USliderSettings* HorizontalSensibilitySlider;

	UFUNCTION()
	void OnVerticalSensitivitySliderValueChanged(float Value);
	UFUNCTION()
	void OnHorizontalSensitivitySliderValueChanged(float Value);
};
