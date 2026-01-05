// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIElements/CommonTextBlockDropdown.h"

void UCommonTextBlockDropdown::NativeConstruct()
{
	Super::NativeConstruct();
}

class UCommonTextBlock* UCommonTextBlockDropdown::GetCommonTextBlock() const
{
	return CommonTextBlock;
}
