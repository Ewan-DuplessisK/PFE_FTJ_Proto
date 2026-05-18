//Header

#include"UI/UIElements/MainMenuButton.h"

#include"CommonTextBlock.h"
#include"Animation/WidgetAnimation.h"
#include"Components/Overlay.h"
#include"Components/OverlaySlot.h"

//Private

//Protected

//Public

void UMainMenuButton::NativePreConstruct()
{
    Super::NativePreConstruct();   
    if(!TextBlock)
    {
        return;
    }
    TextBlock->SetText(Text);
    TextBlock->SetStyle(NormalTextStyle);
    Cast<UOverlaySlot>(Overlay->GetSlots()[0])->SetPadding(TextPadding);
}

void UMainMenuButton::NativeConstruct()
{
    Super::NativeConstruct();
}

void UMainMenuButton::NativeOnHovered()
{
    Super::NativeOnHovered();
    check(TextBlock);
    TextBlock->SetStyle(HoveredTextStyle);
}

void UMainMenuButton::NativeOnUnhovered()
{
    Super::NativeOnUnhovered();
    check(TextBlock);
    TextBlock->SetStyle(NormalTextStyle);
}

void UMainMenuButton::NativeOnPressed()
{
    Super::NativeOnPressed();
    check(TextBlock);
    TextBlock->SetStyle(PressedTextStyle);
    /*
    if (ButtonClickedAnim)
    {
        PlayAnimation(ButtonClickedAnim , 0.0 , 1);
    }
    */
}