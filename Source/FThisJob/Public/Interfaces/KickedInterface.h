// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KickedInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UKickedInterface : public UInterface
{
	GENERATED_BODY()
};
class IKickedInterface
{
	GENERATED_BODY()
 
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	// Add interface function declarations here
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Kick Interface")
	void Kicked(FVector KickVector,FVector PlayerPosition);
};