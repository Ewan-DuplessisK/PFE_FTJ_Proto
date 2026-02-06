// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StaticFunctions.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UStaticFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,Category=Helpers)
	static void OrderByDistance(AActor* PlayerActor, TArray<AActor*>inArray,TArray<AActor*>& outArray);
	UFUNCTION(BlueprintCallable,Category=Helpers)
	static bool IsInBuild();
};
