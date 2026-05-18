//Header

#include"UI/UIElements/DropdownSettings.h"

#include"UI/UIElements/CommonTextBlockDropdown.h"
#include"UI/UIElements/MainMenuButton.h"

#include"CommonAnimatedSwitcher.h"
#include"CommonTextBlock.h"
#include"Components/ComboBoxString.h"
#include"Kismet/GameplayStatics.h"

//Private

void UDropdownSettings::OnLeftArrowClicked()
{
    ToLeftOption();
}

void UDropdownSettings::OnRightArrowClicked()
{
    ToRightOption();
}

//Protected

FReply UDropdownSettings::NativeOnPreviewKeyDown(FGeometry const& InGeometry , FKeyEvent const& InKeyEvent)
{
    auto Reply{Super::NativeOnPreviewKeyDown(InGeometry , InKeyEvent)};
    if(InKeyEvent.GetKey() == EKeys::Gamepad_DPad_Left)
    {
        OnLeftArrowClicked();
    }
    if(InKeyEvent.GetKey() == EKeys::Gamepad_DPad_Right)
    {
        OnRightArrowClicked();
    }
    return(Reply);
}

FReply UDropdownSettings::NativeOnAnalogValueChanged(FGeometry const& InGeometry , FAnalogInputEvent const& InAnalogEvent)
{
    auto Reply{Super::NativeOnAnalogValueChanged(InGeometry , InAnalogEvent)};
    float const CurrentCall{static_cast<float>(UGameplayStatics::GetRealTimeSeconds(GetWorld()))};
    float constexpr JitterTime{0.3};
    if(CurrentCall - LastCall < JitterTime)
    {
        return(FReply::Unhandled());
    }
    if(InAnalogEvent.GetKey() == EKeys::Gamepad_LeftX)
    {
        float constexpr DeadZone{0.4};
        if(InAnalogEvent.GetAnalogValue() < -DeadZone)
        {
            ToLeftOption();
            LastCall = CurrentCall;
        }
        else if(InAnalogEvent.GetAnalogValue() > DeadZone)
        {
            ToRightOption();
            LastCall = CurrentCall;
        }
    }   
    return(Reply);
}

//

void UDropdownSettings::CreateTextBlock(FText Text)
{
    if(!Switcher || !CommonTextBlocDropDownClass)
    {
        return;
    }
    auto PC{UGameplayStatics::GetPlayerController(GetWorld(), 0)};
    check(PC);
    auto CommonTextBlockDropdown{CreateWidget<UCommonTextBlockDropdown>(PC , CommonTextBlocDropDownClass)};
    check(CommonTextBlockDropdown);
    Switcher->AddChild(CommonTextBlockDropdown);
    CommonTextBlockObject = CommonTextBlockDropdown->GetCommonTextBlock();
    check(CommonTextBlockObject);
    CommonTextBlockObject->SetText(Text);
    CommonTextBlockObject->SetStyle(NormalTextStyle);
}

//

void UDropdownSettings::ToLeftOption()
{
    PlayAnimationForward(ToLeftAnimation);
    SwitcherLenght = Switcher->GetChildrenCount();
    auto NewIndex{(Switcher->GetActiveWidgetIndex() + SwitcherLenght - 1) % SwitcherLenght};
    Switcher->SetActiveWidgetIndex(NewIndex);
    auto CurrentText{Cast<UCommonTextBlockDropdown>(Switcher->GetWidgetAtIndex(NewIndex))};
    check(CurrentText);
    CurrentText->GetCommonTextBlock()->SetStyle(HoveredTextStyle);
}

void UDropdownSettings::ToRightOption()
{
    PlayAnimationForward(ToRightAnimation);
    SwitcherLenght = Switcher->GetChildrenCount();
    auto NewIndex{(Switcher->GetActiveWidgetIndex() + SwitcherLenght + 1) % SwitcherLenght};
    Switcher->SetActiveWidgetIndex(NewIndex);
    auto CurrentText{Cast<UCommonTextBlockDropdown>(Switcher->GetWidgetAtIndex(NewIndex))};
    check(CurrentText);
    CurrentText->GetCommonTextBlock()->SetStyle(HoveredTextStyle);
}

