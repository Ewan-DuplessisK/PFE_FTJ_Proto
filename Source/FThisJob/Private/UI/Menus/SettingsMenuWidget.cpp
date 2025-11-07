// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/SettingsMenuWidget.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UIElements/SwitcherTabSettings.h"
#include "CommonAnimatedSwitcher.h"
#include "UI/BaseHUD.h"
#include "UI/Menus/BaseMenuWidget.h"
#include "UI/UIElements/MainMenuButton.h"

void USettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetupInputComponent();
}


void USettingsMenuWidget::SetupInputComponent()
{
	if (!MenusInputMappingContext)
	{
		return;
	}
	const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	InitializeInputComponent();
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(EnhancedInputSubsystem);
	EnhancedInputSubsystem->AddMappingContext(MenusInputMappingContext,200);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	if (!ensure(EnhancedInputComponent != nullptr))
	{
		return;
	}

	check(InputActionToRightTab);
	EnhancedInputComponent->BindAction(InputActionToRightTab, ETriggerEvent::Started, this, &USettingsMenuWidget::ToRightTab);
	check(InputActionToLeftTab);
	EnhancedInputComponent->BindAction(InputActionToLeftTab, ETriggerEvent::Started, this, &USettingsMenuWidget::ToLeftTab);
	check(InputActionReturn);
	EnhancedInputComponent->BindAction(InputActionReturn, ETriggerEvent::Started, this, &USettingsMenuWidget::Return);
	
}

UInputMappingContext* USettingsMenuWidget::GetInputMappingContext() const
{
	return MenusInputMappingContext;
}

void USettingsMenuWidget::ToRightTab(const struct FInputActionValue& Value)
{
	ensure(SwitcherTabSettings);
	if (SwitcherTabSettings->GetAnimatedSwitcher()->GetActiveWidgetIndex() >= 4)
	{
		SwitcherTabSettings->GetAnimatedSwitcher()->SetActiveWidgetIndex(0);
	}
	SwitcherTabSettings->GetAnimatedSwitcher()->SetActiveWidgetIndex(SwitcherTabSettings->GetAnimatedSwitcher()->GetActiveWidgetIndex()+1);
}

void USettingsMenuWidget::ToLeftTab(const struct FInputActionValue& Value)
{
	ensure(SwitcherTabSettings);

	if (SwitcherTabSettings->GetAnimatedSwitcher()->GetActiveWidgetIndex() <= 0)
	{
		SwitcherTabSettings->GetAnimatedSwitcher()->SetActiveWidgetIndex(4);
	}
	SwitcherTabSettings->GetAnimatedSwitcher()->SetActiveWidgetIndex(SwitcherTabSettings->GetAnimatedSwitcher()->GetActiveWidgetIndex()-1);
}

void USettingsMenuWidget::Return(const struct FInputActionValue& Value)
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ABaseHUD* HUD = Cast<ABaseHUD>(PC->GetHUD());

	if (ensure(HUD))
	{
		HUD->GetSettingsMenuWidget()->RemoveFromParent();
		HUD->GetPreviousWidget()->SetIsEnabled(true);
		HUD->GetPreviousWidget()->GetFocusedButton()->SetFocus();
	}
}
