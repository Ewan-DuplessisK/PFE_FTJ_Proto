// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data_3C/PlayerFeel.h"
#include "Data_3C/CombatFeel.h"
#include "Game_Character.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class FTJ_PROTO_API AGame_Character : public ACharacter
{
	GENERATED_BODY()
	
public:
	/** Spring Arm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:
	/** Components */
	//UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	class UAimComponent_Base* AimComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	class UFTJ_ProtoDestructionComponent* DestructionComponent;

public:
	// Sets default values for this character's properties
	AGame_Character();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	ECollisionChannel GetCollisionChannelByName(const FName& ChannelName);
	ECollisionChannel ECC_Kickable;
	ECollisionChannel ECC_Enemy;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Struct Ref
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Refs")
	FUPlayerFeel PlayerFeel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Refs")
	FUCombatFeel CombatFeel;

	// Boolean to know the player does an action for the enemy to go toward him
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player State Check")
	bool PlayerAction = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Debug Vars")
	bool WantPlayerAction = true;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Niagara")
	class UNiagaraSystem* Kick_VFX = nullptr;
	
	
	UFUNCTION(BlueprintCallable)
	void InitializeVarsWithPlayerFeelStruct();
	UFUNCTION(BlueprintCallable)
	void Kick();

	UFUNCTION(BlueprintNativeEvent)
	void KickFeedback(FVector Location);
};
