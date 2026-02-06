// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Player_Controller.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class FTHISJOB_API APlayer_Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;
	virtual void SetPawn(APawn* InPawn) override;
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	// Refs
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Refs")
	class APlayerCharacter_Base* PlayerCharacterRef = nullptr;
	
	UPROPERTY()
	class AGameHUD* GameHUD = nullptr;
	
protected:
	// Mapping
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput")
	class UInputMappingContext* InputMapping;
	// Inputs
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Movement")\
	class UInputAction* InputAction_Move;
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Look")
	class UInputAction* InputAction_Look;
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Kick")
	class UInputAction* InputAction_Kick;
	UPROPERTY(EditDefaultsOnly, Category="EnhancedInput|Dash")
	class UInputAction* InputAction_Dash;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Pause")
	class UInputAction* InputAction_Pause;
	
	// Enhanced Input Sys
	class UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = nullptr;
	class UEnhancedInputUserSettings* EnhancedInputUserSettings = nullptr;
	
	// Actions
	void MovePlayer(const struct FInputActionValue& value);
	void Look(const struct FInputActionValue& value);
	
	void PauseGame(const struct FInputActionValue& value);
	
	// Cam Sensitivity
	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity", meta = (ToolTip = "Change X axis sensitivity.", ClampMin = "0.1",ClampMax="3.0"))
	float InputSensitivityX = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity", meta = (ToolTip = "Change Y axis sensitivity.", ClampMin = "0.1", ClampMax = "3.0"))
	float InputSensitivityY = 1.0f;
	
public:
	// Cam Look
	virtual void AddPitchInput(float Value);
	virtual void AddYawInput(float Value);
	
	float GetInputSensitivityX() const;
	float GetInputSensitivityY() const;
	
	void SetInputSensitivityX(float InSensitivity);
	void SetInputSensitivityY(float InSensitivity);
	
protected:
	// FOV
	float forwardAlpha = 0.0f;
	
	// For smooth look up/down
	static FVector FlattenZAxis(FVector inVec);
	
public:
	void OnKickTriggered();
	
	// Player Movement Stop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ToolTip = "boolean to stop player movement"))
	bool canPlayerMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock- On", meta = (ToolTip = "boolean to stop player looking when target is locked"))
	bool TargetLocked = false;
	
	
	UFUNCTION()
	UInputMappingContext* GetInputMappingContext() const;
};
