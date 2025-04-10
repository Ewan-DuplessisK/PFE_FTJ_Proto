// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CameraFeel.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTJ_PROTO_API FUCameraFeel
{
	GENERATED_BODY()

	// Variables
	// FOV
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FOVBase = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FOVTarget = 95.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FOVInterpSpeed = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FOVSwitchSpeed = 0.01f;
	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInvertCam = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalCamSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticalCamSpeed = 0.45f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ViewPitchMin = -70.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ViewPitchMax = 65.0f;
	// Tilt
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TiltRecoverySpeed = 8.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TiltClamp = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TiltMax = 1.75f;
};
