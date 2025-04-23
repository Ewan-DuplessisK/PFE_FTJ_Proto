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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Trace")
	float SearchRadius = 80.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Trace")
	float StartOffset = 75.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Trace")
	float AssistRange = 2000.0f;
	// Radius
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Radiuses")
	float HeadshotRadius = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Radiuses")
	float BaseShotRadius = 80.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Radiuses")
	float BendShotRadius = 160.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Radiuses")
	float MagneticRadius = 200.0f;
	// Debug
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Debug")
	bool bIsDebugActive = true;
	// Factor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Factors")
	float WeakFactor = 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Factors")
	float BaseFactor = 1.75f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Factors")
	float SimpleFactor = -1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Factors")
	float BendFactor = 1.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Feel | Factors")
	float MagneticFactor = 1.2f;
};
