// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FTJ_CharaBase.h"
#include "Data_3C/CameraFeel.h"
#include "Data_3C/CombatFeel.h"
#include "Data_3C/PlayerFeel.h"
#include "PlayerCharacter_Base.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class FTHISJOB_API APlayerCharacter_Base : public AFTJ_CharaBase
{
	GENERATED_BODY()

public:
	//Public functions
	
	APlayerCharacter_Base();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Public components
	
	/** Spring Arm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;


	//Public variables

	// Struct Ref
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Refs")
	FUPlayerFeel PlayerFeel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Refs")
	FUCombatFeel CombatFeel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Refs")
	FUCameraFeel CameraFeel;

	UPROPERTY(BlueprintReadWrite)
	int HitCounter;
	UPROPERTY(BlueprintReadWrite,Category="Combo",meta=(ToolTip="Delay in seconds after last puch before combo reset"))
	float ComboDecayDelay = 3.f; //in seconds

	// Debug/Cheats Menu Variables
		// Basic
	UPROPERTY(BlueprintReadWrite)
	bool HealthBarUI;
	UPROPERTY(BlueprintReadWrite)
	bool TimerUI;
		// Debug
	UPROPERTY(BlueprintReadWrite)
	bool CoolDownPunchUI;
	UPROPERTY(BlueprintReadWrite)
	bool CoolDownDesperationUI;
	UPROPERTY(BlueprintReadWrite)
	bool GamepadDebuggerUI;
	UFUNCTION(BlueprintNativeEvent)
	void WidgetVisibility();
	
protected:
	
	//Protected components
	

	//Protected functions

	virtual void BeginPlay() override;

public:
	// Kick
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Niagara")
	class UNiagaraSystem* Kick_VFX = nullptr;
	
	/*UFUNCTION(BlueprintCallable)
	void Kick();*/

	/*UFUNCTION(BlueprintNativeEvent)
	void KickFeedback(FVector Location,class AActor* HitEnemy);*/

	UFUNCTION(BlueprintNativeEvent)
	void KickHit(FVector Location,class AActor* HitActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Kick|Damage")
	float damage = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Kick|Cooldown")
	float KickCooldown = 1.0f;
	float CurrentCooldown = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Kick")
	bool CanKick = true;
};
