// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UBaseMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	virtual class UMainMenuButton* GetFocusedButton() const;

	virtual void NativeConstruct() override;

protected:

	// Buttons Functions
	UFUNCTION()
	virtual void OnChangeLevelClicked();

	UFUNCTION()
	virtual void OnSettingsClicked() ;

	UFUNCTION()
	virtual void OnQuitClicked();

	
	// Widgets Button
	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* ChangeLevelButton;

	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* SettingsButton;
	
	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* QuitButton;


	// Variables for GD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menus", meta = (AllowedClasses="World"))
	TSoftObjectPtr<UWorld> NewLevel;

};
