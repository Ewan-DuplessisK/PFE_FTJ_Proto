//Header

#include"UI/MainMenuHUD.h"

#include"UI/Menus/BaseMenuWidget.h"
#include"UI/Menus/PauseMenuWidget.h"
#include"UI/Menus/SettingsMenuWidget.h"
#include"UI/UIElements/MainMenuButton.h"

#include"InputMappingContext.h"
#include"Blueprint/UserWidget.h"
#include"CommonInputSubsystem.h"

//Private

//Protected

void AMainMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    APlayerController * PC{GetOwningPlayerController()};
    if (ULocalPlayer * LocalPlayer{PC->GetLocalPlayer()})
    {
        if(UCommonInputSubsystem * InputSubsystem{ULocalPlayer::GetSubsystem<UCommonInputSubsystem>(LocalPlayer)})
        {
            InputSubsystem->OnInputMethodChangedNative.AddUObject(this , &AMainMenuHUD::HandleInputMethodChanged);
        }
    }

    PreviousWidgetInstance = Cast<UBaseMenuWidget>(PushWidget(PreviousWidgetClass));
}

void AMainMenuHUD::HandleInputMethodChanged(ECommonInputType NewInputType) const
{
    switch(NewInputType)
    {
        case(ECommonInputType::Gamepad):
            //UE_LOG(LogTemp, Warning, TEXT("Switched to Gamepad!"));
        break;
        case(ECommonInputType::MouseAndKeyboard):
            //UE_LOG(LogTemp, Warning, TEXT("Switched to Mouse & Keyboard!"));
        break;
        default:

        break;
    }
}

//

UBaseMenuWidget * AMainMenuHUD::GetPreviousWidget()
{
    return(PreviousWidgetInstance);
}

USettingsMenuWidget * AMainMenuHUD::GetSettingsMenuWidget() const
{
    return(SettingsMenuWidgetInstance);
}

//Public