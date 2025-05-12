// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponComponent_Base.h"

#include "Components/WidgetComponent.h"
#include "Weapons/InteractableWidget.h"
#include "Weapons/WeaponDataAsset_Base.h"

void UWeaponComponent_Base::BeginPlay()
{
	Super::BeginPlay();

	if(CurrentAmmo==-1)
	{
		CurrentAmmo = WeaponData->Ammo;
	}
	Cast<UInteractableWidget>(WidgetComponent->GetWidget())->Title = FText::FromName(WeaponData->Name);
}
