//Header

#include"UI/Menus/MainMenuWidget.h"

#include"UI/UIElements/MainMenuButton.h"

//Private

//Protected

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

//Public

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
    auto PC{GetWorld()->GetFirstPlayerController()};
    check(PC);
    PC->SetShowMouseCursor(true);	
    check(ChangeLevelButton);
    check(SettingsButton)
    check(QuitButton);
    ChangeLevelButton->OnClicked().AddUObject(this , &UMainMenuWidget::OnChangeLevelClicked);
    SettingsButton->OnClicked().AddUObject(this , &UMainMenuWidget::OnSettingsClicked);
    QuitButton->OnClicked().AddUObject(this , &UMainMenuWidget::OnQuitClicked);

}

void UMainMenuWidget::NativeOnActivated()
{	
    Super::NativeOnActivated();
}

//

TOptional<FUIInputConfig> UMainMenuWidget::GetDesiredInputConfig() const
{
    return(FUIInputConfig{ECommonInputMode::All, EMouseCaptureMode::NoCapture});
}

UMainMenuButton * UMainMenuWidget::GetFocusedButton() const
{
    return(ChangeLevelButton);
}

//

void UMainMenuWidget::UnQuit()
{
    SwitchCameraDefault();
}