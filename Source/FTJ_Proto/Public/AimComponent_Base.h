// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data_3C/CombatFeel.h"
#include "Data_3C/AimAssistFeel.h"
#include "AimState_Enum.h"
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
	void PawnSearch(bool &bPawnFound, FVector2D &InLocation, bool &bDoesImplementInterface, FVector2D &BaseSpotLocation, FVector2D &WeaksotLocation);
	FVector2D SetCrosshairLocation(bool bPawnFound, FVector2D InLocation, bool bDoesImplementInterface, FVector2D BaseSpotLocation, FVector2D WeaksotLocation);
	FVector2D GetCrosshairLocation();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Struct Ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs")
	FUCombatFeel CombatFeel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs")
	FUAimAssistFeel AimFeel;

private:
	float TempHorizCamSpeed = 0.0f;
	float TempVertCamSpeed = 0.0f;

	TArray<FHitResult> HitPawns;
	TArray<float> HitPawnsDistToCenter;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D CrosshairScreenLocation;
	
private:
	//EAimingSysState currentState;

	// Refs
	class APlayer_Controller* playerControler = nullptr;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UAimState_Enum CurrentAimState = UAimState_Enum::NotEngaged;
	
protected:
	
	// Timer
	// You should keep the timer handle in one of your properties
	FTimerHandle MyTimerHandle;
};
