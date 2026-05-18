//Header

#include"UI/UIElements/SwitcherTabSettings.h"

#include"UI/Menus/SettingsTabs/SettingsTabBase.h"
#include"UI/Menus/SettingsTabs/WidgetTabHeader.h"

#include"CommonActivatableWidgetSwitcher.h"
#include"Components/HorizontalBox.h"
#include"Components/VerticalBox.h"
#include"Components/Image.h"
#include"CommonInputSubsystem.h"

//Private

//Protected

void USwitcherTabSettings::ToLeftTab() const
{
    int32 const NewIndex{(AnimatedSwitcher->GetActiveWidgetIndex() + TabHeaderBox->GetChildrenCount() - 1) % TabHeaderBox->GetChildrenCount()};
    SetIndex(NewIndex);
}

void USwitcherTabSettings::ToRightTab() const
{
    int32 const NewIndex{(AnimatedSwitcher->GetActiveWidgetIndex() + TabHeaderBox->GetChildrenCount() + 1) % TabHeaderBox->GetChildrenCount()};
    SetIndex(NewIndex);
}

//Public

void USwitcherTabSettings::NativePreConstruct()
{
    Super::NativePreConstruct();
    LeftSwitchImage->SetBrushResourceObject(NormalLeftSwitchTexture);
    RightSwitchImage->SetBrushResourceObject(NormalRightSwitchTexture);
}

void USwitcherTabSettings::NativeConstruct()
{
    Super::NativeConstruct();
    if(AnimatedSwitcher)
    {
        AnimatedSwitcher->OnTransitioningChanged.AddUObject(this , &USwitcherTabSettings::HandleTransitioningChanged);
    }
}

void USwitcherTabSettings::NativeTick(const FGeometry& InGeometry , float InDeltaTime)
{
    Super::NativeTick(InGeometry , InDeltaTime);
    switch(GetWorld()->GetFirstLocalPlayerFromController()->GetSubsystem<UCommonInputSubsystem>()->GetCurrentInputType())
    {
        case(ECommonInputType::MouseAndKeyboard):
            LeftSwitchImage->SetOpacity(0.0);
            RightSwitchImage->SetOpacity(0.0);
        break;
        case(ECommonInputType::Gamepad):
            LeftSwitchImage->SetOpacity(1.0);
            RightSwitchImage->SetOpacity(1.0);
        break;
    }
}

FReply USwitcherTabSettings::NativeOnKeyDown(const FGeometry& InGeometry , const FKeyEvent& InKeyEvent)
{
    auto Reply{Super::NativeOnKeyDown(InGeometry , InKeyEvent)};
    if (InKeyEvent.GetKey() == EKeys::Gamepad_LeftShoulder || InKeyEvent.GetKey() == EKeys::K)
    {
        ToLeftTab();
        LeftSwitchImage->SetBrushResourceObject(PressedLeftSwitchTexture);
        return(FReply::Handled());
    }
    if(InKeyEvent.GetKey() == EKeys::Gamepad_RightShoulder || InKeyEvent.GetKey() == EKeys::L)
    {
        ToRightTab();
        RightSwitchImage->SetBrushResourceObject(PressedRightSwitchTexture);
        return(FReply::Handled());
    }
    return(Reply);
}

FReply USwitcherTabSettings::NativeOnKeyUp(const FGeometry& InGeometry , const FKeyEvent& InKeyEvent)
{
    auto Reply{Super::NativeOnKeyUp(InGeometry, InKeyEvent)};
    if(InKeyEvent.GetKey() == EKeys::Gamepad_LeftShoulder || InKeyEvent.GetKey() == EKeys::K)
    {
        LeftSwitchImage->SetBrushResourceObject(NormalLeftSwitchTexture);
        return(FReply::Handled());
    }
    if(InKeyEvent.GetKey() == EKeys::Gamepad_RightShoulder || InKeyEvent.GetKey() == EKeys::L)
    {
        RightSwitchImage->SetBrushResourceObject(NormalRightSwitchTexture);
        return(FReply::Handled());
    }
    return(Reply);
}

//

UHorizontalBox * USwitcherTabSettings::GetTabHeaderBox() const
{
    return(TabHeaderBox);
}

UCommonAnimatedSwitcher * USwitcherTabSettings::GetAnimatedSwitcher() const
{
    return(AnimatedSwitcher);
}

//

void USwitcherTabSettings::HandleTransitioningChanged(bool bIsTransitioning)
{
    if(!bIsTransitioning)
    {
        /*
            La transition est finie, mais le widget n'est pas forcément
            interactable dans le même frame. On attend le tick suivant
            pour que CommonUI finalise son layout et accepte le focus.
        */
        if(auto World{GetWorld()})
        {
            //World->GetTimerManager().SetTimerForNextTick([this]()
            //{
                SetFocusOnElement();
            //});
        }
    }
}

void USwitcherTabSettings::SetIndex(int Index) const
{
    auto CurrentWidget{Cast<UWidgetTabHeader>(TabHeaderBox->GetChildAt(Index))};
    AnimatedSwitcher->SetActiveWidgetIndex(Index);
    for(auto Widget : TabHeaderBox->GetAllChildren())
    {
        if(auto WidgetTab{Cast<UWidgetTabHeader>(Widget)})
        {
            WidgetTab->Toggle(false);
            WidgetTab->SetIsSelected(false);
        }
    }
    check(CurrentWidget);
    CurrentWidget->Toggle(true);
    if(auto World = GetWorld())
    {
        if(!AnimatedSwitcher->IsTransitionPlaying())
        {
            //World->GetTimerManager().SetTimerForNextTick([this]()
            //{
                SetFocusOnElement();
            //});
        }
    }
}

void USwitcherTabSettings::SetFocusOnElement() const
{
    auto PC{GetWorld()->GetFirstPlayerController()};
    if(!PC)
    {
        return;
    }
    PC->FlushPressedKeys();
    auto ActiveTab{Cast<USettingsTabBase>(AnimatedSwitcher->GetActiveWidget())};
    if(ActiveTab)
    {
        auto FocusTarget{ActiveTab->NativeGetDesiredFocusTarget()};
        if(FocusTarget)
        {
            FocusTarget->SetUserFocus(PC);
        }
    }
}

//

USettingsTabBase * USwitcherTabSettings::GetGameplayTab() const
{
    return(GameplayTab);
}

USettingsTabBase * USwitcherTabSettings::GetAudioTab() const
{
    return(AudioTab);
}

USettingsTabBase * USwitcherTabSettings::GetGraphicsTab() const
{
    return(GraphicsTab);
}

USettingsTabBase * USwitcherTabSettings::GetControlTab() const
{
    return(ControlTab);
}

//

UWidgetTabHeader * USwitcherTabSettings::GetGameplayTabHeader() const
{
    return(GameplayTabHeader);
}

UWidgetTabHeader * USwitcherTabSettings::GetAudioTabHeader() const
{
    return(AudioTabHeader);
}

UWidgetTabHeader * USwitcherTabSettings::GetGraphicsTabHeader() const
{
    return(GraphicsTabHeader);
}

UWidgetTabHeader * USwitcherTabSettings::GetControlTabHeader() const
{
    return(ControlTabHeader);
}