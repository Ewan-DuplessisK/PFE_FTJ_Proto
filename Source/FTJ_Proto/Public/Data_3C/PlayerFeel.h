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
	float Gravity = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Speed")
	float WalkSpeed = 700.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Speed")
	float RunSpeed = 900.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Damping")
	float LinearDamping = 0.01f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Damping")
	float AngularDamping = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Feel | Invincible")
	float Invincibility_Time = 2.0f;
};
