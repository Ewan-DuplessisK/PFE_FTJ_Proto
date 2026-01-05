// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/MainMenuWidget.h"
#include "UI/UIElements/MainMenuButton.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(this->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	check(ChangeLevelButton);
	ChangeLevelButton->OnClicked().AddUObject(this, &UMainMenuWidget::OnChangeLevelClicked);
	
	check(SettingsButton)
	SettingsButton->OnClicked().AddUObject(this, &UMainMenuWidget::OnSettingsClicked);

	check(QuitButton);
	QuitButton->OnClicked().AddUObject(this, &UMainMenuWidget::OnQuitClicked);

	check(NoQuitButton);
	NoQuitButton->OnClicked().AddUObject(this, &UMainMenuWidget::UnQuit);
}

void UMainMenuWidget::UnQuit()
{
	SwitchCameraDefault();
}

void UMainMenuWidget::OnChangeLevelClicked()
{
	SwitchCameraPlay();
}

void UMainMenuWidget::OnQuitClicked()
{
	SwitchCameraQuit();
}

void UMainMenuWidget::OnSettingsClicked()
{
	SwitchCameraSettings();
}

class UMainMenuButton* UMainMenuWidget::GetFocusedButton() const
{
	return ChangeLevelButton;
}
