// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseHUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
#define TOP_LEVEL 100000
UCLASS()
class FTHISJOB_API AGameHUD : public ABaseHUD
{
	GENERATED_BODY()
public:

protected:
	virtual void BeginPlay() override;
	
	virtual UBaseMenuWidget* GetPreviousWidget() override;
	
	virtual USettingsMenuWidget* GetSettingsMenuWidget() const override;

public:
	UFUNCTION()
	void PauseGame();

	UFUNCTION()
	void ResumeGame();
};
