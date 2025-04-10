// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AimAssistFeel.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTJ_PROTO_API FUAimAssistFeel
{
	GENERATED_BODY()
	
	// Variables
	// Aim
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SearchRadius = 80.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartOffset = 75.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AssistRange = 2000.0f;
	// Radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeadshotRadius = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseShotRadius = 80.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BendShotRadius = 160.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MagneticRadius = 200.0f;
	// Debug
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDebugActive = true;
	// Factor
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeakFactor = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseFactor = 1.75f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SimpleFactor = -1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BendFactor = 1.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MagneticFactor = 1.2f;
};
