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
	// Dash
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Dash")
	float dashDistance = 25.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Dash")
	float delayBetweenTwoDash = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Dash")
	float dashVelocity = 250.0f;
};
