// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <CommonInputSubsystem.h>
#include "UI/BaseHUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API AMainMenuHUD : public ABaseHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleInputMethodChanged(ECommonInputType NewInputType) const;

	virtual USettingsMenuWidget* GetSettingsMenuWidget() const override;

	virtual UBaseMenuWidget* GetPreviousWidget() override;


};
