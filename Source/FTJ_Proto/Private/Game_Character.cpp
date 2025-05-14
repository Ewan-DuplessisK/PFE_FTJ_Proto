// Fill out your copyright notice in the Description page of Project Settings.

#include "FTJ_Proto/Public/Game_Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "AimComponent_Base.h"
#include "Enemy_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Physics_Props.h"
#include "Destruction/FTJ_ProtoDestructionActor.h"
#include "Destruction/FTJ_ProtoDestructionComponent.h"
#include "Evaluation/Blending/MovieSceneBlendType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGame_Character::AGame_Character()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
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
	AimComponent = CreateDefaultSubobject<UAimComponent_Base>(TEXT("AC_AimAssist"));
	DestructionComponent = CreateDefaultSubobject<UFTJ_ProtoDestructionComponent>(TEXT("AC_Destruction"));
}

// Called when the game starts or when spawned
void AGame_Character::BeginPlay()
{
	Super::BeginPlay();

	InitializeVarsWithPlayerFeelStruct();

	// Find Kickable Trace Channel
	ECC_Kickable = GetCollisionChannelByName("Kickable");
	ECC_Enemy = GetCollisionChannelByName("Enemy");
}

// Called every frame
void AGame_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGame_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGame_Character::InitializeVarsWithPlayerFeelStruct()
{
	GetCharacterMovement()->GravityScale = PlayerFeel.Gravity;
	
	GetCharacterMovement()->MaxWalkSpeed = PlayerFeel.WalkSpeed;
	
	GetCapsuleComponent()->SetLinearDamping(PlayerFeel.LinearDamping);
	GetCapsuleComponent()->SetAngularDamping(PlayerFeel.AngularDamping);
}

ECollisionChannel AGame_Character::GetCollisionChannelByName(const FName& ChannelName)
{
	// Iterate over all possible collision channels
	for (int32 Channel = ECC_GameTraceChannel1; Channel <= ECC_GameTraceChannel18; ++Channel)
	{
		FName Name = UCollisionProfile::Get()->ReturnChannelNameFromContainerIndex(Channel);

		if (Name == ChannelName)
		{
			return static_cast<ECollisionChannel>(Channel);
		}
	}

	// Not found, log a warning & handle the error
	UE_LOG(LogTemp, Warning, TEXT("Collision channel '%s' not found!"), *ChannelName.ToString());
	return ECC_WorldStatic; // default/fallback
}

void AGame_Character::Kick()
{
	if(WantPlayerAction && !PlayerAction) PlayerAction = true;
	
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation()+(FirstPersonCameraComponent->GetForwardVector()*CombatFeel.KickLength);
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Enemy));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Emplace(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	TArray<FHitResult> HitPawns;
	
	if(UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(), Start, End, 20, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitPawns, false))
	{
		KickFeedback(HitPawns.Top().Location);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Kick_VFX, HitPawns.Top().Location);
		
		if(UKismetMathLibrary::ClassIsChildOf(HitPawns.Top().GetActor()->GetClass(), AEnemy_Base::StaticClass()))
		{
			AEnemy_Base* enemy = Cast<AEnemy_Base>(HitPawns.Top().GetActor());
			enemy->Launched(GetActorRotation().RotateVector(CombatFeel.KickForce));
		}
		else if (UKismetMathLibrary::ClassIsChildOf(HitPawns.Top().GetActor()->GetClass(), APhysics_Props::StaticClass()))
		{
			APhysics_Props* prop = Cast<APhysics_Props>(HitPawns.Top().GetActor());
			prop->Launched(GetActorRotation().RotateVector(CombatFeel.KickForce));
		}
		else if(UKismetMathLibrary::ClassIsChildOf(HitPawns.Top().GetActor()->GetClass(), AFTJ_ProtoDestructionActor::StaticClass()))
		{
			FVector force = GetActorRotation().RotateVector(CombatFeel.KickForce);
			DestructionComponent->Hit(HitPawns.Top().GetComponent(),HitPawns.Top(),100.f,0,1.f,1.f,force,FVector());
		}
	}
	KickFeedback(End);
}

void AGame_Character::KickFeedback_Implementation(FVector Location)
{
	
}
