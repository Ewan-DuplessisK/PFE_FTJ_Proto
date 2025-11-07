// Fill out your copyright notice in the Description page of Project Settings.

#include "FThisJob/Public/Player_Controller.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "Camera/CameraComponent.h"

#include "FThisJob/Public/PlayerCharacter_Base.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/GameHUD.h"

#include "UserSettings/EnhancedInputUserSettings.h"

void APlayer_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!EnhancedInputSubsystem)
	{
		return;
	}
	EnhancedInputSubsystem->ClearAllMappings();
	EnhancedInputSubsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		return;
	}
	EnhancedInputComponent->BindAction(InputAction_Move, ETriggerEvent::Triggered, this, &APlayer_Controller::MovePlayer);
	EnhancedInputComponent->BindAction(InputAction_Look, ETriggerEvent::Triggered, this, &APlayer_Controller::Look);
	EnhancedInputComponent->BindAction(InputAction_Kick,ETriggerEvent::Triggered, this, &APlayer_Controller::OnKickTriggered);
	EnhancedInputComponent->BindAction(InputAction_Pause, ETriggerEvent::Triggered, this,&APlayer_Controller::PauseGame);
	
	/*
	if((EnhancedInputUserSettings = EnhancedInputSubsystem->GetUserSettings()))
	{
		EnhancedInputUserSettings->RegisterInputMappingContext(InputMapping);
	}
	*/
}

void APlayer_Controller::SetPawn(APawn* InPawn)
{
	if (PlayerCharacterRef) return;
	Super::SetPawn(InPawn);
	PlayerCharacterRef = Cast<APlayerCharacter_Base>(InPawn);
}

void APlayer_Controller::BeginPlay()
{	Super::BeginPlay();
	
	GameHUD = Cast<AGameHUD>(GetHUD());
	
	// Camera Clamp
	APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	cameraManager->ViewPitchMin = CameraFeel.ViewPitchMin;
	cameraManager->ViewPitchMax = CameraFeel.ViewPitchMax;
	///
	
	// Timer for FOV Switch (don't add anything after this)
	//GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &APlayer_Controller::FOVChangeSpeed, CameraFeel.FOVSwitchSpeed, true);
}
void APlayer_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void APlayer_Controller::MovePlayer(const FInputActionValue& Value)
{
	if(canPlayerMove)
	{
		if (!PlayerCharacterRef) return;
	
		const FVector2D MoveValue = Value.Get<FVector2D>();
	
		if (MoveValue.Y != 0.0f)
		{
			FVector forwardVec = UKismetMathLibrary::GetForwardVector(GetControlRotation());
			PlayerCharacterRef->AddMovementInput(FlattenZAxis(forwardVec), MoveValue.Y);
		}
		if (MoveValue.X != 0.0f)
		{
			PlayerCharacterRef->AddMovementInput(PlayerCharacterRef->GetActorRightVector(), MoveValue.X);
		}

		
		// Tilt Set for Move
		//Tilt = ((CameraFeel.TiltRecoverySpeed * 0.5f) * MoveValue.X) + Tilt;
	}
}

void APlayer_Controller::Look(const struct FInputActionValue& value)
{
	if(canPlayerMove && !TargetLocked)
	{
		if (!PlayerCharacterRef) return;
	
		const FVector2D MoveValue = value.Get<FVector2D>();
	
		if (MoveValue.X != 0.0f)
		{
			AddYawInput(MoveValue.X * CameraFeel.HorizontalCamSpeed);
		}
	
		if (MoveValue.Y != 0.0f) 
		{
			if(CameraFeel.bInvertCam)
			{
				AddPitchInput(-(MoveValue.Y * CameraFeel.VerticalCamSpeed));
			}
			else
			{
				AddPitchInput(MoveValue.Y * CameraFeel.VerticalCamSpeed);
			}
		
			PlayerCharacterRef->FirstPersonCameraComponent->SetRelativeRotation(FRotator(GetControlRotation().Pitch,0.0,0.0));
		}
		
		//PlayerCharacterRef->FirstPersonCameraComponent->SetWorldRotation(GetControlRotation());
		
		// Tilt set for Look
		/*
		if(MoveValue.X < -CameraFeel.TiltClamp || MoveValue.X > CameraFeel.TiltClamp)
		{
			Tilt = (Tilt * TiltLookFactor) + MoveValue.X;
		}
		else
		{
			Tilt = 0.0f;
		}
		*/
	}
}

void APlayer_Controller::PauseGame(const struct FInputActionValue& value)
{
	if (ensure(GameHUD != nullptr))
	{
		if (!IsPaused())
		{
			GameHUD->PauseGame();
		}
	}
}

void APlayer_Controller::AddPitchInput(float Value)
{
	float MultipliedValue = Value * InputSensitivityY;
	Super::AddPitchInput(MultipliedValue);
}

void APlayer_Controller::AddYawInput(float Value)
{
	float MultipliedValue = Value * InputSensitivityX;
	Super::AddYawInput(MultipliedValue);
}

float APlayer_Controller::GetInputSensitivityX() const
{
	return InputSensitivityX;
}

float APlayer_Controller::GetInputSensitivityY() const
{
	return InputSensitivityY;
}

void APlayer_Controller::SetInputSensitivityX(float InSensitivity)
{
	InputSensitivityX = InSensitivity;
}

void APlayer_Controller::SetInputSensitivityY(float InSensitivity)
{
	InputSensitivityY = InSensitivity;
}

FVector APlayer_Controller::FlattenZAxis(FVector inVec)
{
	inVec.Z = 0.0f;
	inVec.Normalize(0.0001);
	return inVec;
}

void APlayer_Controller::OnKickTriggered()
{
	
	if (IsValid(PlayerCharacterRef) && canPlayerMove)
	{
		PlayerCharacterRef->Kick();
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Kick Triggered"));
	}
}

UInputMappingContext* APlayer_Controller::GetInputMappingContext() const
{
	return InputMapping;
}
