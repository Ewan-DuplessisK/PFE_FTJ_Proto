// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledActor_Component.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTHISJOB_API UPooledActor_Component : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UPooledActor_Component();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
	bool debugActive = true;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	bool bIsInUse = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	bool bIsBeingActivated = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	FVector UnusedLocation = {0.0, 0.0, -500.0};
	
	UFUNCTION(Blueprintable, BlueprintCallable, meta=(ToolTip="Sets the actor state and returns it to pool is not in use"))
	void SetInUse(bool InUse);
	
	UFUNCTION(Blueprintable, BlueprintCallable)
	bool GetInUse();
	
private:
	class APawn* playerRef = nullptr;
	class UObjectPool_Component* poolComp = nullptr;
};
