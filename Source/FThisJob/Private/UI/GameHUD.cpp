// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"

#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter_Base.h"
#include "Player_Controller.h"
#include "UI/Menus/BaseMenuWidget.h"
#include "UI/Menus/SettingsMenuWidget.h"
#include "UI/UIElements/MainMenuButton.h"

class UInputMappingContext* AGameHUD::GetGameplayMappingContext()
{
	return Super::GetGameplayMappingContext();
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayer_Controller* Player_Controller = Cast<APlayer_Controller>(GetOwningPlayerController());
	check(Player_Controller);
	
	if (ensure(PreviousWidgetClass) && ensure(Player_Controller))
	{
		PreviousWidgetInstance = CreateWidget<UBaseMenuWidget>(Player_Controller, PreviousWidgetClass);
	}
	if (ensure(SettingsMenuWidgetClass) && ensure(Player_Controller))
	{
		SettingsMenuWidgetInstance = CreateWidget<USettingsMenuWidget>(Player_Controller, SettingsMenuWidgetClass);
	}
}

UBaseMenuWidget* AGameHUD::GetPreviousWidget()
{
	check(PreviousWidgetInstance);
	return PreviousWidgetInstance;
}

USettingsMenuWidget* AGameHUD::GetSettingsMenuWidget() const
{
	check(SettingsMenuWidgetInstance);
	return SettingsMenuWidgetInstance;
}

void AGameHUD::PauseGame() 
{
	APlayerController* PlayerController = Cast<APlayerController>(GetOwningPlayerController());
	check(PlayerController);

	if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (APlayer_Controller* MyPlayer = Cast<APlayer_Controller>(PlayerController))
			{
				UInputMappingContext* GameplayIMC = MyPlayer->GetInputMappingContext();

				if (GameplayIMC)
				{
					SavedPlayerIMC = GameplayIMC;
					Subsystem->RemoveMappingContext(GameplayIMC);
				}
			}

			if (GetSettingsMenuWidget() && GetSettingsMenuWidget()->GetInputMappingContext())
			{
				UInputMappingContext* MenuIMC = GetSettingsMenuWidget()->GetInputMappingContext();
				Subsystem->AddMappingContext(MenuIMC, 100);
			}
		}
	}

	GetSettingsMenuWidget()->SetupInputComponent();
	
	if (PreviousWidgetInstance)
	{
		PreviousWidgetInstance->AddToViewport();
		PreviousWidgetInstance->GetFocusedButton()->SetFocus();
	}
}

void AGameHUD::ResumeGame() 
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (!PlayerController) return;

	if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (GetSettingsMenuWidget() && GetSettingsMenuWidget()->GetInputMappingContext())
			{
				UInputMappingContext* MenuIMC = GetSettingsMenuWidget()->GetInputMappingContext();
				Subsystem->RemoveMappingContext(MenuIMC);
			}

			if (SavedPlayerIMC)
			{
				Subsystem->AddMappingContext(SavedPlayerIMC, 0);

				SavedPlayerIMC = nullptr;
			}
		}
	}
	
	if (PreviousWidgetInstance)
	{
		PreviousWidgetInstance->RemoveFromParent();
	}
}
