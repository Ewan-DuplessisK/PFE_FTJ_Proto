// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolingManager.h"

#include "Enemy_Base.h"
#include "WaveManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APoolingManager::APoolingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APoolingManager::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle DelayBeginPlay;
	//GetWorldTimerManager().SetTimer(DelayBeginPlay, this, ,&InitializePoolSize, 0.f, false);
}

void APoolingManager::AddTempToPool(TArray<TSubclassOf<AEnemy_Base>> EnemiesClasses, TArray<class AEnemy_Base*> SpawnedEnemies)
{
	for (int i = 0; i < EnemiesClasses.Num(); i++)
	{
		//Pool.Add(EnemiesClasses[i], SpawnedEnemies);
		Pool.FindOrAdd(EnemiesClasses[i], SpawnedEnemies);
	}
}

void APoolingManager::InitializePoolSize_Implementation()
{
	/*TArray<AActor*>OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveManager::StaticClass(), OutActors);
	for (AWaveManager manager: OutActors)
	{
		for (auto wave : manager.waves)
		{
			for (auto type : wave.typemap)
			{
				if (!PoolSizeMap.Find(type))
				{
					PoolSizeMap.Add(type,wave.typemap[type]);
				}
				else
				{
					PoolSizeMap[type]=std::max(PoolSizeMap[type],wave.typemap[type]);
				}
			}
		}
	}*/
	
	//FTimerHandle DelayPoolSpawn;
	//GetWorldTimerManager().SetTimer(DelayPoolSpawn, this, &PopulatePool, 0.f, false);
}

void APoolingManager::PopulatePool_Implementation()
{
	//FRotator TmpRota = FRotator::ZeroRotator;
	
	/*for (TPair<TSubclassOf<AEnemy_Base>, int> Pair:PoolSizeMap)
	{
		if (!Pool.Find(Pair.Key))
		{
			Pool.Add(Pair.Key, TArray<AEnemy_Base*>());
		}
		
		for (int i = 0; i < Pair.Value; i++)
		{
			Pool[Pair.Key].Add(Cast<AEnemy_Base>(GetWorld()->SpawnActor(Pair.Key, &PoolSpawnPosition, &TmpRota)));
			
			Pool[Pair.Key].Last()->SetActorEnableCollision(false);
			Pool[Pair.Key].Last()->SetActorHiddenInGame(true);
			Pool[Pair.Key].Last()->SetActorTickEnabled(false);
		}
	}*/
}

// Called every frame
void APoolingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APoolingManager::HandOverActor_Implementation(AEnemy_Base* Actor)
{
	if (Pool.Find(Actor->GetClass()))
	{
		Pool.Find(Actor->GetClass())->Add(Actor);
		Actor->SetInUse(false);
		Actor->SetActorLocation(PoolSpawnPosition);
		
		return true;
	}
	return false;
}

FPoolRequestResponce APoolingManager::PooledActorRequest_Implementation(TSubclassOf<AEnemy_Base> Class, int Num)
{
	if (Pool.Find(Class))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Success : Enemy Request | Pool.Find(Class)"));
		
		if (Pool.Find(Class)->Num() >= Num)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Success : Enemy Request | Pool.Find(Class)->Num() >= Num"));
			
			FPoolRequestResponce Response{true, "Success", {}};
			for (int i = 0; i < Num; i++)
			{
				Response.EnemyPointers.Add(Pool.Find(Class)->Pop());
				//Response.EnemyPointers.Last()->SetInUse(true);
			}
			
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Response : Enemy Request"));
			
			return Response;
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("FAIL : Enemy Request | Pool.Find(Class)->Num() >= Num"));
			
			UE_LOG(LogTemp, Log, TEXT("Pool does not have enough actors of class %s (requested %d, available %d)"), *Class->GetName(), Num, Pool.Find(Class)->Num());
			return FPoolRequestResponce{false,"Fail: Pool does not have enough actors of requested class",{}};
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FAIL : Enemy Request | Pool.Find(Class)"));
		
		UE_LOG(LogTemp, Log, TEXT("Requested class %s does not exist in Pool!"), *Class->GetName());
		return FPoolRequestResponce{false,"Fail: Requested class does not exist in Pool",{}};
	}
}
