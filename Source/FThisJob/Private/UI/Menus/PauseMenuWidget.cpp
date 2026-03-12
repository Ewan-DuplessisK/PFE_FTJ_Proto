// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/PauseMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UI/GameHUD.h"
#include "UI/UIElements/MainMenuButton.h"

UMainMenuButton* UPauseMenuWidget::GetFocusedButton() const
{
	return ResumeButton;
}

class UVerticalBox* UPauseMenuWidget::GetMenuVerticalBox() const
{
	return MenuVerticalBox;
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(ResumeButton);
	ResumeButton->OnClicked().AddUObject(this, &UPauseMenuWidget::OnResumeClicked);

	check(ChangeLevelButton);
	ChangeLevelButton->OnClicked().AddUObject(this, &UPauseMenuWidget::OnChangeLevelClicked);
	
	check(SettingsButton)
	SettingsButton->OnClicked().AddUObject(this, &UPauseMenuWidget::OnSettingsClicked);

	check(QuitButton);
	QuitButton->OnClicked().AddUObject(this, &UPauseMenuWidget::OnQuitClicked);

	check(NoQuitButton);
	NoQuitButton->OnClicked().AddUObject(this, &UPauseMenuWidget::UnQuit);

}

FReply UPauseMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right || InKeyEvent.GetKey() == EKeys::Gamepad_Special_Right)
	{
		OnResumeClicked();
		
		return FReply::Handled();
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UPauseMenuWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (ResumeButton)
	{
		ResumeButton->SetFocus();
	}
}

void UPauseMenuWidget::OnResumeClicked() const
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AGameHUD* HUD = Cast<AGameHUD>(PC->GetHUD());

	if (ensure(HUD))
	{
		HUD->ResumeGame();
	}
}

void UPauseMenuWidget::OnSettingsClicked()
{
	const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AGameHUD* HUD = Cast<AGameHUD>(PC->GetHUD());

	if (ensure(HUD))
	{
		HUD->OpenSettingsInBlueprint();
	}
	
	Super::OnSettingsClicked();
}

void UPauseMenuWidget::OnChangeLevelClicked()
{
	Super::OnChangeLevelClicked();
}

void UPauseMenuWidget::OnQuitClicked()
{
	TempQuitFunction();
}

void UPauseMenuWidget::UnQuit()
{
	Super::UnQuit();
}
