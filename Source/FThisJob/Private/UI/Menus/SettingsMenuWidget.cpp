//Header

#include"UI/Menus/SettingsMenuWidget.h"

#include"UI/UIElements/SwitcherTabSettings.h"
#include"UI/BaseHUD.h"
#include"UI/GameHUD.h"
#include"UI/MainMenuHUD.h"
#include"UI/Menus/BaseMenuWidget.h"
#include"UI/Menus/SettingsTabs/SettingsTabBase.h"
#include"UI/UIElements/MainMenuButton.h"

#include"CommonAnimatedSwitcher.h"
#include "GameFramework/GameUserSettings.h"
#include"Kismet/GameplayStatics.h"

//Private

//Protected

void USettingsMenuWidget::Return()
{
    auto const PC{UGameplayStatics::GetPlayerController(GetWorld() , 0)};
    auto HUD{Cast<ABaseHUD>(PC->GetHUD())};
    if(ensure(HUD))
    {
        HUD->CloseSettings();
        OnReturnSound();
    }
}

void USettingsMenuWidget::OnBackClicked()
{
    auto const PC{UGameplayStatics::GetPlayerController(GetWorld() , 0)};
    auto BaseHud{PC->GetHUD()};
    if(auto GameHUD{Cast<AGameHUD>(BaseHud)})
    {
        Return();
    }
    else if(auto MainMenuHUD{Cast<AMainMenuHUD>(BaseHud)})
    {
        SwitchCameraDefault();
    }
}

//Public

void USettingsMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
    check(BackButton)
    BackButton->OnClicked().AddUObject(this , &USettingsMenuWidget::OnBackClicked);
}

FReply USettingsMenuWidget::NativeOnKeyDown(FGeometry const& InGeometry , FKeyEvent const& InKeyEvent)
{
    auto Reply{Super::NativeOnKeyDown(InGeometry , InKeyEvent)};    
    if(InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right || InKeyEvent.GetKey() == EKeys::Escape)
    {
        OnBackClicked();
        return(FReply::Handled());
    }
    SwitcherTabSettings->NativeOnKeyDown(InGeometry , InKeyEvent);
    return Reply;
}

void USettingsMenuWidget::NativeOnFocusLost(FFocusEvent const& InFocusEvent)
{
    Super::NativeOnFocusLost(InFocusEvent);
    //SwitcherTabSettings->SetFocusOnElement(0.01);
}

void USettingsMenuWidget::NativeOnActivated()
{
    Super::NativeOnActivated();
    SwitcherTabSettings->SetIndex(0);
}

//

USwitcherTabSettings * USettingsMenuWidget::GetSwitcherTabSettings() const
{
    return(SwitcherTabSettings);
}

TOptional<FUIInputConfig> USettingsMenuWidget::GetDesiredInputConfig() const
{
    return(FUIInputConfig{ECommonInputMode::Menu , EMouseCaptureMode::NoCapture});
}