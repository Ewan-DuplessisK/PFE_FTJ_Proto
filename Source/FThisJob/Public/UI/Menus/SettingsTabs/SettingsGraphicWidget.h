// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingsTabBase.h"
#include "SettingsGraphicWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USettingsGraphicWidget : public USettingsTabBase
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SetupSettingsValues(class USettingsSave* SettingSave) override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UCheckBoxSettings* CameraMotionBlurCheckBox;

	UFUNCTION()
	void OnMotionBlurChanged(bool bValue);
};
