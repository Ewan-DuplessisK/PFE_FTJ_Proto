//Header

#include"UI/BaseHUD.h"

#include"UI/Menus/GameLayoutWidget.h"
#include"UI/Menus/SettingsMenuWidget.h"

#include"CommonActivatableWidget.h"
#include"Widgets/CommonActivatableWidgetContainer.h"

//Private

//Protected

void ABaseHUD::BeginPlay()
{
    Super::BeginPlay();
    //ABSOLUTE MUST
    check(GameLayoutWidgetClass);
    if(GameLayoutWidget)
    {
        return;
    }
    GameLayoutWidget = CreateWidget<UGameLayoutWidget>(GetWorld()->GetFirstPlayerController() , GameLayoutWidgetClass);
    GameLayoutWidget->AddToViewport();
}

//Public

UBaseMenuWidget * ABaseHUD::GetPreviousWidget()
{
    return(nullptr);
}

USettingsMenuWidget * ABaseHUD::GetSettingsMenuWidget() const
{
    return(nullptr);
}

UCommonActivatableWidgetStack * ABaseHUD::GetWidgetStack() const
{
    check(GameLayoutWidget);
    return(GameLayoutWidget->GetStack());
}

//

UCommonActivatableWidget * ABaseHUD::PushWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    check(GameLayoutWidget);
    return(GameLayoutWidget->GetStack()->AddWidget<UCommonActivatableWidget>(WidgetClass));
}

void ABaseHUD::PopWidget(UCommonActivatableWidget * Widget)
{
    check(Widget);
    Widget->DeactivateWidget();
}

//

void ABaseHUD::OpenSettings()
{
    if(!ensure(SettingsMenuWidgetClass))
    {
        return;
    }
    if(!SettingsMenuWidgetInstance)
    {
        SettingsMenuWidgetInstance = CreateWidget<USettingsMenuWidget>(GetWorld()->GetFirstPlayerController() , SettingsMenuWidgetClass);
    }
    if(ensure(SettingsMenuWidgetInstance) && !SettingsMenuWidgetInstance->IsActivated())
    {
        GetWidgetStack()->AddWidgetInstance(*SettingsMenuWidgetInstance);
    }
}

void ABaseHUD::OpenQuitPanel()
{
    if (!ensure(QuitPanelClass)){return;}

    if (!QuitPanelInstance)
    {
        QuitPanelInstance = CreateWidget<USettingsMenuWidget>(GetWorld()->GetFirstPlayerController(), QuitPanelClass);
    }

    if (ensure(QuitPanelInstance) && !QuitPanelInstance->IsActivated())
    {
        GetWidgetStack()->AddWidgetInstance(*QuitPanelInstance);
    }
}

//

void ABaseHUD::CloseSettings()
{
    if(SettingsMenuWidgetInstance)
    {
        SettingsMenuWidgetInstance->DeactivateWidget();
    }
}

void ABaseHUD::CloseQuitPanel()
{
    if(QuitPanelInstance)
    {
        QuitPanelInstance->DeactivateWidget();
    }
}