// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
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
	class AGame_Character* Character = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Movement")
	class UInputAction* InputActionMove;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Look")
	class UInputAction* InputActionLook;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Kick");
	class UInputAction* InputActionKick;


	void MovePlayer(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);

	void HeadTilt(float DeltaTime);
	void Rota180();

	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity", meta = (ToolTip = "Change X axis sensitivity.", ClampMin = "0.1",ClampMax="3.0"))
	float InputSensitivityX = 1.f;
	UPROPERTY(EditDefaultsOnly, Category = "Sensitivity", meta = (ToolTip = "Change Y axis sensitivity.", ClampMin = "0.1", ClampMax = "3.0"))
	float InputSensitivityY = 1.f;


	class UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = nullptr;
	class UEnhancedInputUserSettings* EnhancedInputUserSettings = nullptr;
	
public:
	virtual void AddPitchInput(float Value);
	virtual void AddYawInput(float Value);

	float GetInputSensitivityX() const;
	float GetInputSensitivityY() const;

	void SetInputSensitivityX(float InSensitivity);
	void SetInputSensitivityY(float InSensitivity);

protected:
	bool bCan180Rota = true;
	FRotator TempRota = {0, 0, 0};
	
	
	float Tilt = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUCameraFeel CameraFeel;
};
