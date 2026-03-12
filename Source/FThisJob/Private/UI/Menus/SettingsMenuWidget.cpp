// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/SettingsMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UI/UIElements/SwitcherTabSettings.h"
#include "UI/BaseHUD.h"
#include "UI/GameHUD.h"
#include "UI/MainMenuHUD.h"
#include "UI/Menus/BaseMenuWidget.h"
#include "UI/UIElements/MainMenuButton.h"

class USwitcherTabSettings* USettingsMenuWidget::GetSwitcherTabSettings() const
{
	return SwitcherTabSettings;
}

void USettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply USettingsMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right || InKeyEvent.GetKey() == EKeys::M)
	{
		const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AHUD* BaseHud = PC->GetHUD();
		if (AGameHUD* GameHUD = Cast<AGameHUD>(BaseHud))
		{
			Return();
		}
		else if (AMainMenuHUD* MainMenuHUD = Cast<AMainMenuHUD>(BaseHud))
		{
			SwitchCameraDefault();
		}
		return FReply::Handled();
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void USettingsMenuWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	//SwitcherTabSettings->SetFocusOnElement(0.01f);
	Super::NativeOnFocusLost(InFocusEvent);
}

void USettingsMenuWidget::Return()
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ABaseHUD* HUD = Cast<ABaseHUD>(PC->GetHUD());
	if (ensure(HUD))
	{
		HUD->CloseSettingsInBlueprint();
		/*
		UBaseMenuWidget* PreviousMenu = HUD->GetPreviousWidget();
		check(PreviousMenu);
		PreviousMenu->SetIsEnabled(true);
		PreviousMenu->SetVisibility(ESlateVisibility::Visible);
		PreviousMenu->GetFocusedButton()->SetFocus();
		HUD->GetSettingsMenuWidget()->SetVisibility(ESlateVisibility::Collapsed);
		*/
		
	}
}
