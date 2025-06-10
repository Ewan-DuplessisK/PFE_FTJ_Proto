// Fill out your copyright notice in the Description page of Project Settings.


#include "Vending_Base.h"

// Sets default values
AVending_Base::AVending_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVending_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVending_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVending_Base::IsKicked_Implementation()
{
}

