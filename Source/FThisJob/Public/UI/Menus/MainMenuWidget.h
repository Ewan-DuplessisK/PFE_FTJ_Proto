// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMenuWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UMainMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual class UMainMenuButton* GetFocusedButton() const override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SwitchCameraPlay();
	
	UFUNCTION(BlueprintImplementableEvent)
	void SwitchCameraSettings();
	
	UFUNCTION(BlueprintImplementableEvent)
	void SwitchCameraQuit();

	UFUNCTION(BlueprintImplementableEvent)
	void SwitchCameraDefault();

	virtual void UnQuit() override;


protected:
	virtual void OnChangeLevelClicked() override;

	virtual void OnQuitClicked() override;

	virtual void OnSettingsClicked() override;


};
