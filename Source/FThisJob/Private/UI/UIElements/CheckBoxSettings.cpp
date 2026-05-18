//Header

#include"UI/UIElements/CheckBoxSettings.h"

#include"CommonTextBlock.h"
#include"Components/RichTextBlock.h"
#include"Components/CheckBox.h"

//Private

//Protected

void UCheckBoxSettings::NativePreConstruct()
{
    Super::NativePreConstruct();
    if(ensure(CommonTextBlock))
    {
        CommonTextBlock->SetText(Text);
        CommonTextBlock->SetStyle(NormalTextStyle);
    }
    if(!ensure(CheckBox))
    {
        return;
    }
    SetDesiredFocusWidget(CheckBox);
}

void UCheckBoxSettings::NativeConstruct()
{
    Super::NativeConstruct();
}

void UCheckBoxSettings::NativeOnMouseEnter(FGeometry const& InGeometry , FPointerEvent const& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry , InMouseEvent);
    CheckBox->SetIsEnabled(true);
    CommonTextBlock->SetStyle(HoveredTextStyle);
    OnHoveredSound();
}

void UCheckBoxSettings::NativeOnMouseLeave(FPointerEvent const& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
    CheckBox->SetIsEnabled(false);
    CheckBox->SetRenderOpacity(1.0f);
    CommonTextBlock->SetStyle(NormalTextStyle);
}

//Public
UCheckBox * UCheckBoxSettings::GetCheckBox() const
{
    return(CheckBox);
}
