// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data_3C/AimAssistFeel.h"
#include "AimState_Enum.h"
#include "AimComponent_Base.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FTJ_PROTO_API UAimComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimComponent_Base();
	
	// Fix for cam invert on aim
	UFUNCTION(BlueprintCallable)
	bool SetTempInvertCam(bool invertCam);
	bool tempInvertCam = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Collision channel 
	ECollisionChannel GetCollisionChannelByName(const FName& ChannelName);
	ECollisionChannel ECC_Enemy;
	//
	
	void ExecuteSystem();

private:
	void PawnSearch(bool &bPawnFound, FVector2D &InLocation, bool &bDoesImplementInterface, FVector2D &BaseSpotLocation, FVector2D &WeaksotLocation);
	FVector2D SetCrosshairLocation(bool bPawnFound, FVector2D InLocation, bool bDoesImplementInterface, FVector2D BaseSpotLocation, FVector2D WeaksotLocation);
	UFUNCTION(BlueprintCallable)
	FVector2D GetCrosshairLocation();
	UFUNCTION(BlueprintCallable)
	FVector GetPawnBoneLocation();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Struct Ref
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Refs")
	FUAimAssistFeel AimFeel;

private:
	// Temp cam Speed for aim reset
	float TempHorizCamSpeed = 0.0f;
	float TempVertCamSpeed = 0.0f;

	TArray<FHitResult> HitPawns;
	TArray<float> HitPawnsDistToCenter;

	float distToHit = 1.0f;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D CrosshairScreenLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector PawnHitLocation;
	
private:
	// Refs
	class APlayer_Controller* playerControler = nullptr;
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UAimState_Enum CurrentAimState = UAimState_Enum::NotEngaged;
	
protected:
	
	// Timer
	// You should keep the timer handle in one of your properties
	FTimerHandle MyTimerHandle;
	
	
	// Debug Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs|Debug", meta = (ToolTip = "Class Reference to Aiming Debug HUD"))
	TSubclassOf<AHUD> wAimDebugWidget = nullptr;
	
	// Variable to hold the widget After Creating it.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs|Debug", meta = (ToolTip = "HUD Reference of the Aiming Debug HUD"))
	AHUD* MyAimDebugMenu = nullptr;
};
