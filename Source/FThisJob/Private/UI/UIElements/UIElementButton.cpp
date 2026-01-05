// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/UIElementButton.h"

void UUIElementButton::NativeConstruct()
{
	Super::NativeConstruct();

	SetNavigationRuleExplicit(EUINavigation::Up, UpUIElement);
	SetNavigationRuleExplicit(EUINavigation::Down, DownUIElement);

}

void UUIElementButton::NativeOnHovered()
{
	Super::NativeOnHovered();
}
