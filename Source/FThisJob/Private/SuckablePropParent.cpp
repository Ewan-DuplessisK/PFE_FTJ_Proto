// Fill out your copyright notice in the Description page of Project Settings.
#include "SuckablePropParent.h"

#include "NiagaraComponent.h"
#include "PooledActor_Component.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Prop/FTJ_Prop_PhysicsReactingCompBase.h"

// Sets default values
ASuckablePropParent::ASuckablePropParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuckableMesh"));
	RootComponent = StaticMeshComp;
	StaticMeshComp->CanCharacterStepUpOn = ECB_No;
	StaticMeshComp->SetGenerateOverlapEvents(true);
	StaticMeshComp->SetNotifyRigidBodyCollision(true); //Simulation Generate Hit Event in BP
	StaticMeshComp->SetCollisionProfileName("SleepingProp",false);
	
	LoadingOverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("LoadingOverlap"));
	LoadingOverlapComp->SetupAttachment(StaticMeshComp);
	LoadingOverlapComp->SetSphereRadius(5.f);
	LoadingOverlapComp->SetCollisionProfileName("PropLoad");
	
	TrailComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail Component"));
	TrailComp->SetupAttachment(StaticMeshComp);
	TrailComp->SetAutoActivate(false);

	PooledActor_Component = CreateDefaultSubobject<UPooledActor_Component>(TEXT("PooledActorComp"));
	
	PropPhysicsReactingComp = CreateDefaultSubobject<UFTJ_Prop_PhysicsReactingCompBase>(TEXT("PropPhysicsReactingComp"));
	
	
	if (bIsDebug)
	{
		/*FString redMaterialName = "D:/Epic/UE_5.6/UE_5.6/Engine/Content/EngineDebugMaterials/MAT_LevelColorationLitLightmapUV.MAT_LevelColorationLitLightmapUV";
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> redMaterialAsset(*redMaterialName);*/
		redMaterial = StaticMeshComp->GetMaterial(0);
		
		FString greenMaterialName = "/Game/Materials/Prototyping/Materials/MI_Green.MI_Green";
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> greenMaterialAsset(*greenMaterialName);
		greenMaterial = greenMaterialAsset.Object;
	}

	//SetIsSpatiallyLoaded(false);
	bAlwaysRelevant = true;
	bNetUseOwnerRelevancy = false;
}

// Called when the game starts or when spawned
void ASuckablePropParent::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComp->SetStaticMesh(Mesh);
	TrailComp->Deactivate();
	
	GetWorldTimerManager().SetTimer(
		GroundCheckTimerHandle,
		this,
		&ASuckablePropParent::checkOnStartForGround,
		GroundCheckInterval,
		false
	);
	
	/*
	GetWorldTimerManager().SetTimerForNextTick([this]()
	{
		hasStarted = true;
	});
	*/
	
	Sleep();
}

void ASuckablePropParent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//FString n = GetName();
	//UE_LOG(LogTemp,Warning,TEXT("End %s"),*n);
	Super::EndPlay(EndPlayReason);
	
	SleepHandle.Invalidate();
	GroundCheckTimerHandle.Invalidate();
	
	Destroy();
}

// Called every frame
void ASuckablePropParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASuckablePropParent::PlaceToWorld(FTransform Transform)
{
	SetActorTransform(Transform,false,{},ETeleportType::None);
}

void ASuckablePropParent::SetHoldingActor(AActor* Actor)
{
	if (IsValid(Actor))
	{
		HoldingActor = Actor;
        	if (Actor != UGameplayStatics::GetPlayerPawn(GetWorld(),0))
        	{
        		EnemyAttack = true;
        	}
	}
	
}

void ASuckablePropParent::WakeUp()
{
	if (Asleep)
	{
		Asleep = false;
		
		StaticMeshComp->SetCollisionProfileName("FTJPhysicsReacting",true);
		SetActorTickEnabled(true);
		StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		StaticMeshComp->SetSimulatePhysics(true);

		/*Set Mat*/
		if (bIsDebug)
		{
			StaticMeshComp->SetMaterial(0, greenMaterial);
		}
		/*End Set Mat*/
		
		if (hasStarted)
		{
			TWeakObjectPtr<ASuckablePropParent> WeakThis(this);

			GetWorld()->GetTimerManager().SetTimerForNextTick([WeakThis]()
			{
				if (WeakThis.IsValid())
				{
					WeakThis->GroundCheckTick();
				}
			});
		}
		else
		{
			if (bIsDebug)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Orange, TEXT("Not Started"));
				}
			}
		}
		
		if (!SleepHandle.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(SleepHandle, this, &ASuckablePropParent::WaitSleep, .5f, true);
		}
	}
}

