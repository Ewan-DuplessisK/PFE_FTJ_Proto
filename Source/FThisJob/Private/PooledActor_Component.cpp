// Fill out your copyright notice in the Description page of Project Settings.

#include "PooledActor_Component.h"

#include "ObjectPool_Component.h"
#include "SuckablePropParent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPooledActor_Component::UPooledActor_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPooledActor_Component::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	playerRef = UGameplayStatics::GetPlayerPawn(World, 0);
	if (playerRef)
	{
		poolComp = Cast<UObjectPool_Component>(playerRef->GetComponentByClass(UObjectPool_Component::StaticClass()));
	}
}

// Called every frame
void UPooledActor_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPooledActor_Component::SetInUse(bool InUse)
{
	if (bIsBeingActivated) return; // prevent re-entrant return-to-pool
	
	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
	{
		return;
	}
	
	bIsInUse = InUse;
	
	Owner->SetActorEnableCollision(bIsInUse);
	
	if(bIsInUse)
	{
		//GetOwner()->SetActorLocation({100.0, 0.0, 75.0});
		
		// RegisterAllComponents is handled by object pool SpawnFromPool

		ASuckablePropParent* obj = Cast<ASuckablePropParent>(GetOwner());
		if (IsValid(obj))obj->Health=obj->BaseHealth;
	}
	else
	{
		if(poolComp)
		{
			poolComp->ReturnToPool(Owner);
		}
		else
		{
			if (debugActive)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("INVALID OBJECT POOL COMPONENT IN POOLED ACTOR SET IN USE"));
				}
			}
		}
		
		Owner->SetActorLocation(UnusedLocation,true);
		//GetOwner()->UnregisterAllComponents();
	}
}

bool UPooledActor_Component::GetInUse()
{
	return bIsInUse;
}
