// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyStateEnum.generated.h"

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	PATROL    UMETA(DisplayName = "Patrol"),
	CHASE        UMETA(DisplayName = "Chase"),
	SITTING     UMETA(DisplayName = "Sitting"),
	TALKING     UMETA(DisplayName = "Talking"),
	CHARGE     UMETA(DisplayName = "Charge"),
	GRAB     UMETA(DisplayName = "Grab"),
	STUN     UMETA(DisplayName = "Stun"),
	MAX      UMETA(Hidden)
};
