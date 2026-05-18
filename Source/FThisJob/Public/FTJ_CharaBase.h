// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthInterface.h"
#include "HitInterface.h"
#include "FTJ_CharaBase.generated.h"


UCLASS()
class FTHISJOB_API AFTJ_CharaBase : public ACharacter, public IHealthInterface, public IHitInterface
{
	GENERATED_BODY()

public:
	
	//Public functions
	
	AFTJ_CharaBase();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Public components

	
	//Public variables
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Health")
	float CurrentHealth = 100.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Health")
	float MaxHealth = 100.f;
   
	// Health
	virtual void RemoveHealth_Implementation(float Damage, AActor* EnemyRef) override;
	virtual void AddHealth_Implementation(float Amount) override;
	//Hit
	virtual void GetHit_Implementation(float Damage, float HitStunDuration, FVector KnockbackVector, float InvincibilityTime,AActor* SourceActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

private:

	//deprecated vars
	UPROPERTY()
	bool bCanDash = true;
	UPROPERTY()
	bool isDashing = false;

	UPROPERTY()
	float WalkSpeed = 0.f;
	UPROPERTY()
	float RunSpeed = 0.f;

	UPROPERTY()
	int CQCDamages = 0;

	UPROPERTY()
	TArray<FString>States;
	//end deprecated vars

};
