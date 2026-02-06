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

	virtual UVerticalBox* GetMenuVerticalBox() const override;

	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void NativeOnActivated() override;

	// Buttons Functions
	UFUNCTION()
	void OnResumeClicked() const;
	
	virtual void OnSettingsClicked() override;

	virtual void OnChangeLevelClicked() override;
	
	virtual void OnQuitClicked() override;

	virtual void UnQuit() override;

	protected:
	UFUNCTION(BlueprintImplementableEvent)
	void TempQuitFunction();

	// Widgets Buttons
	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* ResumeButton;
	
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* MenuVerticalBox;

};
