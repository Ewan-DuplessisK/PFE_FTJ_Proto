// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFeel.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTHISJOB_API FUPlayerFeel
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
	float LinearDamping = 0.01f; // 0.01
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Damping")
	float AngularDamping = 0.0f; // cero
	
	// Target Lock
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Target Lock")
	float TargetLockLength = 650.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Target Lock")
	float TargetLockRadius = 75.0f;
};
