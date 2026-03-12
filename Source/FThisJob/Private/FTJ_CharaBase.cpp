// Fill out your copyright notice in the Description page of Project Settings.


#include "FThisJob/Public/FTJ_CharaBase.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFTJ_CharaBase::AFTJ_CharaBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFTJ_CharaBase::RemoveHealth_Implementation(float Damage, AActor* EnemyRef)
{
	//IHealthInterface::RemoveHealth_Implementation(Damage, EnemyRef);
	CurrentHealth = UKismetMathLibrary::FClamp(CurrentHealth-Damage,0.f,MaxHealth);
	if (CurrentHealth<=0.f)
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		Destroy();
	}));
	}
}

void AFTJ_CharaBase::AddHealth_Implementation(float Amount)
{
	//IHealthInterface::AddHealth_Implementation(Amount);
	CurrentHealth = UKismetMathLibrary::FClamp(CurrentHealth+Amount,0.f,MaxHealth);
}

void AFTJ_CharaBase::GetHit_Implementation(float Damage, float HitStunDuration, FVector KnockbackVector, float InvincibilityTime,AActor* SourceActor)
{
	//IHitInterface::GetHit_Implementation(Damage, HitStunDuration, KnockbackVector, InvincibilityTime,SourceActor);
}


// Called when the game starts or when spawned
void AFTJ_CharaBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFTJ_CharaBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFTJ_CharaBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

