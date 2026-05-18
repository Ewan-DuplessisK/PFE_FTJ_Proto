//Header

#include"UI/Menus/PauseMenuWidget.h"

#include"UI/GameHUD.h"
#include"UI/UIElements/MainMenuButton.h"

#include"Kismet/GameplayStatics.h"

//Private

void UPauseMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
    check(ResumeButton);
    check(ChangeLevelButton);
    check(SettingsButton)
    check(QuitButton);
    ResumeButton->OnClicked().AddUObject(this , &UPauseMenuWidget::OnResumeClicked);
    ChangeLevelButton->OnClicked().AddUObject(this , &UPauseMenuWidget::OnChangeLevelClicked);
    SettingsButton->OnClicked().AddUObject(this , &UPauseMenuWidget::OnSettingsClicked);
    QuitButton->OnClicked().AddUObject(this , &UPauseMenuWidget::OnQuitClicked);
    SetDesiredFocusWidget(ResumeButton);
}

FReply UPauseMenuWidget::NativeOnKeyDown(FGeometry const& InGeometry , FKeyEvent const& InKeyEvent)
{
    auto Reply{Super::NativeOnKeyDown(InGeometry , InKeyEvent)};
    if(InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right || InKeyEvent.GetKey() == EKeys::Gamepad_Special_Right || InKeyEvent.GetKey() == EKeys::Escape)
    {
        OnResumeClicked();  
        return(FReply::Handled());
    }
    return(Reply);
}

UWidget * UPauseMenuWidget::NativeGetDesiredFocusTarget() const
{
    return(ResumeButton);
}

void UPauseMenuWidget::NativeOnActivated()
{
    Super::NativeOnActivated();
    if(ResumeButton)
    {
        ResumeButton->SetFocus();
    }
}

//

UMainMenuButton * UPauseMenuWidget::GetFocusedButton() const
{
    return(ResumeButton);
}

UVerticalBox * UPauseMenuWidget::GetMenuVerticalBox() const
{
    return(MenuVerticalBox);
}

TOptional<FUIInputConfig> UPauseMenuWidget::GetDesiredInputConfig() const
{
    return(FUIInputConfig{ECommonInputMode::Menu , EMouseCaptureMode::NoCapture});
}

//

void UPauseMenuWidget::OnResumeClicked() const
{
    auto const PC{UGameplayStatics::GetPlayerController(GetWorld() , 0)};
    auto HUD{Cast<AGameHUD>(PC->GetHUD())};
    if(ensure(HUD))
    {
        HUD->ResumeGame();
    }
}

void UPauseMenuWidget::OnSettingsClicked()
{
    Super::OnSettingsClicked();
    auto const PC{UGameplayStatics::GetPlayerController(GetWorld() , 0)};
    auto HUD{Cast<AGameHUD>(PC->GetHUD())};
    if(ensure(HUD))
    {
        HUD->OpenSettings();
    }
}

void UPauseMenuWidget::OnChangeLevelClicked()
{
    OnMainMenuImplementation();
}

void UPauseMenuWidget::OnQuitClicked()
{
    OnQuitImplementation();
}

//

void UPauseMenuWidget::UnQuit()
{
    Super::UnQuit();
}

//Protected

//Public