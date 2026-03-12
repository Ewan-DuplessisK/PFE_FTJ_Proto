// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/BaseMenuWidget.h"

#include "CommonAnimatedSwitcher.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BaseHUD.h"
#include "UI/GameHUD.h"
#include "UI/Menus/SettingsMenuWidget.h"
#include "UI/Menus/SettingsTabs/SettingsTabBase.h"
#include "UI/UIElements/MainMenuButton.h"
#include "UI/UIElements/SwitcherTabSettings.h"

class UMainMenuButton* UBaseMenuWidget::GetFocusedButton() const
{
	return nullptr;
}

void UBaseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (ensure(PC))
	{
		PC->bEnableClickEvents = false;
		PC->bEnableTouchEvents = false;
	}
	
	check(YesQuitButton);
	YesQuitButton->OnClicked().AddUObject(this, &UBaseMenuWidget::Quit);

	check(CanvasPanel);
	CanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
	
}

class UVerticalBox* UBaseMenuWidget::GetMenuVerticalBox() const
{
	return nullptr;
}

void UBaseMenuWidget::OnChangeLevelClicked()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NewLevel);
}

void UBaseMenuWidget::OnSettingsClicked()
{
	OpenSettings();
}

void UBaseMenuWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);

	//OpenQuitPanel();
}

void UBaseMenuWidget::UnQuit()
{
	CanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
	
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ABaseHUD* HUD = Cast<ABaseHUD>(PC->GetHUD()))
		{
			HUD->GetPreviousWidget()->GetMenuVerticalBox()->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UBaseMenuWidget::OpenSettings()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ABaseHUD* HUD = Cast<ABaseHUD>(PC->GetHUD()))
		{
			if (USettingsMenuWidget* Settings = HUD->GetSettingsMenuWidget())
			{
				check(Settings);
				Settings->GetSwitcherTabSettings()->SetIndex(0, 0.02f);
			}
		}
	}

}

void UBaseMenuWidget::OpenQuitPanel()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ABaseHUD* HUD = Cast<ABaseHUD>(PC->GetHUD()))
		{
			HUD->GetPreviousWidget()->GetMenuVerticalBox()->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	CanvasPanel->SetVisibility(ESlateVisibility::Visible);
	YesQuitButton->SetFocus();
}
