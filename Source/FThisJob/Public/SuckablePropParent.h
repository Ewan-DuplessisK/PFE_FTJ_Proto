// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AkComponent.h"
#include "AkComponent.h"
#include "GameFramework/Actor.h"
#include "SuckablePropParent.generated.h"

UENUM(BlueprintType)
enum ESuckableType
{
	Light UMETA(DisplayName=Light),
	Medium UMETA(DisplayName=Medium),
	Heavy UMETA(DisplayName=Heavy),
	AOE UMETA(DisplayName=AOE),
	Extinguisher UMETA(DisplayName=Extinguisher),
	MAX UMETA(Hidden)
};

UCLASS()
class FTHISJOB_API ASuckablePropParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuckablePropParent();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UPooledActor_Component* PooledActor_Component;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* TrailComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UFTJ_Prop_PhysicsReactingCompBase* PropPhysicsReactingComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* LoadingOverlapComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* HoldingActor = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool EnemyAttack = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool Asleep = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FTimerHandle SleepHandle;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,meta=(Units="CentimetersPerSecond"))
	float SleepVelocity = 5.0f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanHitOnce = true;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool DamageEnabled = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMesh *Mesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Health = 2;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	int BaseHealth = 2;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	class UNiagaraSystem* DestructionVFX;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	int ScoreOnDestruction = 1;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float MultiplierOnDestruction = 0.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FText MessageOnDestruction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float Damage = 1.f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float DamageToBreakable = 1.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TEnumAsByte<ESuckableType> PropClass = Light;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	uint8 SoundType;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PlaceToWorld(FTransform Transform);

	UFUNCTION(BlueprintCallable)
	void SetHoldingActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void WakeUp();

	UFUNCTION(BlueprintCallable)
	void WaitSleep();

	UFUNCTION(BlueprintCallable)
	void Sleep();

	UFUNCTION(BlueprintCallable)
	bool SetReadyToShoot();

	UFUNCTION(BlueprintCallable)
	bool SetReadyToShootAsEnemy();

	bool SetReadyToShootHelper();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void ActivateTrail();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnSetReadyToShoot();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void LooseDurability();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void DeactivateAndStash(FVector Location);
	
	/** Ground Check */
protected:
	// Debug
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
	bool bIsDebug = false;
	UPROPERTY(VisibleInstanceOnly)
	UMaterialInterface* redMaterial = nullptr;
	UPROPERTY(VisibleInstanceOnly)
	UMaterialInterface* greenMaterial = nullptr;
	
	// Timer
	FTimerHandle GroundCheckTimerHandle;
	
	// Interval in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GroundCheck")
	float GroundCheckInterval = 0.3f;
	// Trace distance downward (adjust to your capsule half-height + offset)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GroundCheck")
	float GroundTraceDistance = 75.0f;
	
	// NO TOUCHING
	void GroundCheckTick();
	void checkOnStartForGround();
	bool hasStarted = false;

	void WakeUpFromAbove();
};
