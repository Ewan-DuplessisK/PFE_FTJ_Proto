// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AimState_Enum.generated.h"

UENUM(BlueprintType)
enum class UAimState_Enum : uint8
{
	NotEngaged UMETA(DisplayName = "Not Engaged"),
	MagnetiseCrosshair UMETA(DisplayName = "Magnetise Crosshair"),
	BendingCrosshair UMETA(DisplayName = "Bending Crosshair"),
	SimpleEngaged UMETA(DisplayName = "Simple Engaged"),
	LockingWeakSpot UMETA(DisplayName = "Locking on Weak Spot"),
	LockingBaseSpot UMETA(DisplayName = "Locking on Base Spot")
	
};
