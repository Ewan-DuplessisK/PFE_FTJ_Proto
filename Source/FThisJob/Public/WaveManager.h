// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

UCLASS()
class FTHISJOB_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Refs")
	class APoolingManager* PoolingManager;
	
	// Wave Manager Functions
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable)
	void LaunchWave(int index);
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable, meta=(ToolTip="Removes an enemy from the wave manager and hands it over to the pooling manager"))
	bool RemoveEnemyFromWaveManager(class AEnemy_Base* Enemy_To_Remove);

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="DO NOT TOUCH"))
	int CurrentAreaIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="DO NOT TOUCH"))
	int CurrentWaveIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="DO NOT TOUCH"))
	TArray<class AEnemy_Base*> SpawnedEnemies;
};
