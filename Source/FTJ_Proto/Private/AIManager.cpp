// Fill out your copyright notice in the Description page of Project Settings.


#include "AIManager.h"

#include "AIController.h"
#include "Enemy_Base.h"
#include "Game_Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAIManager::AAIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIManager::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AGame_Character>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	UpdateActorOnScene();
}

// Called every frame
void AAIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Player->PlayerAction)
	{
		ActivatePlayerInRangeBox();
		for (AActor* Actor : EnemyOnScene)
		{
			AEnemy_Base* Enemy = Cast<AEnemy_Base>(Actor);
			if (Enemy)
			{
				AAIController* AIController = Cast<AAIController>(Enemy->GetController());
				if (AIController)
				{
					UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
					if (BlackboardComp)
					{
						BlackboardComp->SetValueAsBool(PlayerActionKey, true);
					}
				}
			}
		}
	}
}

void AAIManager::NotifyInRange(AEnemy_Base* Enemy)
{
	EnemyInRange.AddUnique(Enemy);
}

void AAIManager::NotifyOutOfRange(AEnemy_Base* Enemy)
{
	if(IsValid(Enemy))
	{
		EnemyInRange.Remove(Enemy);
	}
}

void AAIManager::UpdateActorOnScene()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy_Base::StaticClass(), EnemyOnScene);
}

void AAIManager::ActivatePlayerInRangeBox()
{
	for (AActor* Actor : EnemyOnScene)
	{
		AEnemy_Base* Enemy = Cast<AEnemy_Base>(Actor);
		
		if (IsValid(Enemy) && IsValid(Enemy->PlayerInRangeSphere))
		{
			Enemy->PlayerInRangeSphere->Activate();
		}
	}
}

void AAIManager::TriggerWithKick()
{
	for (AActor* Actor : EnemyOnScene)
	{
		AEnemy_Base* Enemy = Cast<AEnemy_Base>(Actor);
		if (IsValid(Enemy) && Enemy->AggroType == EAggroType::KICK)
		{
			Player->PlayerAction = true;
			Enemy->AggroActivate = true;
			
			AAIController* AIController = Cast<AAIController>(Enemy->GetController());
			if (AIController)
			{
				UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
				if (BlackboardComp)
				{
					BlackboardComp->SetValueAsBool(PlayerActionKey, true);
				}
			}
		}
	}
}

void AAIManager::TriggerWithSpotted()
{
	for (AActor* Actor : EnemyOnScene)
	{
		AEnemy_Base* Enemy = Cast<AEnemy_Base>(Actor);
		if (IsValid(Enemy) && Enemy->AggroType == EAggroType::SPOTTED)
		{
			Enemy->AggroActivate = true;
			
			AAIController* AIController = Cast<AAIController>(Enemy->GetController());
			if (AIController)
			{
				UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
				if (BlackboardComp)
				{
					BlackboardComp->SetValueAsBool(PlayerActionKey, true);
				}
			}
		}
	}
}

