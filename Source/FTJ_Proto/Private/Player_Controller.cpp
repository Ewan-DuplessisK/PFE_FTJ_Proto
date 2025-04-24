// Fill out your copyright notice in the Description page of Project Settings.


#include "FTJ_Proto/Public/Player_Controller.h"

#include "Blueprint/UserWidget.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "FTJ_Proto/Public/Game_Character.h"


#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

	EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &APlayer_Controller::MovePlayer);
	EnhancedInputComponent->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &APlayer_Controller::Look);

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
	PlayerCharacterRef = Cast<AGame_Character>(InPawn);
}

void APlayer_Controller::BeginPlay()
{
	Super::BeginPlay();
	
	// Camera Clamp
	APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	cameraManager->ViewPitchMin = CameraFeel.ViewPitchMin;
	cameraManager->ViewPitchMax = CameraFeel.ViewPitchMax;
	///
	
	InitializeVarsWithCameraFeelStruct();
	
	// Timer for FOV Switch (don't add anything after this)
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &APlayer_Controller::FOVChangeSpeed, CameraFeel.FOVSwitchSpeed, true);
}

void APlayer_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//HeadTilt(DeltaSeconds);
}

void APlayer_Controller::MovePlayer(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Move Player"));
	if (!PlayerCharacterRef) return;

	const FVector2D MoveValue = Value.Get<FVector2D>();

	if (MoveValue.X != 0.f)
	{
		FVector forwardVec = UKismetMathLibrary::GetForwardVector(GetControlRotation());
		PlayerCharacterRef->AddMovementInput(FlattenZAxis(forwardVec), MoveValue.X);
	}
	if (MoveValue.Y != 0.f)
	{
		PlayerCharacterRef->AddMovementInput(PlayerCharacterRef->GetActorRightVector(), MoveValue.Y);
	}

	// Tilt Set for Move
	Tilt = ((CameraFeel.TiltRecoverySpeed * 0.5f) * MoveValue.X) + Tilt;
}

void APlayer_Controller::Look(const FInputActionValue& Value)
{
	if (!PlayerCharacterRef) return;
	const FVector2D MoveValue = Value.Get<FVector2D>();
	
	if (MoveValue.Y != 0.f) 
	{
		if(CameraFeel.bInvertCam)
     	{
     		PlayerCharacterRef->AddControllerPitchInput(MoveValue.Y * CameraFeel.VerticalCamSpeed);
     	}
		else
		{
			PlayerCharacterRef->AddControllerPitchInput(-(MoveValue.Y * CameraFeel.VerticalCamSpeed));
		}
	}

	if (MoveValue.X != 0.f)
	{
		PlayerCharacterRef->AddControllerYawInput(MoveValue.X * CameraFeel.HorizontalCamSpeed);
	}

	// Tilt set for Look
	if(MoveValue.X < -CameraFeel.TiltClamp || MoveValue.X > CameraFeel.TiltClamp)
	{
		Tilt = (Tilt * TiltLookFactor) + MoveValue.X;
	}
	else
	{
		Tilt = 0.0f;
	}
}

void APlayer_Controller::HeadTilt(float DeltaTime) // TODO: remove from PC & add to Weapon 
{
	// Tilt Calc
	Tilt = Tilt - (Tilt * CameraFeel.TiltRecoverySpeed * DeltaTime);
	
	if(PlayerCharacterRef)
	{
		// Tilt Clamp
		if (Tilt < 0.0f)
		{
			Tilt = FMath::Clamp(Tilt, (CameraFeel.TiltMax * -1.0f), CameraFeel.TiltClamp);
		}
		else
		{
			Tilt = FMath::Clamp(Tilt, CameraFeel.TiltClamp, CameraFeel.TiltMax);
		}
		
		PlayerCharacterRef->FirstPersonCameraComponent->SetWorldRotation(GetControlRotation());
		// Tilt Set
		FRotator DeltaRotation = {0.0f, 0.0f, Tilt};
		PlayerCharacterRef->FirstPersonCameraComponent->AddRelativeRotation(DeltaRotation);
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
	InputSensitivityX=InSensitivity;
}

void APlayer_Controller::SetInputSensitivityY(float InSensitivity)
{
	InputSensitivityY=InSensitivity;
}

FVector APlayer_Controller::FlattenZAxis(FVector inVec)
{
	inVec.Z = 0.0f;
	inVec.Normalize(0.0001);
	return inVec;
}

void APlayer_Controller::InitializeVarsWithCameraFeelStruct() // Set FOV From Player Controller
{
	PlayerCharacterRef->FirstPersonCameraComponent->SetFieldOfView(CameraFeel.FOVBase);
}

void APlayer_Controller::FOVChangeSpeed()
{
	FVector charaVel = PlayerCharacterRef->GetVelocity();
	charaVel.Normalize(0.0001);
	ForwardAlpha = FVector::DotProduct(charaVel, PlayerCharacterRef->GetActorForwardVector());
	if(ForwardAlpha >= 0.0f)
	{
		float newFOV =FMath::FInterpConstantTo
		(
			PlayerCharacterRef->FirstPersonCameraComponent->FieldOfView, 
			FMath::Lerp(CameraFeel.FOVBase,CameraFeel.FOVTarget, ForwardAlpha), 
			GetWorld()->GetDeltaSeconds(), 
			
			CameraFeel.FOVInterpSpeed
		);
		
		PlayerCharacterRef->FirstPersonCameraComponent->SetFieldOfView(newFOV);
	}

	UE_LOG(LogTemp, Log, TEXT("FOV Timer"));
}
