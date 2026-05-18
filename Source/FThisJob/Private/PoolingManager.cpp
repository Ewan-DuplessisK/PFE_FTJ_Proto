// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolingManager.h"

//#include "WaveManager.h"
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
	
	/*
	FTimerHandle DelayBeginHandle;
	GetWorldTimerManager().SetTimer(DelayBeginHandle, this, &APoolingManager::InitializePoolSize, 0.2f, false);
	*/
}

// Called every frame
void APoolingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FPoolRequestResponce APoolingManager::PooledActorRequest_Implementation(TSubclassOf<AActor> Class, int Num)
{
	FPoolRequestResponce Response{false, "Default", {}};
	if (!Class)
	{
		Response = {false, "Fail: Invalid class", {}};
		return Response;
	}
	
	if (Num <= 0)
	{
		Response = {true, "Success", {}};
		return Response;
	}
	
	if (PoolClassesArray.Contains(Class))
	{
		for (int32 i = PoolActorsArray.Num() - 1; i >= 0 && Response.ActorPointers.Num() < Num; --i)
		{
			AActor* Actor = PoolActorsArray[i];
			if (!IsValid(Actor))
			{
				PoolActorsArray.RemoveAtSwap(i);
				continue;
			}
			
			if (Actor->GetClass() != Class)
			{
				continue;
			}
			
			Response.ActorPointers.Add(Actor);
			PoolActorsArray.RemoveAtSwap(i);
			
			int& PoolSize = PoolSizeMap.FindOrAdd(Actor->GetClass());
			PoolSize = FMath::Max(0, PoolSize - 1);
			if (PoolSize == 0)
			{
				PoolClassesArray.Remove(Actor->GetClass());
			}
		}
		if (Response.ActorPointers.Num() == Num)
		{
			Response = {true, "Success", Response.ActorPointers};
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("FAIL : Actor Request | Pool.Find(Class)->Num() >= Num"));
			
			UE_LOG(LogTemp, Log, TEXT("Pool does not have enough actors of class %s (requested %d, available %d)"), *Class->GetName(), Num, Response.ActorPointers.Num());
			
			/*for (int i = 0; i < Pool.Find(Class)->Num(); i++)
			{
				Response.ActorPointers.Add(Pool.Find(Class)->Pop());
				//Response.ActorPointers.Last()->SetInUse(true);
			}*/
			
			Response = {false, "Not Enough Actors | Max amount added", Response.ActorPointers};
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FAIL : Actor Request | Pool.Find(Class)"));
		
		UE_LOG(LogTemp, Log, TEXT("Requested class %s does not exist in Pool!"), *Class->GetName());
		Response = {false,"Fail: Requested class does not exist in Pool",{}};
	}
	
	return Response;
	
	/*
	 *DEPRACATED
		if (Pool.Find(Class))
		{
			if (Pool.Find(Class)->Num() >= Num)
			{
				FPoolRequestResponce Response{true, "Success", {}};
				for (int i = 0; i < Num; i++)
				{
					Response.ActorPointers.Add(Pool.Find(Class)->Pop());
					//Response.ActorPointers.Last()->SetInUse(true);
				}
				
				return Response;
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("FAIL : Actor Request | Pool.Find(Class)->Num() >= Num"));
				
				UE_LOG(LogTemp, Log, TEXT("Pool does not have enough actors of class %s (requested %d, available %d)"), *Class->GetName(), Num, Pool.Find(Class)->Num());
				
				FPoolRequestResponce Response{false, "Not Enough Actors", {}};
				for (int i = 0; i < Pool.Find(Class)->Num(); i++)
				{
					Response.ActorPointers.Add(Pool.Find(Class)->Pop());
					//Response.ActorPointers.Last()->SetInUse(true);
				}
				
				return Response;
			}
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FAIL : Actor Request | Pool.Find(Class)"));
			
			UE_LOG(LogTemp, Log, TEXT("Requested class %s does not exist in Pool!"), *Class->GetName());
			return FPoolRequestResponce{false,"Fail: Requested class does not exist in Pool",{}};
		}
	*/
}

bool APoolingManager::HandOverActor_Implementation(AActor* Actor)
{
	//if (PoolActorsArray.Contains(Actor))
	if (IsValid(Actor))
	{
		const bool bWasAlreadyInPool = PoolActorsArray.Contains(Actor);
		if (!bWasAlreadyInPool)
		{
			PoolActorsArray.Add(Actor);
			PoolSizeMap[Actor->GetClass()] += 1;
		}
		PoolClassesArray.AddUnique(Actor->GetClass());
		
		Actor->SetActorLocation(GetActorLocation());
		
		return true;
	}
/*
 *DEPRACATED
	if (Pool.Find(Actor->GetClass()))
	{
		Pool.Find(Actor->GetClass())->Add(Actor);
		//Actor->SetInUse(false);
		Actor->SetActorLocation(GetActorLocation());
		
		return true;
	}
*/
	return false;
}

void APoolingManager::InitializePoolSize_Implementation()
{
	/*
	TArray<AActor*>OutActors;
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
	}
	*/
	
	//FTimerHandle DelayPoolSpawn;
	//GetWorldTimerManager().SetTimer(DelayPoolSpawn, this, &PopulatePool, 0.f, false);
}

void APoolingManager::PopulatePool_Implementation()
{
	//FRotator TempRota = FRotator::ZeroRotator;
	
	/*
	for (TPair<TSubclassOf<AEnemy_Base>, int> Pair:PoolSizeMap)
	{
		if (!Pool.Find(Pair.Key))
		{
			Pool.Add(Pair.Key, TArray<AEnemy_Base*>());
		}
		
		for (int i = 0; i < Pair.Value; i++)
		{
			Pool[Pair.Key].Add(Cast<AActor>(GetWorld()->SpawnActor(Pair.Key, &PoolSpawnPosition, &TempRota)));
			
			Pool[Pair.Key].Last()->SetActorEnableCollision(false);
			Pool[Pair.Key].Last()->SetActorHiddenInGame(true);
			Pool[Pair.Key].Last()->SetActorTickEnabled(false);
		}
	}
	*/
}
