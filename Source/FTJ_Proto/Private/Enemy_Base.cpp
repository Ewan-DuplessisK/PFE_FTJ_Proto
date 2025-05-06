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

	PlayerInRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_Base::OnPlayerInRangeBeginOverlap);
	
	PlayerInRangeSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy_Base::OnPlayerOutOfRange);
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

void AEnemy_Base::OnPlayerInRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AGame_Character::StaticClass()))
	{		
		aiManagerRef->NotifyInRange(this);
		
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
			{
				BlackboardComp->SetValueAsBool(playerInAttackRangeKey, true);
			}
		}
	}
}

void AEnemy_Base::OnPlayerOutOfRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(AGame_Character::StaticClass()))
	{
		aiManagerRef->NotifyOutOfRange(this);
		
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
			{
				BlackboardComp->SetValueAsBool(playerInAttackRangeKey, false);
			}
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("PlayerOutOfRange"));
}

void AEnemy_Base::Launched(FVector Force)
{
	// 2. Stop Logic
	AAIController* AIController = Cast<AAIController>(Controller);
	if (IsValid(AIController))
	{
		if(IsValid(AIController->GetBrainComponent()))
		{
			AIController->GetBrainComponent()->StopLogic(TEXT("Dead"));
		}
	}
	LaunchCharacter(Force, true, true);
	isLaunched=true;
	//UE_LOG(LogTemp,Warning,TEXT("Enemy Launched"));
}

void AEnemy_Base::Landed(const FHitResult& hit)
{
	Super::Landed(hit);
	UE_LOG(LogTemp,Warning,TEXT("Enemy Landed"));
	
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	Tags.Add(FName("Dead"));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayerInRangeSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetSimulatePhysics(true);
	isLaunched=false;
}



