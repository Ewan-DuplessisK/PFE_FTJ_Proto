// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "Data_3C/PlayerFeel.h"
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
	
	// Sets default values for this character's properties
	AGame_Character();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Struct Ref
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FUPlayerFeel PlayerFeel;
};
