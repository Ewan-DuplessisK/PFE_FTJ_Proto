// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPool_Component.h"

#include "PooledActor_Component.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UObjectPool_Component::UObjectPool_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UObjectPool_Component::BeginPlay()
{
	Super::BeginPlay();
	
	InitPool();
}

// Called every frame
void UObjectPool_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UObjectPool_Component::InitPool()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	int amount = 25;
	AActor* TempActor = nullptr;
	UPooledActor_Component* TempPooledComponent = nullptr;
	
	//Spawn Parameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = nullptr;
	SpawnParams.Instigator = nullptr;
	//SpawnParams.OverrideLevel = GetWorld()->PersistentLevel;
	
	for (const TSubclassOf<AActor>& actorClass : PooledActorClass)
	{
		if (!actorClass)
		{
			continue;
		}
		
		if (actorClass->GetName().Contains("Heavy", ESearchCase::IgnoreCase, ESearchDir::FromEnd))
		{
			amount = Amount_Heavy;
		}
		else if (actorClass->GetName().Contains("Medium", ESearchCase::IgnoreCase, ESearchDir::FromEnd))
		{
			amount = Amount_Medium;
		}
		else
		{
			amount = Amount_Light;
		}
		
		for (int i = 0; i < amount; ++i)
		{
			TempActor = World->SpawnActor<AActor>(actorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
			if (!IsValid(TempActor))
			{
				continue;
			}
			
			TempPooledComponent = TempActor->FindComponentByClass<UPooledActor_Component>();
			if (!TempPooledComponent)
			{
				if (debugActive)
				{
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Actor Destroyed: doesn't contain Required Component in ObjectPool CPP"));
					}
				}
				
				TempActor->Destroy();
				TempActor = nullptr;
				TempPooledComponent = nullptr;
			}
			else
			{
				ObjectPool.AddUnique(TempActor);
				
				TempPooledComponent->SetInUse(false);
			}
		}
	}
	if (debugActive)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, "Pool Init");
	}
}

AActor* UObjectPool_Component::FindAvailableActor(TSubclassOf<AActor> inActor)
{
	if (!inActor)
	{
		return nullptr;
	}
	
	for (int32 i = ObjectPool.Num() - 1; i >= 0; --i)
	{
		AActor* Actor = ObjectPool[i];
		if (!IsValid(Actor))
		{
			ObjectPool.RemoveAtSwap(i);
			continue;
		}
		
		if (!Actor->IsA(inActor))
		{
			continue;
		}
		
		UPooledActor_Component* PooledComponent = Actor->FindComponentByClass<UPooledActor_Component>();
		if (!IsValid(PooledComponent))
		{
			continue;
		}
		
		if (!PooledComponent->GetInUse())
		{
			return Actor;
		}
	}
	
	return nullptr;
}

AActor* UObjectPool_Component::SpawnFromPool(FTransform spawnTransform, TSubclassOf<AActor> inActor)
{
	UWorld* World = GetWorld();
	if (!World || !inActor)
	{
		return nullptr;
	}
	
	AActor* outActor = FindAvailableActor(inActor);
	if (!IsValid(outActor))
	{
		/** Spawning Missing Actor */
		if (shouldSpawnMissingActor)
		{
			if (debugActive)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Orange, TEXT("Spawning missing Actor"));
				}
			}
			
			//Spawn Parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Owner = nullptr;
			SpawnParams.Instigator = nullptr;
			
			AActor* TempActor = World->SpawnActor<AActor>(inActor, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
			UPooledActor_Component* TempPooledComponent = IsValid(TempActor) ? TempActor->FindComponentByClass<UPooledActor_Component>() : nullptr;
			if (!IsValid(TempActor) || !TempPooledComponent)
			{
				if (debugActive)
				{
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Actor Destroyed: doesn't contain Required Component in Spawn Missing Actor in Object Pool CPP"));
					}
				}
				
				if (IsValid(TempActor))
				{
					TempActor->Destroy();
				}
				TempActor = nullptr;
			}
			else
			{
				outActor = TempActor;
				
			}
		} /** End of spawn missing Actor */
		else
		{
			if (debugActive)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Spawn Invalid Out Actor"));
				}
			}
		}
	}
	
	if (!IsValid(outActor))
	{
		return nullptr;
	}
	
	UPooledActor_Component* PooledComponent = outActor->FindComponentByClass<UPooledActor_Component>();
	if (!IsValid(PooledComponent))
	{
		if (debugActive && GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("SpawnFromPool failed: Actor missing UPooledActor_Component"));
		}
		return nullptr;
	}

	ObjectPool.Remove(outActor);
	ActiveActors.AddUnique(outActor);

	PooledComponent->bIsBeingActivated = true;

	outActor->SetActorTransform(spawnTransform);
	outActor->RegisterAllComponents();
	PooledComponent->SetInUse(true);

	PooledComponent->bIsBeingActivated = false;
		
		
	/*UWorld* ActorWorld = outActor->GetWorld();
	UWorld* CurrentWorld = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetWorld();

	UE_LOG(LogTemp, Warning, TEXT("Actor world: %s | Current world: %s"),*ActorWorld->GetName(), *CurrentWorld->GetName());

	ULevel* ActorLevel = outActor->GetLevel();
	bool bIsVisible = ActorLevel && ActorLevel->bIsVisible;
	bool bIsHidden = outActor->IsHidden();
	//bool bIsLoaded  = ActorLevel && ActorLevel.bIsLoaded;

	UE_LOG(LogTemp, Warning, TEXT("Actor level: %s | Visible: %d | Hidden: %d"), *ActorLevel->GetName(), bIsVisible,bIsHidden);*/
	PooledComponent->SetInUse(true);
	return outActor;
}

void UObjectPool_Component::ReturnToPool(AActor* inActor)
{
	if (!IsValid(inActor))
	{
		return;
	}
	
	ActiveActors.Remove(inActor);
	ObjectPool.AddUnique(inActor);
}
