//Header

#include"UI/Menus/BaseMenuWidget.h"

#include"UI/BaseHUD.h"
#include"UI/GameHUD.h"
#include"UI/Menus/SettingsMenuWidget.h"
#include"UI/Menus/SettingsTabs/SettingsTabBase.h"
#include"UI/UIElements/MainMenuButton.h"
#include"UI/UIElements/SwitcherTabSettings.h"

#include"CommonAnimatedSwitcher.h"
#include"Components/CanvasPanel.h"
#include"Components/VerticalBox.h"
#include"Kismet/GameplayStatics.h"

//Private

//Protected

void UBaseMenuWidget::OnChangeLevelClicked()
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld() , NewLevel);
}

void UBaseMenuWidget::OnSettingsClicked()
{
    OpenSettings();
}

void UBaseMenuWidget::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this , nullptr , EQuitPreference::Quit , false);
    //OpenQuitPanel();
}

//

void UBaseMenuWidget::UnQuit()
{
    if(auto PC{GetOwningPlayer()})
    {
        if (auto HUD{Cast<ABaseHUD>(PC->GetHUD())})
        {
            HUD->GetPreviousWidget()->GetMenuVerticalBox()->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

//

void UBaseMenuWidget::OpenSettings()
{
    if(auto PC{GetOwningPlayer()})
    {
        if(auto HUD{Cast<ABaseHUD>(PC->GetHUD())})
        {
            if(auto Settings{HUD->GetSettingsMenuWidget()})
            {
                check(Settings);
                Settings->GetSwitcherTabSettings()->SetIndex(0);
            }
        }
    }
}

void UBaseMenuWidget::OpenQuitPanel()
{
    
}

//Public

void UBaseMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
    auto PC{UGameplayStatics::GetPlayerController(GetWorld() , 0)};
    if(ensure(PC))
    {
        PC->bEnableClickEvents = false;
        PC->bEnableTouchEvents = false;
    }	
}

//

UMainMenuButton * UBaseMenuWidget::GetFocusedButton() const
{
    return(nullptr);
}

UVerticalBox * UBaseMenuWidget::GetMenuVerticalBox() const
{
    return(nullptr);
}