// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "GameFramework/Actor.h"
#include "AIManager.generated.h"

UCLASS()
class FTJ_PROTO_API AAIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void NotifyInRange(AEnemy_Base* Enemy);

	UFUNCTION(BlueprintCallable)
	void NotifyOutOfRange(AEnemy_Base* Enemy);

	UFUNCTION(BlueprintCallable)
	void UpdateActorOnScene();

	UPROPERTY(BlueprintReadWrite, Category="Enemy|Variables", meta = (ToolTip = "[Don't Touch] Reference to the Player"))
	class AGame_Character* Player = nullptr;

	// Array of Sitting and Talking Enemy for GD to know who are in this State
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIManager|Variables")
	TArray<AEnemy_Base*> EnemySitting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIManager|Variables")
	TArray<AEnemy_Base*> EnemyTalking;
	
	UPROPERTY(BlueprintReadOnly, Category = "AIManager|Variables")
	TArray<AActor*> EnemyOnScene;

	UPROPERTY(BlueprintReadOnly, Category = "AIManager|Variables")
	TArray<AEnemy_Base*> EnemyInRange;

	UPROPERTY(BlueprintReadWrite, Category="AIManager|Variables|BehaviorTree", meta = (ToolTip = "Name to focus on the good boolean in the behaviortree"))
	FName PlayerActionKey = "playerAction?";

	void ActivatePlayerInRangeBox();

	UFUNCTION()
	void TriggerWithKick();
	
	UFUNCTION(BlueprintCallable)
	void TriggerWithSpotted();
	
	// Regulate enemy attacks
	UPROPERTY(BlueprintReadWrite, Category="AIManager|Variables|Control", meta=(ToolTip = "Amount of enemies that can attack the player at once"))
	int amountEnemyAttack = 3;
	
	UPROPERTY(BlueprintReadWrite, Category="AIManager|Variables|Control", meta=(ToolTip = "Can enemy attack player"))
	bool bCanAttack = true;
};
