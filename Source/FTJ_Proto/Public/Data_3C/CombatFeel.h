// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombatFeel.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTJ_PROTO_API FUCombatFeel
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Kick")
	FVector KickForce = {3000.0f, 0.0f, 150.0f};
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Kick")
	float KickLength = 300.0f;
	// Debug
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Debug")
	bool bDebugActive = true;
	
	// Combo System
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Sys",  meta = (ToolTip = "This means each time we hit we will add X amount of points as a base."))
	float BaseComboPoints = 15.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Sys", meta = (ToolTip = "The speed at wich the combo bar decreases."))
	float ComboBarDecreasingSpeed = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Sys", meta = (ToolTip = "The base value for how much we will add to combo bar when hit an enemy."))
	float ComboBarIncreasingValue = 0.35f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Sys", meta = (ToolTip = "How much combo bar should decrease if we miss."))
	float MissDecreaseValue = 0.25f;
	// Combo Factors
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Sys", meta = (ToolTip = "Combo Multiplier for the Head."))
	float HeadComboFactor = 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Sys", meta = (ToolTip = "Combo Multiplier for the Body."))
	float BodyComboFactor = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Sys", meta = (ToolTip = "Combo Multiplier for the Arms."))
	float ArmsComboFactor = 0.45f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Sys", meta = (ToolTip = "Combo Multiplier for the Legs."))
	float LegsComboFactor = 0.65f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo Sys", meta = (ToolTip = "Combo Multiplier for the Kick."))
	float KickComboFactor = 0.25f;
};
