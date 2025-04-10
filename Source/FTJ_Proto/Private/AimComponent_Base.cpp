// Fill out your copyright notice in the Description page of Project Settings.


#include "AimComponent_Base.h"

#include "ComponentUtils.h"

// Sets default values for this component's properties
UAimComponent_Base::UAimComponent_Base()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	//playerControler = Cast<APlayer_Controller>(GetWorld());
}


// Called when the game starts
void UAimComponent_Base::BeginPlay()
{
	Super::BeginPlay();
	// Set Debug
	if(AimFeel.bIsDebugActive)
	{
		// Debug HUD Ref
	}
	// Set Camera Base Speed
	//TempHorizCamSpeed = playerControler.CameraFeel.HorizontalCamSpeed;
	//TempVertCamSpeed = playerControler.CameraFeel.VerticalCamSpeed;

	
	// Timer for Aim System (don't add anything after this)
	// Time(60 FPS) = 1/60 = 0.016667 or (30 FPS) = 1/30 = 0.033333
	float inRate = 0.016667f;
	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &UAimComponent_Base::ExecuteSystem, inRate, true);
}

void UAimComponent_Base::ExecuteSystem()
{
	bool bPawnFound = false;
	FVector2d InLocation = {0,0};
	bool bDoesImplementInterface = false; 
	FVector2d BaseSpotLocation = {0,0}; 
	FVector2d WeakspotLocation = {0,0};
	
	PawnSearch(bPawnFound, InLocation, bDoesImplementInterface, BaseSpotLocation, WeakspotLocation);
	CrosshairScreenLocation = SetCrosshairLocation(bPawnFound, InLocation, bDoesImplementInterface, BaseSpotLocation, WeakspotLocation);
	
	// Debug
	if(CombatFeel.bDebugActive)
	{
		//set crosshair location in debug hud
		//DebugHUD->MainCrosshairLocation = CrosshairScreenLocation;
	}
}

void UAimComponent_Base::PawnSearch(bool& bPawnFound, FVector2d& InLocation, bool& bDoesImplementInterface,
	FVector2d& BaseSpotLocation, FVector2d& WeakspotLocation)
{
	
}


FVector2d UAimComponent_Base::SetCrosshairLocation(bool bPawnFound, FVector2d InLocation, bool bDoesImplementInterface,
	FVector2d BaseSpotLocation, FVector2d WeakspotLocation)
{
	return {0, 0};
}

FVector2d UAimComponent_Base::GetCrosshairLocation()
{
	return CrosshairScreenLocation;
}

// Called every frame
void UAimComponent_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

