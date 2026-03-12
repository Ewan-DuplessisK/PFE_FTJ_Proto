// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"

#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter_Base.h"
#include "Player_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Menus/BaseMenuWidget.h"
#include "UI/Menus/SettingsMenuWidget.h"
#include "UI/UIElements/MainMenuButton.h"



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
	
	Player_Controller->SetInputMode(FInputModeGameOnly());
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
	/*if (PreviousWidgetInstance)
	{
		PreviousWidgetInstance->AddToViewport(TOP_LEVEL);
		PreviousWidgetInstance->GetFocusedButton()->SetFocus();
	}*/

	PauseGameInBlueprint();

	UGameplayStatics::SetGamePaused(GetWorld(), true);
	GetOwningPlayerController()->SetInputMode(FInputModeUIOnly());
}

void AGameHUD::ResumeGame() 
{
	/*if (PreviousWidgetInstance)
	{
		PreviousWidgetInstance->RemoveFromParent();
	}*/

	ResumeGameInBlueprint();

	UGameplayStatics::SetGamePaused(GetWorld(), false);
	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
}
