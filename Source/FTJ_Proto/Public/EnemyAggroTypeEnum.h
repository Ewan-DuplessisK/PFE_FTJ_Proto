// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAggroTypeEnum.generated.h"

UENUM(BlueprintType)
enum class EAggroType : uint8
{
	KICK    UMETA(DisplayName = "Kick"),
	SPOTTED        UMETA(DisplayName = "Spotted"),
	NONE     UMETA(DisplayName = "None"),
	MAX      UMETA(Hidden)
};
