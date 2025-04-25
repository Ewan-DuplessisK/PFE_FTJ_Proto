// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIManager.generated.h"

UCLASS()
class FTJ_PROTO_API AAIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Array of Sitting and Talking Enemy for GD to know who are in this State
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIManager|Variables")
	TArray<AActor*> EnemySitting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIManager|Variables")
	TArray<AActor*> EnemyTalking;
	

};
