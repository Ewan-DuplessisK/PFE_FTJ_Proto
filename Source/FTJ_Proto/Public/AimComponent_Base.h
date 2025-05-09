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
	
	// Invert Cam
	/*UFUNCTION(BlueprintCallable, meta = (ToolTip = "Set Invert Cam"))
	bool SetTempInvertCam(bool invertCam);
	bool tempInvertCam = false;*/

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
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Gets 2D screen Location of the crosshair"))
	FVector2D GetCrosshairLocation();
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Get the current bone Location of the aim"))
	FVector GetPawnBoneLocation();
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Sets location to FVector::Zero() For when the aim is inactive"))
	void ResetPawnBoneLocation();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Struct Ref
	UPROPERTY(BlueprintReadWrite, Category = "Refs")
	FUAimAssistFeel AimFeel;

private:
	// Temp cam Speed for aim cam speed reset
	float TempHorizCamSpeed = 0.0f;
	float TempVertCamSpeed = 0.0f;
	
	TArray<FHitResult> HitPawns;
	TArray<float> HitPawnsDistToCenter;

	float distToHit = 1.0f;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ToolTip = "Crosshair Screen Location"))
	FVector2D CrosshairScreenLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ToolTip = "Bone Location of the targeted enemy bone"))
	FVector PawnHitLocation;
	
private:
	// Refs
	class APlayer_Controller* playerControler = nullptr;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAimState_Enum CurrentAimState = UAimState_Enum::NotEngaged;
	
protected:
	
	// Timer
	// You should keep the timer handle in one of your properties
	FTimerHandle MyTimerHandle;
	
	
	// Debug Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs|Debug", meta = (ToolTip = "Class Reference to Aiming Debug HUD"))
	TSubclassOf<AHUD> wAimDebugWidget = nullptr;
	// Variable to hold the debug widget After Creating it.
	UPROPERTY(BlueprintReadWrite, Category = "Refs|Debug", meta = (ToolTip = "HUD Reference of the Aiming Debug HUD"))
	AHUD* MyAimDebugMenu = nullptr;
};
