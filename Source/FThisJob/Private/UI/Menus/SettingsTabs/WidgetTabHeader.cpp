// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/SettingsTabs/WidgetTabHeader.h"

#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"

void UWidgetTabHeader::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CommonTextBlock)
	{
		return;
	}
	CommonTextBlock->SetText(Text);
}

void UWidgetTabHeader::SetIndex(int NewIndex)
{
	Index = NewIndex;
}

int UWidgetTabHeader::GetIndex() const
{
	return Index;
}

void UWidgetTabHeader::Toggle(bool bToggle)
{
	if (bToggle)
	{
		check(TabImage);
		TabImage->SetBrushFromTexture(SelectedTabTexture);
		FVector2D TextureSize = FVector2D(SelectedTabTexture->GetSizeX()/1.5, SelectedTabTexture->GetSizeY()/1.5);
		TabImage->SetDesiredSizeOverride(TextureSize);
		CommonTextBlock->SetStyle(HoveredTextStyle);
	}
	else
	{
		check(TabImage);
		TabImage->SetBrushFromTexture(UnSelectedTabTexture);
		FVector2D TextureSize = FVector2D(UnSelectedTabTexture->GetSizeX()/1.5, UnSelectedTabTexture->GetSizeY()/1.5);
		TabImage->SetDesiredSizeOverride(TextureSize);
		CommonTextBlock->SetStyle(NormalTextStyle);
	}
}
