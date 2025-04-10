// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"Data_3C/CombatFeel.h"
#include"Data_3C/AimAssistFeel.h"
#include "Player_Controller.h"
#include "AimComponent_Base.generated.h"


//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS(Blueprintable)
class FTJ_PROTO_API UAimComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimComponent_Base();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ExecuteSystem();

private:
	void PawnSearch(bool &bPawnFound, FVector2d &InLocation, bool &bDoesImplementInterface, FVector2d &BaseSpotLocation, FVector2d &WeaksotLocation);
	FVector2d SetCrosshairLocation(bool bPawnFound, FVector2d InLocation, bool bDoesImplementInterface, FVector2d BaseSpotLocation, FVector2d WeaksotLocation);
	FVector2d GetCrosshairLocation();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Struct Ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUCombatFeel CombatFeel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUAimAssistFeel AimFeel;

private:
	float TempHorizCamSpeed = 0.0f;
	float TempVertCamSpeed = 0.0f;

	 TArray<FHitResult> HitPawns;
	TArray<float> HitPawnsDistToCenter;
	FVector2d CrosshairScreenLocation = {0, 0};
	//EAimingSysState currentState;

	// Refs
	class APlayer_Controller* playerControler;

	
protected:
	// Timer
	// You should keep the timer handle in one of your properties
	FTimerHandle MyTimerHandle;
};
