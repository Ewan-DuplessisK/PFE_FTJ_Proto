//Header

#include"UI/Menus/SettingsTabs/WidgetTabHeader.h"

#include"UI/UIElements/SwitcherTabSettings.h"

#include"CommonTextBlock.h"
#include"Components/Image.h"
#include"Components/RichTextBlock.h"
#include"CommonUILibrary.h"
#include"Components/HorizontalBox.h"

//Private

//Protected

//Public

void UWidgetTabHeader::NativePreConstruct()
{
    Super::NativePreConstruct();
    if(!CommonTextBlock)
    {
        return;
    }
    CommonTextBlock->SetText(Text);
    if(UnSelectedTabTexture)
    {
        TabImage->SetBrushFromTexture(UnSelectedTabTexture);
        Toggle(false);
    }
}

void UWidgetTabHeader::NativeConstruct()
{
    Super::NativeConstruct();
    Switcher = Cast<USwitcherTabSettings>(UCommonUILibrary::FindParentWidgetOfType(this , USwitcherTabSettings::StaticClass()));
    Index = Switcher->GetTabHeaderBox()->GetChildIndex(this);
}

FReply UWidgetTabHeader::NativeOnMouseButtonDown(FGeometry const& InGeometry , FPointerEvent const& InMouseEvent)
{
    auto Reply{Super::NativeOnMouseButtonDown(InGeometry , InMouseEvent)};
    if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        Switcher->SetIndex(Index);
    }
    return(Reply);
}

void UWidgetTabHeader::NativeOnMouseEnter(FGeometry const& InGeometry , FPointerEvent const& InMouseEvent)
{
    check(TabImage);
    TabImage->SetBrushFromTexture(SelectedTabTexture);
}

void UWidgetTabHeader::NativeOnMouseLeave(FPointerEvent const& InMouseEvent)
{
    check(TabImage);
    TabImage->SetBrushFromTexture(UnSelectedTabTexture);
}

//

void UWidgetTabHeader::SetIndex(int NewIndex)
{
    Index = NewIndex;
}

int UWidgetTabHeader::GetIndex() const
{
    return(Index);
}

//

void UWidgetTabHeader::Toggle(bool bToggle)
{
    if(bToggle)
    {
        check(TabImage);
        TabImage->SetDesiredSizeOverride({SelectedTabTexture->GetSizeX()/1.5, SelectedTabTexture->GetSizeY()/1.5});
        CommonTextBlock->SetStyle(HoveredTextStyle);
    }
    else
    {
        check(TabImage);
        TabImage->SetDesiredSizeOverride({UnSelectedTabTexture->GetSizeX()/1.5, UnSelectedTabTexture->GetSizeY()/1.5});
        CommonTextBlock->SetStyle(NormalTextStyle);
    }
}

void UWidgetTabHeader::SetIsSelected(bool bIsSelected)
{
    isSelected = bIsSelected;
}