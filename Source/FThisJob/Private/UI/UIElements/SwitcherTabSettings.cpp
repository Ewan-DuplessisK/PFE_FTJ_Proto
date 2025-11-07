// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/SwitcherTabSettings.h"

void USwitcherTabSettings::NativeConstruct()
{
	Super::NativeConstruct();
}

class UCommonAnimatedSwitcher* USwitcherTabSettings::GetAnimatedSwitcher() const
{
	return AnimatedSwitcher;
}
