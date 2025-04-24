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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | FOV")
	float FOVBase = 90.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | FOV")
	float FOVTarget = 95.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | FOV")
	float FOVInterpSpeed = 50.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | FOV")
	float FOVSwitchSpeed = 0.01f;
	// Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | Base")
	bool bInvertCam = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | Base")
	float HorizontalCamSpeed = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | Base")
	float VerticalCamSpeed = 0.45f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | Base")
	float ViewPitchMin = -70.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | Base")
	float ViewPitchMax = 65.0f;
	// Tilt
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | Tilt")
	float TiltRecoverySpeed = 8.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | Tilt")
	float TiltClamp = 0.05f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cam | Tilt")
	float TiltMax = 1.75f;
};
