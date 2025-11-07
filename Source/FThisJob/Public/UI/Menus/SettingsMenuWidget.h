// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SettingsMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USettingsMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetupInputComponent();

	UFUNCTION()
	UInputMappingContext* GetInputMappingContext() const;
protected:
	UPROPERTY(meta = (BindWidget))
	class USwitcherTabSettings* SwitcherTabSettings;
	
	// Inputs
	UPROPERTY(EditDefaultsOnly,Blueprintable, Category = "Menus|Enhanced Input")
	class UInputMappingContext* MenusInputMappingContext;
	UPROPERTY(EditDefaultsOnly,Blueprintable, Category = "Menus|Enhanced Input")
	class UInputAction* InputActionToRightTab;
	UPROPERTY(EditDefaultsOnly, Category = "Menus|Enhanced Input")
	class UInputAction* InputActionToLeftTab;
	UPROPERTY(EditDefaultsOnly, Category = "Menus|Enhanced Input")
	class UInputAction* InputActionReturn;

	UFUNCTION()
	void ToRightTab(const struct FInputActionValue& Value);
	UFUNCTION()
	void ToLeftTab(const struct FInputActionValue& Value);
	UFUNCTION()
	void Return(const struct FInputActionValue& Value);
};
