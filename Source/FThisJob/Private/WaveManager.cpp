// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveManager.h"

#include "Enemy_Base.h"
#include "PoolingManager.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWaveManager::LaunchWave_Implementation(int index)
{
	
}

bool AWaveManager::RemoveEnemyFromWaveManager_Implementation(AEnemy_Base* Enemy_To_Remove)
{
	if (IsValid(Enemy_To_Remove))
	{
		SpawnedEnemies.Remove(Enemy_To_Remove);
		
		if (PoolingManager->HandOverActor(Enemy_To_Remove))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Success : Enemy Handover | Wave --> Pool"));
			
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FAIL : Enemy Handover | Wave --> Pool"));
			
			return false;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FAIL : Invalid Enemy to remove | wave manager"));
		
		return false;
	}
}
