// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerFeel.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTJ_PROTO_API FUPlayerFeel
{
	GENERATED_BODY()
	
	// Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel")
	float Gravity = 1.75f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Speed")
	float WalkSpeed = 700.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Speed")
	float RunSpeed = 1900.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Damping")
	float LinearDamping = 0.01f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Damping")
	float AngularDamping = 0.0f;
	
	// Dash
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Dash", meta=(tooltip="rate of the FOV switch for dash"))
	float dashRate = 5.15f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Dash", meta=(tooltip="How far will the Dash go"))
	float dashDistance = 747.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Dash", meta=(tooltip="DO NOT TOUCH, Speed = Rate x Distance"))
	float dashSpeed = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat Feel|Dash", meta=(tooltip="Amount of time before the player can Dash again"))
	float delayBetweenTwoDash = 0.95f;
};
