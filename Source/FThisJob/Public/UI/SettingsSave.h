// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SettingsSave.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsChanged);

UCLASS()
class FTHISJOB_API USettingsSave : public USaveGame
{
	GENERATED_BODY()
protected:
	// Runtime Values
	// Gameplay
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float HorizontalSensitivity;
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float VerticalSensitivity;
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	bool ControllerHapticFeedback;
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	bool CameraShake;
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	bool CameraBlur;

	//Graphics
	UPROPERTY(EditDefaultsOnly, Category = "Graphics")
	int32 ResolutionDropdownIndex;
	UPROPERTY(EditDefaultsOnly, Category = "Graphics")
	int32 DisplayDropdownIndex;

	//Audio
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	float MasterVolume;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Events")
	FOnSettingsChanged OnSettingsChanged;

	// Events

	UFUNCTION()
	void InitializeFromDefaults(class USettingsDataAsset* DefaultData);

	// Setters
	// Gameplay
	UFUNCTION()
	void SetHorizontalSensitivity(float Value);
	UFUNCTION()
	void SetVerticalSensitivity(float Value);
	UFUNCTION()
	void SetControllerHapticFeedback(bool bValue);

	//Graphics
	UFUNCTION()
	void SetResolutionDropdownIndex(int32 Index);
	UFUNCTION()
	void SetDisplayDropdownIndex(int32 Index);

	// Audio
	UFUNCTION()
	void SetMasterVolume(float Value);


	// Getters
	// Gameplay
	UFUNCTION()
	float GetHorizontalSensitivity() const;
	UFUNCTION()
	float GetVerticalSensitivity() const;
	UFUNCTION()
	bool GetControllerHapticFeedback() const;

	//Graphics
	UFUNCTION()
	int32 GetResolutionDropdownIndex() const;
	UFUNCTION()
	int32 GetDisplayDropdownIndex() const;

	// Audio
	UFUNCTION()
	float GetMasterVolume() const;
};
