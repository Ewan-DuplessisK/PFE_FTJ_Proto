// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/MainMenuWidget.h"
#include "UI/UIElements/MainMenuButton.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();


	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	check(PC);
	PC->SetShowMouseCursor(true);	

	check(ChangeLevelButton);
	ChangeLevelButton->OnClicked().AddUObject(this, &UMainMenuWidget::OnChangeLevelClicked);
	
	check(SettingsButton)
	SettingsButton->OnClicked().AddUObject(this, &UMainMenuWidget::OnSettingsClicked);

	check(QuitButton);
	QuitButton->OnClicked().AddUObject(this, &UMainMenuWidget::OnQuitClicked);

	check(NoQuitButton);
	NoQuitButton->OnClicked().AddUObject(this, &UMainMenuWidget::UnQuit);
}

void UMainMenuWidget::NativeOnActivated()
{	
	Super::NativeOnActivated();
}

TOptional<FUIInputConfig> UMainMenuWidget::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture);
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
