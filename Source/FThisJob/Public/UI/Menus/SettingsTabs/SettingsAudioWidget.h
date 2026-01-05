// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SettingsTabBase.h"
#include "SettingsAudioWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USettingsAudioWidget : public USettingsTabBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USliderSettings* MasterSlider;

	UFUNCTION()
	void OnMasterSliderValueChanged(float Value);
};
