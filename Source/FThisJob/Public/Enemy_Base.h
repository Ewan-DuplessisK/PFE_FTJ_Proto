// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTJ_CharaBase.h"
#include "Enemy_Base.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API AEnemy_Base : public AFTJ_CharaBase
{
	GENERATED_BODY()

public:
	
	//Public functions
	
	AEnemy_Base();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetInUse(bool InUse);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Kicked(FVector LaunchVector, FVector PlayerPosition);

	UFUNCTION(BlueprintCallable)
	void StartTimers();

	UFUNCTION(BlueprintCallable)
	void StopTimers();


	//Public components


	//Public variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Refs")
	class AWaveManager* WaveManagerReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Vars")
	float MovementRefreshRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Vars")
	float Attack_GuardRefreshRate;
	
protected:

	//Protected functions

	virtual void BeginPlay() override;

	void UpdatePosition();
	void ChooseMove();

	//Protected components


	//Protected variables

	FTimerHandle MoveTimerHandle;
	FTimerHandle AttackTimerHandle;
};