void ASuckablePropParent::WaitSleep()
{
	if (IsValid(this))
	{
		if (this->GetName().Contains("SuckableProp",ESearchCase::IgnoreCase,ESearchDir::FromStart) && IsValid(StaticMeshComp) && StaticMeshComp->GetComponentVelocity().Length()<SleepVelocity && !EnemyAttack)
		{
			Sleep();
		}
	}
}

void ASuckablePropParent::Sleep()
{
	if (IsValid(this) && this->IsA(ASuckablePropParent::StaticClass()) && this->GetName().Contains("SuckableProp",ESearchCase::IgnoreCase,ESearchDir::FromStart))
	{
		Asleep = true;
		
		/*Set Mat*/
		if (bIsDebug)
		{
			StaticMeshComp->SetMaterial(0, redMaterial);
		}
		/*End Set Mat*/
		
		SetActorTickEnabled(false);
        StaticMeshComp->SetSimulatePhysics(false);
		
        SleepHandle.Invalidate();
		GroundCheckTimerHandle.Invalidate();
		
        StaticMeshComp->SetCollisionProfileName("SleepingProp",true);
		FName matName = FName("SleepingProp");

		EnemyAttack = false;
		HoldingActor = nullptr;
	}
}

bool ASuckablePropParent::SetReadyToShoot()
{
	WakeUp();
	return SetReadyToShootHelper();
}

bool ASuckablePropParent::SetReadyToShootAsEnemy(){
	WakeUp();
	EnemyAttack = true;
	StaticMeshComp->SetCollisionObjectType(ECC_GameTraceChannel16);
	return SetReadyToShootHelper();
}

bool ASuckablePropParent::SetReadyToShootHelper(){
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	StaticMeshComp->SetSimulatePhysics(true);
	bCanHitOnce = true;
	DamageEnabled = true;
	ActivateTrail();
	OnSetReadyToShoot();
	return true;
}

void ASuckablePropParent::DeactivateAndStash_Implementation(FVector Location)
{
	if (IsValid(this))
	{
		Sleep();
		
		FTransform T;
		T.SetLocation(Location);
		T.SetRotation({});
		T.SetScale3D({0.01f,0.01f,0.01f});
		SetActorTransform(T);
	}
}

void ASuckablePropParent::GroundCheckTick()
{
	UWorld* World = GetWorld();
	if (!World) return;
	
	const FVector Start = GetActorLocation();
	const FVector End = Start + FVector(0.0f, 0.0f, GroundTraceDistance);
	
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // --- ACTORS TO IGNORE HERE (make an array of actors to ignore, then add them) ---
	
	const bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	/*
		TArray<FHitResult> HitResults;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
	
		const bool bHit = World->LineTraceMultiByChannel(HitResults, Start, End, ECC_Visibility, Params);
	*/
	if (bIsDebug)
	{
		DrawDebugLine(World, Start, End, bHit ? FColor::Green : FColor::Red, false, GroundCheckInterval);
	}
	
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			if(ASuckablePropParent* Prop = Cast<ASuckablePropParent>(HitActor))
			{
				Prop->WakeUpFromAbove();
			}
		}
		else
		{
			if (bIsDebug)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Red, TEXT("Bad Actor in Prop Parent Ground Check (null HitActor)"));
				}
				UE_LOG(LogTemp, Warning, TEXT("Bad Actor in Ground Check for Prop %s: HitActor is null"), *GetName());
			}
		}
	}
	/*
		for (const FHitResult& HitResult : HitResults)
		{
			AActor* HitActor = HitResult.GetActor();
			if (!HitActor) continue;
	
			if (ASuckablePropParent* Prop = Cast<ASuckablePropParent>(HitActor))
			{
				if (Prop->Asleep)
				{
					Prop->WakeUpFromAbove();
				}
			}
		}
	*/
}

void ASuckablePropParent::checkOnStartForGround()
{
	hasStarted = true;
	/*
	if (bIsDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Blue, "Check Start True");
	}
	*/
}

void ASuckablePropParent::WakeUpFromAbove()
{
	if (bIsDebug)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Green, TEXT("Wake From Above"));
		}
	}
	WakeUp();
}

void ASuckablePropParent::LooseDurability_Implementation()
{
}

void ASuckablePropParent::OnSetReadyToShoot_Implementation()
{
}

void ASuckablePropParent::ActivateTrail_Implementation()
{
}
