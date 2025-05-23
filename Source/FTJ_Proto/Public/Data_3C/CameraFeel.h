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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|FOV")
	float FOVBase = 90.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|FOV")
	float FOVTarget = 90.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|FOV")
	float FOVInterpSpeed = 50.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|FOV")
	float FOVSwitchSpeed = 0.01f;
	// Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base")
	bool bInvertCam = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base", meta=(ClampMin=0.0, ClampMax=1.0))
	float HorizontalCamSpeed = 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base", meta=(ClampMin=0.0, ClampMax=1.0))
	float VerticalCamSpeed = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base")
	float ViewPitchMin = -70.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base")
	float ViewPitchMax = 25.0f;
	
	// Tilt
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Tilt")
	float TiltRecoverySpeed = 8.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Tilt")
	float TiltClamp = 0.05f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Tilt")
	float TiltMax = 1.75f;
	*/
};
