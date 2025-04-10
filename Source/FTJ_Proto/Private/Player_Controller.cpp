// Fill out your copyright notice in the Description page of Project Settings.


#include "FTJ_Proto/Public/Player_Controller.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "FTJ_Proto/Public/Game_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	EnhancedInputComponent->ClearActionBindings();

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
	if (Character) return;
	Super::SetPawn(InPawn);
	Character = Cast<AGame_Character>(InPawn);
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
	
	HeadTilt(DeltaSeconds);
}

// Timer
void APlayer_Controller::EndPlay(const EEndPlayReason::Type EndPlayReason) // If you ever want to stop the timer for some reason
{
	// It's important to keep the call chain on EndPlay or you may end up with serious bugs or crashes
	Super::EndPlay(EndPlayReason);
	
	// There's a chance your timer is still running when our Actor is destroyed, So we need to make sure we clear the timer on EndPlay just in case.
	// This is safe to call even if the timer handle's already been cleared.
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
}
/// 

void APlayer_Controller::MovePlayer(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Move Player"));
	if (!Character) return;

	const FVector2D MoveValue = Value.Get<FVector2D>();

	if (MoveValue.X != 0.f)
	{
		
		//Character->AddMovementInput(Character->GetActorForwardVector(), MoveValue.X);
		
		FVector forwardVec = UKismetMathLibrary::GetForwardVector(GetControlRotation());
		Character->AddMovementInput(FlattenZAxis(forwardVec), MoveValue.X);
	}
	if (MoveValue.Y != 0.f)
	{
		Character->AddMovementInput(Character->GetActorRightVector(), MoveValue.Y);
	}

	// Tilt Set for Move
	Tilt = ((CameraFeel.TiltRecoverySpeed * 0.5f) * MoveValue.X) + Tilt;
}

void APlayer_Controller::Look(const FInputActionValue& Value)
{
	if (!Character) return;
	const FVector2D MoveValue = Value.Get<FVector2D>();
	
	if (MoveValue.Y != 0.f) 
	{
		if(CameraFeel.bInvertCam)
     	{
     		Character->AddControllerPitchInput(MoveValue.Y * CameraFeel.VerticalCamSpeed);
     	}
		else
		{
			Character->AddControllerPitchInput(-(MoveValue.Y * CameraFeel.VerticalCamSpeed));
		}
	}

	if (MoveValue.X != 0.f)
	{
		Character->AddControllerYawInput(MoveValue.X * CameraFeel.HorizontalCamSpeed);
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

void APlayer_Controller::HeadTilt(float DeltaTime)
{
	// Tilt Calc
	Tilt = Tilt - (Tilt * CameraFeel.TiltRecoverySpeed * DeltaTime);
	
	if(Character)
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
		
		Character->FirstPersonCameraComponent->SetWorldRotation(GetControlRotation());
		// Tilt Set
		FRotator DeltaRotation = {0.0f, 0.0f, Tilt};
		Character->FirstPersonCameraComponent->AddRelativeRotation(DeltaRotation);
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
	Character->FirstPersonCameraComponent->SetFieldOfView(CameraFeel.FOVBase);
}

void APlayer_Controller::FOVChangeSpeed()
{
	FVector charaVel = Character->GetVelocity();
	charaVel.Normalize(0.0001);
	ForwardAlpha = FVector::DotProduct(charaVel, Character->GetActorForwardVector());
	if(ForwardAlpha >= 0.0f)
	{
		float newFOV =FMath::FInterpConstantTo
		(
			Character->FirstPersonCameraComponent->FieldOfView, 
			FMath::Lerp(CameraFeel.FOVBase,CameraFeel.FOVTarget, ForwardAlpha), 
			GetWorld()->GetDeltaSeconds(), 
			
			CameraFeel.FOVInterpSpeed
		);
		
		Character->FirstPersonCameraComponent->SetFieldOfView(newFOV);
	}

	UE_LOG(LogTemp, Log, TEXT("FOV Timer"));
}
