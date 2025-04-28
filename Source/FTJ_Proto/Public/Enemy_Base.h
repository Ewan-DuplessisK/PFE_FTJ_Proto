// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION()
	void OnPlayerInRangeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnPlayerOutOfRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void Launched(FVector Force);

	// Enemy Variables for DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Enemy WalkSpeed depending on the ABP and BlendSpace"))
	float WalkSpeed = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Enemy RunSpeed depending on the ABP and BlendSpace"))
	float RunSpeed = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Enemy max HP"))
	int MaxHealth = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Enemy Damages to player"))
	int Damages = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Enemy distance to charge on the player"))
	float ChargeDistance = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Enemy Speed charge"))
	float SpeedCharge = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Enemy range he can grab the player"))
	float GrabDistance = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Number of time you need to spam the input to exit the QTE"))
	int QTEInputRequired = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Number of time the enemy stay still after the player exit the QTE"))
	float TimeAFKAfterQTE = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Datatable Variables [Don't Touch]", meta = (ToolTip = "[Modify in DataTable] Number of time the enemy stay stun"))
	float StunDuration = 0.f;

// --------------------------------------------------------
	
	// Enemy Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Define the Enemy State"))
	EEnemyType EnemyState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Boolean to see if the enemy is attacking the player"))
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemy|Variables", meta = (ToolTip = "Boolean to see if the player is in the enemy attack range"))
	bool IsPlayerInAttackRangeBOOL = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Boolean to see if the enemy can talk"))
	bool bCanTalk = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Boolean to see if the enemy is launched"))
	bool isLaunched = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Integer where we save the new enemy HP value after he get hit by the player"))
	int CurrentHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Size of the Player Detection Sphere"))
	float PlayerAttackSphereSize = 125.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Variables", meta = (ToolTip = "Collision box for the enemy to detext thep layer in range for attacking"))
	class USphereComponent* PlayerInRangeSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Get the position of the player if he get in the range of the enemy for the attack"))
	FVector OverlapedPosition = {0, 0, 0};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "Get the position of the second enemy this enemy is supposed to talk to, for him to look at him"))
	FVector TalkingToPosition = {0, 0, 0};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "When the player exit the QTE, the direction and force the enemy will be launch"))
	FVector LaunchVelocity = {0, 0, 0};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "The reference to the enemy this enemy is supposed to talk, don't forget to change the enemy state to talking"))
	AActor* TalkingTo = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "[Don't Touch] Reference to the Player"))
	AActor* Player = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "[Don't Touch] Reference to the AIManager"))
	AActor* AIManager = nullptr;

// -----------------------------------------------------

	// Enum Bool Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Enum Bool [Don't Touch]", meta = (ToolTip = "[Don't Touch] Boolean for the enemy state"))
	bool E_Patrol = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Enum Bool [Don't Touch]", meta = (ToolTip = "[Don't Touch] Boolean for the enemy state"))
	bool E_Chase = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Enum Bool [Don't Touch]", meta = (ToolTip = "[Don't Touch] Boolean for the enemy state"))
	bool E_Talk = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Enum Bool [Don't Touch]", meta = (ToolTip = "[Don't Touch] Boolean for the enemy state"))
	bool E_Sit = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Enum Bool [Don't Touch]", meta = (ToolTip = "[Don't Touch] Boolean for the enemy state"))
	bool E_Charge = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Enum Bool [Don't Touch]", meta = (ToolTip = "[Don't Touch] Boolean for the enemy state"))
	bool E_Grab = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|Enum Bool [Don't Touch]", meta = (ToolTip = "[Don't Touch] Boolean for the enemy state"))
	bool E_Stun = false;

// -----------------------------------------------------

	// Behavior Tree Bool Name Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|BehaviorTree", meta = (ToolTip = "Name to focus on the good boolean in the behaviortree"))
	FName PlayerInAttackRangeKey = "playerInAttackRange?";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|BehaviorTree", meta = (ToolTip = "Name to focus on the good boolean in the behaviortree"))
	FName CanTalkWithOtherKey = "CanTalkWithOther?";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy|BehaviorTree", meta = (ToolTip = "Name to focus on the good boolean in the behaviortree"))
	FName hasSeenPlayerKey = "hasSeenPlayer?";
	
};
