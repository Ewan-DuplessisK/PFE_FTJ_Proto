// Fill out your copyright notice in the Description page of Project Settings.


#include "FThisJob/Public/FTJ_CharaBase.h"

// Sets default values
AFTJ_CharaBase::AFTJ_CharaBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

