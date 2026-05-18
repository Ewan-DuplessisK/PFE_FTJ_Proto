// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPool_Component.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTHISJOB_API UObjectPool_Component : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UObjectPool_Component();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Amount")
	int Amount_Light = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Amount")
	int Amount_Medium = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Amount")
	int Amount_Heavy = 1000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrays")
	TArray<TSubclassOf<AActor>> PooledActorClass = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrays")
	TArray<AActor*> ObjectPool = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Arrays")
	TArray<AActor*> ActiveActors = {};
	
	UFUNCTION(Blueprintable, BlueprintCallable)
	void InitPool();
	
	UFUNCTION(Blueprintable, BlueprintCallable)
	AActor* FindAvailableActor(TSubclassOf<AActor> inActor);
	
	UFUNCTION(Blueprintable, BlueprintCallable)
	AActor* SpawnFromPool(FTransform spawnTransform, TSubclassOf<AActor> inActor);
	
	UFUNCTION(Blueprintable, BlueprintCallable)
	void ReturnToPool(AActor* inActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	bool shouldSpawnMissingActor = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
	bool debugActive = true;
};
