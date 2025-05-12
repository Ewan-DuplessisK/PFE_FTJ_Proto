// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTypeEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class UWeaponTypeEnum : uint8
{
	MELEE UMETA(DisplayName="Melee"),
	RANGED UMETA(DisplayName="Ranged"),
	MAX UMETA(Hidden)
};
