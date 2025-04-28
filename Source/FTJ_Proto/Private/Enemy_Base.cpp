// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Base.h"
#include "Game_Character.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
AEnemy_Base::AEnemy_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerInRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerInRangeSphere"));
	PlayerInRangeSphere->SetupAttachment(GetCapsuleComponent());
	//PlayerInRangeSphere->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	PlayerInRangeSphere->InitSphereRadius(PlayerAttackSphereSize);
	PlayerInRangeSphere->Deactivate();

	PlayerInRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_Base::OnPlayerInRangeBeginOverlap);
	
	PlayerInRangeSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy_Base::OnPlayerOutOfRange);
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
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
		IsAttacking = true;
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
			{
				BlackboardComp->SetValueAsBool(PlayerInAttackRangeKey, true);
			}
		}
	}
}

void AEnemy_Base::OnPlayerOutOfRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(AGame_Character::StaticClass()))
	{
		IsAttacking = false;
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
			{
				BlackboardComp->SetValueAsBool(PlayerInAttackRangeKey, false);
			}
		}
	}
}

// void AEnemy_Base::Launched(FVector Force)
// {
// 	AController* Controller = GetController();
//
// 	if (Controller)
// 	{
// 		// 2. Stop Logic
// 		if (Controller->IsA(AAIController::StaticClass()))
// 		{
// 			AAIController* AIController = Cast<AAIController>(Controller);
// 			if (AIController)
// 			{
// 				FAIRequestID RequestID = AIController->GetBrainComponent() ? AIController->GetBrainComponent()->StopLogic(TEXT("Dead")) : FAIRequestID::InvalidRequest;
// 			}
// 		}
// 	}
// 	
// 	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
// 	Tags.Add(FName("Dead"));
// 	LaunchCharacter(Force, true, true);
// }


