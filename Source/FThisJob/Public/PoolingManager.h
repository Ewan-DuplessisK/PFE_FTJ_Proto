// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolingManager.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FPoolRequestResponce
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	bool Success;
	
	UPROPERTY(BlueprintReadOnly)
	FString Message;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<class AEnemy_Base*> EnemyPointers;
};

UCLASS()
class FTHISJOB_API APoolingManager : public AActor
{
	GENERATED_BODY()
	
public:
	/**Public functions*/
	
	// Sets default values for this actor's properties
	APoolingManager();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable, meta=(ToolTip="Request {Num} Enemies of {Class} class from the Pool"))
	FPoolRequestResponce PooledActorRequest(TSubclassOf<AEnemy_Base> Class, int Num);
	
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable, meta=(ToolTip="Give back an Enemy to the Pool once it's dead or unloaded"))
	bool HandOverActor(AEnemy_Base* Actor);
	
	/**Public variables*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="Spawn Point of all the enemies assigned to the pooling manager"))
	FVector PoolSpawnPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="DO NOT TOUCH"))
	TMap<TSubclassOf<class AEnemy_Base>, int> PoolSizeMap;
	
	/** all spawned enemies of a certain class */
	TMap<TSubclassOf<class AEnemy_Base>, TArray<class AEnemy_Base*>> Pool;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ToolTip="DO NOT TOUCH"))
	TArray<class AEnemy_Base*> TempPoolArray;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable)
	void InitializePoolSize();
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable)
	void PopulatePool();
	
	UFUNCTION(Blueprintable, BlueprintCallable)
	void AddTempToPool(TArray<TSubclassOf<AEnemy_Base>> EnemiesClasses, TArray<class AEnemy_Base*> SpawnedEnemies); 
};
