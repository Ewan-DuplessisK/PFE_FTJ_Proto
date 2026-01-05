// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};
class IHitInterface
{
	GENERATED_BODY()
 
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	// Add interface function declarations here
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Hit Interface")
	void GetHit(float Damage,float HitStunDuration,FVector KnockbackVector, float InvincibilityTime,class AActor* SourceActor);
};