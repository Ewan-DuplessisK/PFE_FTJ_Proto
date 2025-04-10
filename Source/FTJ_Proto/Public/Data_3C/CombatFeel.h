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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector KickForce = {3000.0f, 0.0f, 150.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KickLength = 200.0f;
	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebugActive = true;
};
