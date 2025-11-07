// Fill out your copyright notice in the Description page of Project Settings.


#include "FThisJob/Public/Enemy_Base.h"

#include "WaveManager.h"

AEnemy_Base::AEnemy_Base()
{
	PrimaryActorTick.bCanEverTick = true;
}
	
void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
	
void AEnemy_Base::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy_Base::SetInUse_Implementation(bool InUse)
{
	if (InUse){
		StartTimers();
	}
	else{
		StopTimers();
	}
	
	SetActorEnableCollision(InUse);
	SetActorHiddenInGame(!InUse);
	SetActorTickEnabled(InUse);
}

void AEnemy_Base::Kicked_Implementation(FVector LaunchVector, FVector PlayerPosition)
{
}

void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Base::StopTimers()
{
	MoveTimerHandle.Invalidate();
	AttackTimerHandle.Invalidate();
}

void AEnemy_Base::StartTimers()
{
	//GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle,this,UpdatePosition(),MovementRefreshRate,true);
	//GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle,this,ChooseMove(),Attack_GuardRefreshRate,true);
}

void AEnemy_Base::UpdatePosition()
{
	
}

void AEnemy_Base::ChooseMove()
{
	
}