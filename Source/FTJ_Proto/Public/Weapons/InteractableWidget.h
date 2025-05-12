// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractableWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTJ_PROTO_API UInteractableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText Title;
	UFUNCTION(BlueprintCallable)
	FText GetText();
	
};
