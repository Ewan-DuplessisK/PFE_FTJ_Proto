// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAggroTypeEnum.h"
#include "GameFramework/Character.h"
#include "EnemyStateEnum.h"
#include "Enemy_Base.generated.h"

UCLASS()
class FTJ_PROTO_API AEnemy_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class AAIManager* aiManagerRef;

	UFUNCTION(BlueprintCallable)
	void Damaged(float damage, FVector Force);
	
	FVector launchForce = {2500.0f, 0.0f, 0.0f};
	
	UFUNCTION(BlueprintCallable)
	void Launched(FVector Force);
	
	void Landed(const FHitResult& hit) override;
	

	// Enemy Variables for DataTable
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	float WalkSpeed = 0.f;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	float RunSpeed = 0.f;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	int MaxHealth = 0;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	float AttackDistanceRange = 0.f;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	int CQCDamages = 0;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	float CQCInvincibilityTime = 0.f;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	int DistanceDamages = 0;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	float DistanceInvincibilityTime = 0.f;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	int QTEInputRequired = 0.f;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	float TimeAFKAfterQTE = 0.f;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Datatable Variables")
	float CQC_Range = 0.f;
	

// --------------------------------------------------------
	
	// Enemy Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Define the Enemy State"))
	EEnemyType EnemyState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Define the Enemy State"))
	EAggroType AggroType;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Variables")
	bool IsAttacking = false;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Variables")
	bool isLaunched = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables")
	bool AttackCanDash = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Variables")
	int CurrentHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Integer where we save the new enemy HP value after he get hit by the player"))
	float CQCAttackAnimationTime = 2.f ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Size of the Player Detection Sphere for cqc attack"))
	float PlayerAttackSphereSize = 125.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Variables", meta = (ToolTip = "Collision box for the enemy to detext thep layer in range for attacking"))
	class USphereComponent* PlayerInRangeSphere;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Get the position of the second enemy this enemy is supposed to talk to, for him to look at him"))
	FVector TalkingToPosition = {0, 0, 0};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "When the player exit the QTE, the direction and force the enemy will be launch"))
	FVector LaunchVelocity = {0, 0, 0};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "The reference to the enemy this enemy is supposed to talk, don't forget to change the enemy state to talking"))
	AActor* TalkingTo = nullptr;
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Variables")
	AActor* Player = nullptr;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Variables")
	AActor* AIManager = nullptr;

// -----------------------------------------------------

	// Enum Bool Variables
	UPROPERTY(BlueprintReadWrite, Category="Enemy|Enum Bool")
	bool E_Patrol = false;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Enum Bool")
	bool E_Chase = false;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Enum Bool")
	bool E_Talk = false;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Enum Bool")
	bool E_Sit = false;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Enum Bool")
	bool E_AFK = false;

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Debug")
	bool AggroActivate = false;

// -----------------------------------------------------

	// Behavior Tree Bool Name Variables
	UPROPERTY(BlueprintReadWrite, Category="Enemy|BehaviorTree")
	FName playerInAttackRangeKey = "playerInAttackRange?";

	UPROPERTY(BlueprintReadWrite, Category="Enemy|BehaviorTree")
	FName PlayerDashAttackRangeKey = "playerDashAttackRange?";

	UPROPERTY(BlueprintReadWrite, Category="Enemy|BehaviorTree")
	FName playerInDistanceAttackRangeKey = "playerInDistanceAttackRange?";

	UPROPERTY(BlueprintReadWrite, Category="Enemy|BehaviorTree")
	FName playerActionKey = "playerAction?";
	
	UPROPERTY(BlueprintReadWrite, Category="Enemy|BehaviorTree")
	FName hasSeenPlayerKey = "hasSeenPlayer?";
};
