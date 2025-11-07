// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseHUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API AGameHUD : public ABaseHUD
{
	GENERATED_BODY()
public:
	virtual class UInputMappingContext* GetGameplayMappingContext() override;

protected:
	virtual void BeginPlay() override;
	
	virtual UBaseMenuWidget* GetPreviousWidget() override;
	
	virtual USettingsMenuWidget* GetSettingsMenuWidget() const override;

public:
	UFUNCTION()
	void PauseGame();

	UFUNCTION()
	void ResumeGame();

protected:
	UPROPERTY(EditDefaultsOnly, Category="GameHUD|Enhanced Inputs")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY()
	UInputMappingContext* SavedPlayerIMC = nullptr;
};
