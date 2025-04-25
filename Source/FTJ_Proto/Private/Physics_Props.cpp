// Fill out your copyright notice in the Description page of Project Settings.


#include "Physics_Props.h"

#include "Enemy_Base.h"
#include "Components/BoxComponent.h"

// Sets default values
APhysics_Props::APhysics_Props()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapPhysics = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapPhysics"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	OverlapPhysics->OnComponentBeginOverlap.AddDynamic(this, &APhysics_Props::OnPhysicsOverlap);

}

// Called when the game starts or when spawned
void APhysics_Props::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APhysics_Props::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhysics_Props::Launched(FVector force)
{
	isLaunched = true;
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->AddImpulse(force,"None",true);
}

void APhysics_Props::OnPhysicsOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(isLaunched&&OtherActor!=this)
	{
		if(OtherActor->GetClass() == AEnemy_Base::StaticClass())
		{
			AEnemy_Base* Enemy = Cast<AEnemy_Base>(OtherActor);
			if(!Enemy->isLaunched){/*Launched: Velocity*TransmissionFactor */}
		}
		if(OtherActor->GetClass() == APhysics_Props::StaticClass())
		{
			APhysics_Props* Prop = Cast<APhysics_Props>(OtherActor);
			if(!Prop->isLaunched)Prop->Launched(GetVelocity()*TransmissionFactor);
		}
		StaticMesh->SetAllPhysicsLinearVelocity(GetVelocity()*DampingFactor);
	}
}

