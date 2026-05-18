//Header

#include"UI/UIElements/UIElementButton.h"

//Private

//Protected

void UUIElementButton::NativeConstruct()
{
    Super::NativeConstruct();
    if(UpUIElement)
    {
        SetNavigationRuleExplicit(EUINavigation::Up , UpUIElement);
    }
    if(DownUIElement)
    {
        SetNavigationRuleExplicit(EUINavigation::Down , DownUIElement);
    }

}

//

void UUIElementButton::NativeOnHovered()
{
    Super::NativeOnHovered();
}

void UUIElementButton::NativeOnUnhovered()
{
    Super::NativeOnUnhovered();
}

//Public