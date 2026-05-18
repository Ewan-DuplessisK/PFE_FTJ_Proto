//Header

#include"UI/GameHUD.h"

#include"UI/Menus/BaseMenuWidget.h"
#include"UI/Menus/PauseMenuWidget.h"
#include"UI/Menus/SettingsMenuWidget.h"
#include"UI/UIElements/MainMenuButton.h"

#include"EnhancedInputSubsystems.h"
#include"PlayerCharacter_Base.h"
#include"Player_Controller.h"
#include"Kismet/GameplayStatics.h"

//Private

//Protected

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();
    APlayerController * Player_Controller{Cast<APlayerController>(GetOwningPlayerController())};
    check(Player_Controller);
    if(ensure(PreviousWidgetClass) && ensure(Player_Controller))
    {
        PreviousWidgetInstance = CreateWidget<UBaseMenuWidget>(Player_Controller , PreviousWidgetClass);
    }
    if(ensure(SettingsMenuWidgetClass) && ensure(Player_Controller))
    {
        SettingsMenuWidgetInstance = CreateWidget<USettingsMenuWidget>(Player_Controller , SettingsMenuWidgetClass);
    }
    if(ensure(EndScreenClass) && ensure(Player_Controller))
    {
        EndScreen = CreateWidget<UBaseMenuWidget>(Player_Controller , EndScreenClass);
    }
    //Player_Controller->SetInputMode(FInputModeGameOnly());
}

//

UBaseMenuWidget * AGameHUD::GetPreviousWidget()
{
    check(PreviousWidgetInstance);
    return(PreviousWidgetInstance);
}

USettingsMenuWidget * AGameHUD::GetSettingsMenuWidget() const
{
    check(SettingsMenuWidgetInstance);
    return(SettingsMenuWidgetInstance);
}

TSubclassOf<UCommonActivatableWidget> AGameHUD::GetEndScreenClass()
{
    return(EndScreenClass);
}

//Public

void AGameHUD::PauseGame() 
{
    UGameplayStatics::SetGamePaused(GetWorld() , true);
    check(PauseMenuWidgetClass);
    PauseMenuWidgetInstance = Cast<UPauseMenuWidget>(PushWidget(PauseMenuWidgetClass));
    OnPauseGameSound();
}

void AGameHUD::ResumeGame() 
{
    UGameplayStatics::SetGamePaused(GetWorld() , false);
    if(PauseMenuWidgetInstance)
    {
        PauseMenuWidgetInstance->DeactivateWidget();
        PauseMenuWidgetInstance = nullptr;
        OnResumeGameSound();
    }
}