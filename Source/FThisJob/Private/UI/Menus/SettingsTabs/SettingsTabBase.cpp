//Header

#include"UI/Menus/SettingsTabs/SettingsTabBase.h"

#include"Components/Image.h"
#include "Components/ScrollBox.h"

//Private

//Protected

void USettingsTabBase::NativeConstruct()
{
    Super::NativeConstruct();
}

//Public

void USettingsTabBase::SetupSettingsValues(USettingsSave * SettingSave)
{

}

UWidget * USettingsTabBase::NativeGetDesiredFocusTarget() const
{
    if(ScrollBox && ScrollBox->GetChildrenCount() > 0)
    {
        return(ScrollBox->GetChildAt(0));
    }
    return(nullptr);
}

UScrollBox * USettingsTabBase::GetScrollBox() const
{
    return(ScrollBox);
}