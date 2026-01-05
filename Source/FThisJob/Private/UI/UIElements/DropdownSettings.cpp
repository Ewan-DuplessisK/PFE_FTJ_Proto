// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/DropdownSettings.h"
#include "CommonAnimatedSwitcher.h"
#include "CommonTextBlock.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UIElements/CommonTextBlockDropdown.h"

void UDropdownSettings::NativeConstruct()
{
	Super::NativeConstruct();

	const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	for (FDropdownOption Entry : Entries)
	{
		CreateTextBlock(Entry.DisplayName);
	}

	if (ensure(CommonTextBlock != nullptr))
	{
		CommonTextBlock->SetText(NameText);
		CommonTextBlock->SetStyle(NormalTextStyle);
	}
}

FDropdownOption UDropdownSettings::GetSelectedOption() const
{
	int32 ActiveIndex = Switcher ? Switcher->GetActiveWidgetIndex() : 0;
	if (Entries.IsValidIndex(ActiveIndex))
	{
		return Entries[ActiveIndex];
	}
	return FDropdownOption();
}

void UDropdownSettings::NativeOnHovered()
{
	CommonTextBlock->SetStyle(HoveredTextStyle);

	UCommonTextBlockDropdown* CurrentText = Cast<UCommonTextBlockDropdown>(Switcher->GetActiveWidget());
	check(CurrentText);
	CurrentText->GetCommonTextBlock()->SetStyle(HoveredTextStyle);
	
	Super::NativeOnHovered();
}

void UDropdownSettings::NativeOnUnhovered()
{
	CommonTextBlock->SetStyle(NormalTextStyle);

	UCommonTextBlockDropdown* CurrentText = Cast<UCommonTextBlockDropdown>(Switcher->GetActiveWidget());
	check(CurrentText);
	CurrentText->GetCommonTextBlock()->SetStyle(NormalTextStyle);
	
	Super::NativeOnUnhovered();
}

FReply UDropdownSettings::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Gamepad_DPad_Left)
	{
		ToLeftOption();
	}

	if (InKeyEvent.GetKey() == EKeys::Gamepad_DPad_Right)
	{
		ToRightOption();
	}
	
	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

FReply UDropdownSettings::NativeOnAnalogValueChanged(const FGeometry& InGeometry,
	const FAnalogInputEvent& InAnalogEvent)
{
	const float CurrentCall = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	constexpr float JitterTime = 0.3f;
	if (CurrentCall - LastCall < JitterTime)
	{
		return FReply::Unhandled();
	}

	if (InAnalogEvent.GetKey() == EKeys::Gamepad_LeftX)
	{
		constexpr float DeadZone = 0.4f;
		if (InAnalogEvent.GetAnalogValue() > DeadZone)
		{
			ToRightOption();
			LastCall = CurrentCall;
		}
		else if (InAnalogEvent.GetAnalogValue() < -DeadZone)
		{
			ToLeftOption();
			LastCall = CurrentCall;
		}
	}
	
	return Super::NativeOnAnalogValueChanged(InGeometry, InAnalogEvent);
}

void UDropdownSettings::CreateTextBlock(FText Text)
{
	if (!Switcher || !CommonTextBlocDropDownClass)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	check(PC);

	UCommonTextBlockDropdown* CommonTextBlockDropdown = CreateWidget<UCommonTextBlockDropdown>(
		PC, CommonTextBlocDropDownClass);
	check(CommonTextBlockDropdown);

	Switcher->AddChild(CommonTextBlockDropdown);

	CommonTextBlockObject = CommonTextBlockDropdown->GetCommonTextBlock();
	check(CommonTextBlockObject);

	CommonTextBlockObject->SetText(Text);
	CommonTextBlockObject->SetStyle(NormalTextStyle);
}

void UDropdownSettings::ToRightOption()
{
	SwitcherLenght = Switcher->GetChildrenCount();
	int32 NewIndex = (Switcher->GetActiveWidgetIndex() + SwitcherLenght + 1) % SwitcherLenght;

	Switcher->SetActiveWidgetIndex(NewIndex);

	UCommonTextBlockDropdown* CurrentText = Cast<UCommonTextBlockDropdown>(Switcher->GetWidgetAtIndex(NewIndex));
	check(CurrentText);
	CurrentText->GetCommonTextBlock()->SetStyle(HoveredTextStyle);
}

void UDropdownSettings::ToLeftOption()
{
	SwitcherLenght = Switcher->GetChildrenCount();
	int32 NewIndex = (Switcher->GetActiveWidgetIndex() + SwitcherLenght - 1) % SwitcherLenght;

	Switcher->SetActiveWidgetIndex(NewIndex);

	UCommonTextBlockDropdown* CurrentText = Cast<UCommonTextBlockDropdown>(Switcher->GetWidgetAtIndex(NewIndex));
	check(CurrentText);
	CurrentText->GetCommonTextBlock()->SetStyle(HoveredTextStyle);
}

class UCommonAnimatedSwitcher* UDropdownSettings::GetSwitcher() const
{
	return Switcher;
}
