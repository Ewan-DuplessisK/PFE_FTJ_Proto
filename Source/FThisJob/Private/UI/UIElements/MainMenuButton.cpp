// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/MainMenuButton.h"
#include "CommonTextBlock.h"
#include "Animation/WidgetAnimation.h"

void UMainMenuButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (!TextBlock)
	{
		return;
	}

	TextBlock->SetText(Text);
	TextBlock->SetStyle(NormalTextStyle);
}

void UMainMenuButton::NativeOnHovered()
{
	check(TextBlock);
	TextBlock->SetStyle(HoveredTextStyle);
	
	Super::NativeOnHovered();
}

void UMainMenuButton::NativeOnUnhovered()
{
	check(TextBlock);
	TextBlock->SetStyle(NormalTextStyle);
	
	Super::NativeOnUnhovered();
}

void UMainMenuButton::NativeOnPressed()
{
	check(TextBlock);
	TextBlock->SetStyle(PressedTextStyle);
	
	Super::NativeOnClicked();
	
	/*if (ButtonClickedAnim)
	{
		PlayAnimation(ButtonClickedAnim, 0.f, 1);
	}*/
}


