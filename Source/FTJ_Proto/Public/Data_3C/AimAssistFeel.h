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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Trace")
	float SearchRadius = 80.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Trace")
	float StartOffset = 75.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Trace")
	float AssistRange = 2000.0f;
	// Radius
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Radiuses")
	float HeadshotRadius = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Radiuses")
	float BaseShotRadius = 80.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Radiuses")
	float BendShotRadius = 160.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Radiuses")
	float MagneticRadius = 200.0f;
	// Debug
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Debug")
	bool bIsDebugActive = false;
	// Factor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Factors", meta=(ClampMin=0.0, ClampMax=1.0))
	float WeakFactor = 0.2f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Factors", meta=(ClampMin=0.0, ClampMax=1.0))
	float BaseFactor = 0.75f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Factors", meta=(ClampMin=0.0, ClampMax=1.0))
	float SimpleFactor = 0.85f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Factors", meta=(ClampMin=0.0, ClampMax=1.0))
	float BendFactor = 0.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel|Factors", meta=(ClampMin=0.0, ClampMax=1.0))
	float MagneticFactor = 0.7f;
};
