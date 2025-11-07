// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/MainMenuButton.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMainMenuButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (!TextBlock)
	{
		return;
	}

	TextBlock->SetText(Text);
}

void UMainMenuButton::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (ButtonHoveredAnim)
	{
		PlayAnimation(ButtonHoveredAnim, 0.f, 1); 
	}
}

void UMainMenuButton::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();
	
	if (ButtonHoveredAnim)
	{
		PlayAnimation(ButtonHoveredAnim, 0.f, 1, EUMGSequencePlayMode::Reverse); 
	}
}

void UMainMenuButton::NativeOnPressed()
{
	Super::NativeOnClicked();
	
	if (ButtonClickedAnim)
	{
		PlayAnimation(ButtonClickedAnim, 0.f, 1);
	}
}


