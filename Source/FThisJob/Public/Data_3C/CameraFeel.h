// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CameraFeel.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FTHISJOB_API FUCameraFeel
{
	GENERATED_BODY()
	
	// Variables
	// FOV
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|FOV")
	float FOVBase = 90.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|FOV")
	float FOVTarget = 95.0f;
	
	// Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base")
	bool bInvertCam = false; // flase
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base", meta=(ClampMin=0.0, ClampMax=1.0))
	float HorizontalCamSpeed = 1.94f; // 1.94
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base", meta=(ClampMin=0.0, ClampMax=1.0))
	float VerticalCamSpeed = 1.67f; // 1.67
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base")
	float ViewPitchMin = -74.0f; // -70.0
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Feel|Base")
	float ViewPitchMax = 33.0f; // 30.0
	
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
