// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseHUD.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
}

class UInputMappingContext* ABaseHUD::GetGameplayMappingContext()
{
	return nullptr;
}

class USettingsMenuWidget* ABaseHUD::GetSettingsMenuWidget() const
{
	return nullptr;
}

class UBaseMenuWidget* ABaseHUD::GetPreviousWidget()
{
	return nullptr;
}
