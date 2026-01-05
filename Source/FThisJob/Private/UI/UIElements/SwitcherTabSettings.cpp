// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/SwitcherTabSettings.h"
#include "CommonActivatableWidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "UI/Menus/SettingsTabs/SettingsTabBase.h"
#include "UI/Menus/SettingsTabs/WidgetTabHeader.h"

void USwitcherTabSettings::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply USwitcherTabSettings::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Gamepad_RightShoulder || InKeyEvent.GetKey() == EKeys::L)
	{
		ToRightTab();
		return FReply::Handled();
	}
	if (InKeyEvent.GetKey() == EKeys::Gamepad_LeftShoulder || InKeyEvent.GetKey() == EKeys::K)
	{
		ToLeftTab();
		return FReply::Handled();
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void USwitcherTabSettings::SetIndex(int Index, float WaitingTime) const
{
	UWidgetTabHeader* CurrentWidget = Cast<UWidgetTabHeader>(TabHeaderBox->GetChildAt(Index));

	AnimatedSwitcher->SetActiveWidgetIndex(Index);

	for (UWidget* Widget : TabHeaderBox->GetAllChildren())
	{
		if (UWidgetTabHeader* WidgetTab = Cast<UWidgetTabHeader>(Widget))
		{
			WidgetTab->Toggle(false);
		}
	}
	check(CurrentWidget);
	CurrentWidget->Toggle(true);

	SetFocusOnElement(WaitingTime);
}

void USwitcherTabSettings::SetFocusOnElement(float WaitingTime) const
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC)
	{
		return;
	}

	PC->FlushPressedKeys();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(
		Handle,
		[this]()
		{
			USettingsTabBase* CurrentWidget = Cast<USettingsTabBase>(AnimatedSwitcher->GetActiveWidget());
			if (!CurrentWidget)
			{
				return;
			}
			CurrentWidget->GetVerticalBox()->GetChildAt(0)->SetFocus();
		},
		WaitingTime,
		false
	);
}

void USwitcherTabSettings::ToRightTab() const
{
	const int32 NewIndex = (AnimatedSwitcher->GetActiveWidgetIndex() + TabHeaderBox->GetChildrenCount() + 1) %
		TabHeaderBox->GetChildrenCount();
	UCommonActivatableWidget* NewWidget = Cast<UCommonActivatableWidget>(AnimatedSwitcher->GetActiveWidget());
	NewWidget->ActivateWidget();
	SetIndex(NewIndex, 0.25f);
}

void USwitcherTabSettings::ToLeftTab() const
{
	const int32 NewIndex = (AnimatedSwitcher->GetActiveWidgetIndex() + TabHeaderBox->GetChildrenCount() - 1) %
		TabHeaderBox->GetChildrenCount();
	UCommonActivatableWidget* NewWidget = Cast<UCommonActivatableWidget>(AnimatedSwitcher->GetActiveWidget());
	NewWidget->ActivateWidget();
	SetIndex(NewIndex, 0.25f);
}

USettingsTabBase* USwitcherTabSettings::GetGameplayTab() const
{
	return GameplayTab;
}

USettingsTabBase* USwitcherTabSettings::GetAudioTab() const
{
	return AudioTab;
}

USettingsTabBase* USwitcherTabSettings::GetGraphicsTab() const
{
	return GraphicsTab;
}

/*USettingsTabBase* USwitcherTabSettings::GetAccessibilityTab() const
{
	return AccessibilityTab;
}*/

USettingsTabBase* USwitcherTabSettings::GetControlTab() const
{
	return ControlTab;
}

UWidgetTabHeader* USwitcherTabSettings::GetAudioTabHeader() const
{
	return AudioTabHeader;
}

UWidgetTabHeader* USwitcherTabSettings::GetGraphicsTabHeader() const
{
	return GraphicsTabHeader;
}

/*UWidgetTabHeader* USwitcherTabSettings::GetAccessibilityTabHeader() const
{
	return AccessibilityTabHeader;
}*/

UWidgetTabHeader* USwitcherTabSettings::GetControlTabHeader() const
{
	return ControlTabHeader;
}

class UWidgetTabHeader* USwitcherTabSettings::GetGameplayTabHeader() const
{
	return GameplayTabHeader;
}

class UHorizontalBox* USwitcherTabSettings::GetTabHeaderBox() const
{
	return TabHeaderBox;
}

class UCommonAnimatedSwitcher* USwitcherTabSettings::GetAnimatedSwitcher() const
{
	return AnimatedSwitcher;
}
