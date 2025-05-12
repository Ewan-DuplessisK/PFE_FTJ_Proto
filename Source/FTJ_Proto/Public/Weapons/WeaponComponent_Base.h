// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractibleComponent_Base.h"
#include "WeaponComponent_Base.generated.h"

/**
 * 
 */
UCLASS()
class FTJ_PROTO_API UWeaponComponent_Base : public UInteractibleComponent_Base
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ClampMin=-1))
	int CurrentAmmo = -1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UWeaponDataAsset_Base* WeaponData = nullptr;
};
