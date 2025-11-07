// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menus/BaseMenuWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UPauseMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()
	
	virtual UMainMenuButton* GetFocusedButton() const override;

	virtual void NativeConstruct() override;

	// Buttons Functions
	UFUNCTION()
	void OnResumeClicked() const;


	virtual void OnSettingsClicked() override;

	virtual void OnChangeLevelClicked() override;
	
	virtual void OnQuitClicked() override;

	// Widgets Buttons
	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* ResumeButton;
};
