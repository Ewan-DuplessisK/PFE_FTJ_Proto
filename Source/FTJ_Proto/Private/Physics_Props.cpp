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
	DestructionComponent = CreateDefaultSubobject<UFTJ_ProtoDestructionComponent>(TEXT("AC_Destruction"));
}

// Called when the game starts or when spawned
void APhysics_Props::BeginPlay()
{
	Super::BeginPlay();
	for(TObjectPtr<USceneComponent> Child : OverlapPhysics->GetAttachChildren())
	{
		UBoxComponent* ChildBox = Cast<UBoxComponent>(Child);
		ChildBox->OnComponentBeginOverlap.AddDynamic(this,&APhysics_Props::OnPhysicsOverlap);
	}
}

bool canLand = false;
// Called every frame
void APhysics_Props::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!canLand && GetVelocity().Length()>PropLandSpeedThreshold)canLand=true;
	if(isLaunched && canLand && GetVelocity().Length()<PropLandSpeedThreshold)
	{
		isLaunched=false;
		canLand=false;
	}
}

void APhysics_Props::Launched(FVector force)
{
	isLaunched = true;
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->AddImpulse(force,"None",true);
}

void APhysics_Props::OnPhysicsOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp,Warning,TEXT("Overlap %d"),isLaunched);
	/*if(isLaunched&&OtherActor!=this)
	{*/
		//UE_LOG(LogTemp,Warning,TEXT("Overlap %s"),*OtherActor->GetName());
		if(UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(),AEnemy_Base::StaticClass()))
		{
			AEnemy_Base* Enemy = Cast<AEnemy_Base>(OtherActor);
			if(!isLaunched&&Enemy->isLaunched)
			{
				Launched(Enemy->GetVelocity()*TransmissionFactor);
				Enemy->Damaged(Damage,FVector());
				Enemy->GetMesh()->SetAllPhysicsLinearVelocity(Enemy->GetVelocity()*DampingFactor);
			}
			if(isLaunched&&!Enemy->isLaunched)
			{
				Enemy->Damaged(Damage,GetVelocity()*TransmissionFactor);
				//Enemy->Launched(GetVelocity()*TransmissionFactor);
				StaticMesh->SetAllPhysicsLinearVelocity(GetVelocity()*DampingFactor);
			}
		}
		
		APhysics_Props* Prop = Cast<APhysics_Props>(OtherActor);
		if(IsValid(Prop) || UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(),APhysics_Props::StaticClass()))
		{
			//UE_LOG(LogTemp,Warning,TEXT("Prop Overlap"));
			if(!isLaunched)
			{
				Launched(Prop->GetVelocity()*TransmissionFactor);
				Prop->StaticMesh->SetAllPhysicsLinearVelocity(GetVelocity()*DampingFactor);
			}
		}
		
		if(UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(),AFTJ_ProtoDestructionActor::StaticClass()))
		{
			FHitResult OutHit;
			if(UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),GetActorLocation(),OtherActor->GetActorLocation(),{UEngineTypes::ConvertToObjectType(ECC_Destructible)},false,{},EDrawDebugTrace::ForOneFrame,OutHit,true))
			{
				AFTJ_ProtoDestructionActor* DActor = Cast<AFTJ_ProtoDestructionActor>(OtherActor);
				DestructionComponent->Hit(OutHit.GetComponent(),OutHit,100,0,1.f,1.f,GetVelocity()*TransmissionFactor,FVector());
			}
		}
		
	//}
}

void APhysics_Props::HitFeedBack_Implementation()
{
}

/*void APhysics_Props::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(),AFTJ_ProtoDestructionActor::StaticClass()))
	{
		AFTJ_ProtoDestructionActor* DActor = Cast<AFTJ_ProtoDestructionActor>(OtherActor);
		DestructionComponent->Hit(HitComp,Hit,100,0,1.f,1.f,GetVelocity()*TransmissionFactor,FVector());
	}
	StaticMesh->SetAllPhysicsLinearVelocity(GetVelocity()*DampingFactor);
}*/

