// Fill out your copyright notice in the Description page of Project Settings.


#include "FThisJob/Public/PlayerCharacter_Base.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Enemy_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter_Base::APlayerCharacter_Base()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(25.f,2.f,70.f));
	SpringArm->TargetArmLength = 0.f;
	
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(SpringArm);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f)); // Position the camera
	FirstPersonCameraComponent->SetRelativeRotation(FRotator(-22.f,0.f,0.f));
	FirstPersonCameraComponent->bUsePawnControlRotation=false;
	
	// Set Mesh
	GetMesh()->SetRelativeLocation(FVector(0.f,0.f,-90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f,-90.f,0.f));

	// Aim Component
	//-AimComponent = CreateDefaultSubobject<UAimComponent_Base>(TEXT("AC_AimAssist"));

}

void APlayerCharacter_Base::WidgetVisibility_Implementation()
{
}

// Called when the game starts or when spawned
void APlayerCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(CurrentCooldown>0.f)CurrentCooldown-=DeltaTime;
}

// Called to bind functionality to input
void APlayerCharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/*void APlayerCharacter_Base::Kick()
{
	if(CurrentCooldown<=0.f && CanKick)
	{
		CurrentCooldown=KickCooldown;
		
		FVector Start = GetActorLocation();
		FVector End = GetActorLocation() + (FirstPersonCameraComponent->GetForwardVector() * CombatFeel.KickLength);
		AActor* HitEnemy = nullptr;
		
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		//*ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));
		//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));
	
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Emplace(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
		TArray<FHitResult> HitPawns;
	
		if(UKismetSystemLibrary::SphereTraceMultiForObjects(
			GetWorld(), Start, End, 20, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, HitPawns, false))
		{
			//*UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Kick_VFX, HitPawns[0].Location);
			UE_LOG(LogTemp,Warning,TEXT("%s"),*HitPawns[0].GetActor()->GetName());
			HitEnemy = HitPawns[0].GetActor();
			
			if(UKismetMathLibrary::ClassIsChildOf(HitPawns[0].GetActor()->GetClass(), AEnemy_Base::StaticClass()))
			{
				AEnemy_Base* enemy = Cast<AEnemy_Base>(HitPawns[0].GetActor());
				//enemy->Launched(GetActorRotation().RotateVector(CombatFeel.KickForce));
				//*enemy->Damaged(damage, GetActorRotation().RotateVector(CombatFeel.KickForce));
				HitEnemy = enemy;
				KickHit(HitPawns[0].Location,enemy);
				
			}
			/*
			 *
			else if(UKismetMathLibrary::ClassIsChildOf(HitPawns[0].GetActor()->GetClass(), AVending_Base::StaticClass()))
			{
				AVending_Base* vending = Cast<AVending_Base>(HitPawns[0].GetActor());
				vending->IsKicked();
			}
			*
			
			KickFeedback(HitPawns[0].Location, HitEnemy);
		}else
		{
			KickFeedback(End, HitEnemy);
		}
	}
}*/

void APlayerCharacter_Base::KickHit_Implementation(FVector Location, AActor* HitActor)
{
}

/*void APlayerCharacter_Base::KickFeedback_Implementation(FVector Location, AActor* HitEnemy)
{
}*/
