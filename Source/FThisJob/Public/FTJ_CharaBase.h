// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FTJ_CharaBase.generated.h"

UCLASS()
class FTHISJOB_API AFTJ_CharaBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	//Public functions
	
	AFTJ_CharaBase();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Public components


	
	//Public variables

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bCanDash = true;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool isDashing = false;

	UPROPERTY(BlueprintReadWrite)
	int MaxHealth = 100;
	UPROPERTY(BlueprintReadWrite)
	int CurrentHealth = 100;

	UPROPERTY(BlueprintReadWrite, Category="")
	float WalkSpeed = 0.f;
	UPROPERTY(BlueprintReadWrite, Category="")
	float RunSpeed = 0.f;

	UPROPERTY(BlueprintReadWrite, Category="")
	int CQCDamages = 0;

	UPROPERTY(BlueprintReadWrite, Category="")
	TArray<FString>States;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

};