//Public

FDropdownOption::FDropdownOption()
{

}

FDropdownOption FDropdownOption::MakeResolution(FText Name , FIntPoint Res)
{
    FDropdownOption Opt;
    Opt.DisplayName = Name;
    Opt.ValueType = EDropdownValueType::IntPoint;
    Opt.IntPointValue = Res;
    return(Opt);
}

FDropdownOption FDropdownOption::MakeWindowMode(FText Name , EWindowMode::Type Mode)
{
    FDropdownOption Opt;
    Opt.DisplayName = Name;
    Opt.ValueType = EDropdownValueType::WindowMode;
    Opt.WindowModeValue = Mode;
    return(Opt);
}

FDropdownOption FDropdownOption::MakeInteger(FText Name , int32 Val)
{
    FDropdownOption Opt;
    Opt.DisplayName = Name;
    Opt.ValueType = EDropdownValueType::Integer;
    Opt.IntValue = Val;
    return(Opt);
}

FDropdownOption FDropdownOption::MakeBool(FText Name , bool bValue)
{
    FDropdownOption Opt;
    Opt.DisplayName = Name;
    Opt.ValueType = EDropdownValueType::Bool;
    Opt.bValue = bValue;
    return(Opt);
}

void UDropdownSettings::NativePreConstruct()
{
    Super::NativePreConstruct();
    auto const PC{UGameplayStatics::GetPlayerController(GetWorld(), 0)};
    if(ensure(CommonTextBlock))
    {
        CommonTextBlock->SetText(NameText);
        CommonTextBlock->SetStyle(NormalTextStyle);
    }
    LeftArrowButton->OnClicked().AddUObject(this , &UDropdownSettings::OnLeftArrowClicked);
    RightArrowButton->OnClicked().AddUObject(this , &UDropdownSettings::OnRightArrowClicked);
}

void UDropdownSettings::NativeConstruct()
{
    Super::NativeConstruct();
    for(FDropdownOption const& Entry : Entries)
    {
        CreateTextBlock(Entry.DisplayName);
    }
    LeftArrowButton->SetIsEnabled(false);
    RightArrowButton->SetIsEnabled(false);
}

void UDropdownSettings::NativeOnHovered()
{
    Super::NativeOnHovered();
    CommonTextBlock->SetStyle(HoveredTextStyle);
    auto CurrentText{Cast<UCommonTextBlockDropdown>(Switcher->GetActiveWidget())};
    check(CurrentText);
    CurrentText->GetCommonTextBlock()->SetStyle(HoveredTextStyle);
    OnHoveredSound();

    
    LeftArrowButton->SetIsEnabled(true);
    RightArrowButton->SetIsEnabled(true);
}

void UDropdownSettings::NativeOnUnhovered()
{
    Super::NativeOnUnhovered();
    CommonTextBlock->SetStyle(NormalTextStyle);
    auto CurrentText{Cast<UCommonTextBlockDropdown>(Switcher->GetActiveWidget())};
    check(CurrentText);
    CurrentText->GetCommonTextBlock()->SetStyle(NormalTextStyle);
    
    LeftArrowButton->SetIsEnabled(false);
    RightArrowButton->SetIsEnabled(false);
}

//

FDropdownOption UDropdownSettings::GetSelectedOption() const
{
    int32 ActiveIndex{Switcher ? Switcher->GetActiveWidgetIndex() : 0};
    if(Entries.IsValidIndex(ActiveIndex))
    {
        return(Entries[ActiveIndex]);
    }
    return(FDropdownOption{});
}

UCommonAnimatedSwitcher * UDropdownSettings::GetSwitcher() const
{
    return(Switcher);
}

TArray<FDropdownOption> const& UDropdownSettings::GetEntries()
{
    return(Entries);
}