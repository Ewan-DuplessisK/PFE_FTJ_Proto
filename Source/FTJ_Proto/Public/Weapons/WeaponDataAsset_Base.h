// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTypeEnum.h"
#include "Engine/DataAsset.h"
#include "Projectiles/Projectile_Base.h"
#include "WeaponDataAsset_Base.generated.h"

/**
 * 
 */
UCLASS()
class FTJ_PROTO_API UWeaponDataAsset_Base : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName Name = "<Weapon>";
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Damage = 0;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UWeaponTypeEnum Type = UWeaponTypeEnum::MELEE;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName SocketName = "FlyingSocket";
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FTransform RelativeSocketTransform;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* WeaponAnim;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ranged")
	bool IsAutomaticWeapon = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(ClampMin=0.01,ClampMax=1),Category="Ranged")
	float AutomaticFireDelay = .3;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ranged")
	int Ammo = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ranged")
	bool ThrowWhenEmpty = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ranged|Shotgun",meta=(ClampMin=1))
	int ProjectileNumber = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ranged|Shotgun",meta=(ClampMin=0))
	float Scatter = 0.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ranged")
	TSubclassOf<AProjectile_Base> ProjectileClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Melee")
	int Durability = 1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Melee")
	float MeleeHitForce = 3000.f;
};
