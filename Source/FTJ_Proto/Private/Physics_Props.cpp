// Fill out your copyright notice in the Description page of Project Settings.


#include "Physics_Props.h"

#include "Enemy_Base.h"
#include "Components/BoxComponent.h"
#include "Destruction/FTJ_ProtoDestructionActor.h"
#include "Destruction/FTJ_ProtoDestructionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APhysics_Props::APhysics_Props()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeLocation(FVector(0.f,0.f,0.f));
	OverlapPhysics = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapPhysics"));
	OverlapPhysics->SetupAttachment(StaticMesh);
	OverlapPhysics->SetRelativeLocation(FVector(0.f,0.f,0.f));
	OverlapPhysics->OnComponentBeginOverlap.AddDynamic(this, &APhysics_Props::OnPhysicsOverlap);
	StaticMesh->OnComponentHit.AddDynamic(this, &APhysics_Props::OnHit);

	DestructionComponent = CreateDefaultSubobject<UFTJ_ProtoDestructionComponent>(TEXT("AC_Destruction"));
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
		if(UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(),AEnemy_Base::StaticClass()))
		{
			AEnemy_Base* Enemy = Cast<AEnemy_Base>(OtherActor);
			if(!Enemy->isLaunched){Enemy->Launched(GetVelocity()*TransmissionFactor);}
		}
		if(UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(),APhysics_Props::StaticClass()))
		{
			APhysics_Props* Prop = Cast<APhysics_Props>(OtherActor);
			if(!Prop->isLaunched)Prop->Launched(GetVelocity()*TransmissionFactor);
		}
		if(UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(),AFTJ_ProtoDestructionActor::StaticClass()))
		{
			UE_LOG(LogTemp,Log,TEXT("Prop Overlap"));
			FHitResult OutHit;
			//UE_LOG(LogTemp,Log,TEXT("SweepLoc %f, %f, %f"),SweepResult.Location.X,SweepResult.Location.Y,SweepResult.Location.Z);
			if(UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),GetActorLocation(),OtherActor->GetActorLocation(),{UEngineTypes::ConvertToObjectType(ECC_Destructible)},false,{},EDrawDebugTrace::ForOneFrame,OutHit,true))
			{
				UE_LOG(LogTemp,Log,TEXT("LineHit"));
				AFTJ_ProtoDestructionActor* DActor = Cast<AFTJ_ProtoDestructionActor>(OtherActor);
				DestructionComponent->Hit(OutHit.GetComponent(),OutHit,100,0,1.f,1.f,GetVelocity()*TransmissionFactor,FVector());
			}
			/*AFTJ_ProtoDestructionActor* DActor = Cast<AFTJ_ProtoDestructionActor>(OtherActor);
			DestructionComponent->Hit(HitComp,Hit,100,0,1.f,1.f,GetVelocity()*TransmissionFactor,FVector());*/
		}
		StaticMesh->SetAllPhysicsLinearVelocity(GetVelocity()*DampingFactor);
	}
}

void APhysics_Props::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Log,TEXT("Prop OnHit"));
	if(UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(),AFTJ_ProtoDestructionActor::StaticClass()))
	{
		UE_LOG(LogTemp,Log,TEXT("Prop OnHit 2"));
		AFTJ_ProtoDestructionActor* DActor = Cast<AFTJ_ProtoDestructionActor>(OtherActor);
		DestructionComponent->Hit(HitComp,Hit,100,0,1.f,1.f,GetVelocity()*TransmissionFactor,FVector());
	}
	StaticMesh->SetAllPhysicsLinearVelocity(GetVelocity()*DampingFactor);
}

