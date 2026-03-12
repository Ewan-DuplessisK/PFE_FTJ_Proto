// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SettingsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USettingsDataAsset : public UDataAsset
{
	GENERATED_BODY()

	public:
    	//Gameplay 
    	UPROPERTY(EditDefaultsOnly, Category = "Gameplay",
    		meta = (ClampMin = "1.0", ClampMax = "5.0", DisplayPrecision = "2"))
    	float HorizontalSensitivity = 1.2f;
    
    	UPROPERTY(EditDefaultsOnly, Category = "Gameplay",
    		meta = (ClampMin = "1.0", ClampMax = "5.0", DisplayPrecision = "2"))
    	float VerticalSensitivity = 0.7f;
    
    	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
    	bool ControllerHapticFeedback = true;
    
    
    	// Graphics
    	UPROPERTY(EditDefaultsOnly, Category = "Graphics")
    	int32 DisplayIndex;
    
    	UPROPERTY(EditDefaultsOnly, Category = "Graphics")
    	int32 ResolutionIndex;

		UPROPERTY(EditDefaultsOnly, Category = "Graphics")
		bool CameraMotionBlur;
    
    
    
    	// Audio
    	UPROPERTY(EditDefaultsOnly, Category = "Audio"
    		, meta = (ClampMin = "0.", ClampMax = "100.0"))
    	float MasterVolume = 100.f;
    
    
    	//Accessibility
    	UPROPERTY(EditDefaultsOnly, Category = "Accessibility")
    	TArray<FString> Language;
    
    	UPROPERTY(EditDefaultsOnly, Category = "Accessibility"
    		, meta = (ClampMin = "0.", ClampMax = "100.0"))
    	float SubtitleBackgroundOpacity = 100.0f;
    
    	UPROPERTY(EditDefaultsOnly, Category = "Accessibility"
    		, meta = (ClampMin = "0.", ClampMax = "100.0"))
    	float SubtitleSize = 50.0f;
};
