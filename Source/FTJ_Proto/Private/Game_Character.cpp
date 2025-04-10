// Fill out your copyright notice in the Description page of Project Settings.

#include "FTJ_Proto/Public/Game_Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AGame_Character::AGame_Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
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

	GetMesh()->SetRelativeLocation(FVector(0.f,0.f,-90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f,-90.f,0.f));
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGame_Character::BeginPlay()
{
	Super::BeginPlay();

	InitializeVarsWithPlayerFeelStruct();
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
