// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Data_3C/CameraFeel.h"
#include "Player_Controller.generated.h"

/**
 * 
 */
UCLASS()
class FTJ_PROTO_API APlayer_Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;
	virtual void SetPawn(APawn* InPawn) override;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	// Timer
	// You should keep the timer handle in one of your properties
	FTimerHandle MyTimerHandle;
	///
	
public:
	// Refs
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class AGame_Character* PlayerCharacterRef = nullptr;
	
	// Struct Ref
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Refs")
	FUCameraFeel CameraFeel;
	
protected:
	// Inputs
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Movement")
	class UInputAction* InputActionMove;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Look")
	class UInputAction* InputActionLook;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Kick");
	class UInputAction* InputActionKick;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Dash");
	class UInputAction* InputActionDash;

	//
	void MovePlayer(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);

	void HeadTilt(float DeltaTime);
	
	//
	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity", meta = (ToolTip = "Change X axis sensitivity.", ClampMin = "0.1",ClampMax="3.0"))
	float InputSensitivityX = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity", meta = (ToolTip = "Change Y axis sensitivity.", ClampMin = "0.1", ClampMax = "3.0"))
	float InputSensitivityY = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tilt", meta = (ToolTip = "Tilt Multiplier for Look", ClampMin = "0.1", ClampMax = "2.5"))
	float TiltLookFactor = 1.25f;
	

	class UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = nullptr;
	class UEnhancedInputUserSettings* EnhancedInputUserSettings = nullptr;
	
public:
	// Camera/Look
	virtual void AddPitchInput(float Value);
	virtual void AddYawInput(float Value);

	float GetInputSensitivityX() const;
	float GetInputSensitivityY() const;

	void SetInputSensitivityX(float InSensitivity);
	void SetInputSensitivityY(float InSensitivity);
	
protected:
	
	// Tilt
	float Tilt = 0.0f;

	// FOV
	float ForwardAlpha = 0.0f;

	// For smooth look up/down
	static FVector FlattenZAxis(FVector inVec);
	
public:
	UFUNCTION(BlueprintCallable)
	void InitializeVarsWithCameraFeelStruct();
	
	void FOVChangeSpeed();
	void OnKickTriggered();
	
	// Debug Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs|Debug", meta = (ToolTip = "Class Reference to Debug Widget"))
	TSubclassOf<UUserWidget> wDebugWidget = nullptr;
	
	// Variable to hold the widget After Creating it.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs|Debug", meta = (ToolTip = "Widget Reference of the Debug Widget"))
	UUserWidget* MyDebugMenu = nullptr;

	
	// Variable to hold the widget After Creating it.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ToolTip = "boolean to stop player movement"))
	bool bCanPlayerMove = true;
};
