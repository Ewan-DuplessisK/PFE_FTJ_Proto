// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Base.h"
#include "Game_Character.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "AIManager.h"
#include "ConstraintsManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemy_Base::AEnemy_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerInRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerInRangeSphere"));
	PlayerInRangeSphere->SetupAttachment(GetCapsuleComponent());
	PlayerInRangeSphere->InitSphereRadius(PlayerAttackSphereSize);
	PlayerInRangeSphere->Deactivate();

	PlayerDashAttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerDashAttackSphere"));
	PlayerDashAttackSphere->SetupAttachment(GetCapsuleComponent());
	PlayerDashAttackSphere->InitSphereRadius(PlayerDashAttackSphereSize);
	PlayerDashAttackSphere->Deactivate();
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
	aiManagerRef = Cast<AAIManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIManager::StaticClass()));
}

// Called every frame
void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy_Base::Damaged(float damage, FVector Force = FVector())
{
	if(Force == FVector())
	{
		Force = launchForce;
		
		UE_LOG(LogTemp, Warning, TEXT("Force fallback"));
	}
	
	CurrentHealth-=damage;
	
	//UE_LOG(LogTemp,Warning,TEXT("Enemy Hit"));
	
	if(CurrentHealth <= 0)
	{
		// 1. Set enemy to Dead State
		Tags.Add(FName("Dead"));
		
		//UE_LOG(LogTemp, Warning, TEXT("Enemy Dead"));
		
		// 2. Stop Logic
		//stop move
		AAIController* AIController = Cast<AAIController>(Controller);
		if (IsValid(AIController))
		{
			if(IsValid(AIController->GetBrainComponent()))
			{
				AIController->GetBrainComponent()->StopLogic(TEXT("Dead"));
			}
		}
	}
	
	Launched(Force);
}

void AEnemy_Base::Launched(FVector Force)
{
	LaunchCharacter(Force, true, true);
	isLaunched=true;
	//UE_LOG(LogTemp, Warning, TEXT("Enemy Launched"));
}

void AEnemy_Base::Landed(const FHitResult& hit)
{
	Super::Landed(hit);
	
	if (CurrentHealth <= 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Enemy Landed"));
	
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlayerInRangeSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		GetMesh()->SetSimulatePhysics(true);
	}
	
	isLaunched=false;
}
