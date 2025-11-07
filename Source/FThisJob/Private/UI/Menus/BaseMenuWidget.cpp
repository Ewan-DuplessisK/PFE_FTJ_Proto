// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/BaseMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UI/BaseHUD.h"
#include "UI/Menus/SettingsMenuWidget.h"
#include "UI/UIElements/MainMenuButton.h"

class UMainMenuButton* UBaseMenuWidget::GetFocusedButton() const
{
	return nullptr;
}

void UBaseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensure(PC))
	{
		PC->SetInputMode(InputMode);
		PC->SetShowMouseCursor(false);
		PC->bEnableClickEvents = false;
		PC->bEnableTouchEvents = false;
	}
	check(ChangeLevelButton);
	ChangeLevelButton->OnClicked().AddUObject(this, &UBaseMenuWidget::OnChangeLevelClicked);
	
	check(SettingsButton)
	SettingsButton->OnClicked().AddUObject(this, &UBaseMenuWidget::OnSettingsClicked);

	check(QuitButton);
	QuitButton->OnClicked().AddUObject(this, &UBaseMenuWidget::OnQuitClicked);	
	
}

void UBaseMenuWidget::OnChangeLevelClicked()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NewLevel);
}

void UBaseMenuWidget::OnSettingsClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ABaseHUD* HUD = Cast<ABaseHUD>(PC->GetHUD()))
		{
			if (USettingsMenuWidget* Settings = HUD->GetSettingsMenuWidget())
			{
				Settings->AddToViewport();
				Settings->SetupInputComponent();
				HUD->GetPreviousWidget()->SetIsFocusable(false);
			}
		}
	}
	
}

void UBaseMenuWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
