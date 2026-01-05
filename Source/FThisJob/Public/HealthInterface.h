// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"
/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};
 
/* Actual Interface declaration. */
class IHealthInterface
{
	GENERATED_BODY()
 
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	// Add interface function declarations here
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	void RemoveHealth(float Damage, AActor* EnemyRef);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	void AddHealth(float Amount);
};
