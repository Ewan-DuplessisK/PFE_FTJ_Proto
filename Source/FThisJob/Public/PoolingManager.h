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
	bool Success = false;
	
	UPROPERTY(BlueprintReadOnly)
	FString Message;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<class AActor*> ActorPointers;
};

UCLASS()
class FTHISJOB_API APoolingManager : public AActor
{
	GENERATED_BODY()
	
public:
	/**Public functions*/
	
	// Sets default values for this actor's properties
	APoolingManager();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable, meta=(ToolTip="Request {Num} Actor of {Class} class from the Pool"))
	FPoolRequestResponce PooledActorRequest(TSubclassOf<AActor> Class, int Num);
	
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable, meta=(ToolTip="Give back an Actor to the Pool once it's dead or unloaded"))
	bool HandOverActor(AActor* Actor);
	
	/**Public variables*/
	
	/** Amount of a certain class */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default|Map", meta=(ToolTip="DO NOT TOUCH"))
	TMap<TSubclassOf<class AActor>, int> PoolSizeMap;
	
	/** All spawned enemies of a certain class */
	//TMap<TSubclassOf<class AActor>, TArray<class AActor*>> Pool;
	
	// Suckable Vars
	
	/** Should we make the pool from existing Suckable assets on the scene or spawn them ourselves */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Suck")
	bool MakePoolFromExistingSuckables = false;
	/** Actor spawn Buffer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Suck|Amount", meta = (EditCondition="!MakePoolFromExistingSuckables", ClampMin=5))
	int SpawnBuffer = 20;
	/** Amount of LIGHT Suckable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Suck|Amount", meta = (EditCondition="!MakePoolFromExistingSuckables"))
	int SuckableAmount_Light = 500;
	/** Amount of MEDIUM Suckable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Suck|Amount", meta = (EditCondition="!MakePoolFromExistingSuckables"))
	int SuckableAmount_Medium = 500;
	/** Amount of HEAVY Suckable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Suck|Amount", meta = (EditCondition="!MakePoolFromExistingSuckables"))
	int SuckableAmount_Heavy = 500;
	/** Which Classes of Suckable Props should we spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Suck", meta = (EditCondition="!MakePoolFromExistingSuckables"))
	TArray<TSubclassOf<AActor>> SuckableToSpawn;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta = (ToolTip="Array of actors contained in the Pool"))
	TArray<class AActor*> PoolActorsArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default", meta = (ToolTip="Array of classes contained in the Pool"))
	TArray<TSubclassOf<AActor>> PoolClassesArray;
	
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable)
	void InitializePoolSize();
	UFUNCTION(BlueprintNativeEvent, Blueprintable, BlueprintCallable)
	void PopulatePool();
};
