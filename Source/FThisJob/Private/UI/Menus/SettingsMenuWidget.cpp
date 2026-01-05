// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/SettingsMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UI/UIElements/SwitcherTabSettings.h"
#include "UI/BaseHUD.h"
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
		SwitchCameraDefault();
		return FReply::Handled();
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void USettingsMenuWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	SwitcherTabSettings->SetFocusOnElement(0.01f);
	Super::NativeOnFocusLost(InFocusEvent);
}

void USettingsMenuWidget::Return()
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ABaseHUD* HUD = Cast<ABaseHUD>(PC->GetHUD());
	if (ensure(HUD))
	{
		UBaseMenuWidget* PreviousMenu = HUD->GetPreviousWidget();
		check(PreviousMenu);
		PreviousMenu->SetIsEnabled(true);
		PreviousMenu->SetVisibility(ESlateVisibility::Visible);
		PreviousMenu->GetFocusedButton()->SetFocus();
		HUD->GetSettingsMenuWidget()->SetVisibility(ESlateVisibility::Collapsed);
		
	}
}
