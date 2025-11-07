// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/PauseMenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UI/GameHUD.h"
#include "UI/UIElements/MainMenuButton.h"

UMainMenuButton* UPauseMenuWidget::GetFocusedButton() const
{
	return ResumeButton;
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(ResumeButton);
	ResumeButton->OnClicked().AddUObject(this, &UPauseMenuWidget::OnResumeClicked);
	ResumeButton->SetFocus();
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
	Super::OnSettingsClicked();
}

void UPauseMenuWidget::OnChangeLevelClicked()
{
	Super::OnChangeLevelClicked();
}

void UPauseMenuWidget::OnQuitClicked()
{
	Super::OnQuitClicked();
}
