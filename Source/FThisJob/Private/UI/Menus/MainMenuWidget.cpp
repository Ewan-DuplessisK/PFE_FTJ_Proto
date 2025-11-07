// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/MainMenuWidget.h"
#include "UI/UIElements/MainMenuButton.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ChangeLevelButton->SetFocus();
}


void UMainMenuWidget::OnChangeLevelClicked()
{
	SwitchCameraPlay();
	
	//Super::OnChangeLevelClicked();
}

void UMainMenuWidget::OnQuitClicked()
{
	SwitchCameraQuit();
	
	//Super::OnQuitClicked();
}

void UMainMenuWidget::OnSettingsClicked()
{
	SwitchCameraSettings();
	Super::OnSettingsClicked();
}

class UMainMenuButton* UMainMenuWidget::GetFocusedButton() const
{
	return ChangeLevelButton;
}
