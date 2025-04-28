// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Base.h"
#include "Game_Character.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
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
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerInRangeSphere)
	{
		PlayerInRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy_Base::OnPlayerInRangeBeginOverlap);
	}
	PlayerInRangeSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy_Base::OnPlayerOutOfRange);
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
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
			{
				BlackboardComp->SetValueAsBool(PlayerInAttackRangeKey, false);
			}
		}
	}
}


