// Fill out your copyright notice in the Description page of Project Settings.


#include "FTJ_Proto/Public/Player_Controller.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "FTJ_Proto/Public/Game_Character.h"
#include "UserSettings/EnhancedInputUserSettings.h"

void APlayer_Controller::SetupInputComponent(){
	Super::SetupInputComponent();

	EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!EnhancedInputSubsystem) {
		return;
	}
	EnhancedInputSubsystem->ClearAllMappings();
	EnhancedInputSubsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent) {
		return;
	}
	EnhancedInputComponent->ClearActionBindings();

	EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &APlayer_Controller::MovePlayer);
	EnhancedInputComponent->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &APlayer_Controller::Look);

	/*if((EnhancedInputUserSettings = EnhancedInputSubsystem->GetUserSettings())){
		EnhancedInputUserSettings->RegisterInputMappingContext(InputMapping);
	}*/
	
}

void APlayer_Controller::SetPawn(APawn* InPawn){
	if (Character)return;
	Super::SetPawn(InPawn);
	Character = Cast<AGame_Character>(InPawn);
}

void APlayer_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void APlayer_Controller::MovePlayer(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Move Player"));
	if (!Character)return;

	const FVector2D MoveValue = Value.Get<FVector2D>();

	if (MoveValue.Y != 0.f) {
		Character->AddMovementInput(Character->GetActorForwardVector(), MoveValue.Y);
	}

	if (MoveValue.X != 0.f) {
		Character->AddMovementInput(Character->GetActorRightVector(), MoveValue.X);
	}
}

void APlayer_Controller::Look(const FInputActionValue& Value)
{
	if (!Character)return;
	const FVector2D MoveValue = Value.Get<FVector2D>();
	if (MoveValue.Y != 0.f) {
		Character->AddControllerPitchInput(-MoveValue.Y);
	}

	if (MoveValue.X != 0.f) {
		Character->AddControllerYawInput(MoveValue.X);
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

