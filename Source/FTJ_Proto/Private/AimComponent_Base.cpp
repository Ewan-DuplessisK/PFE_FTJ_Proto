// Fill out your copyright notice in the Description page of Project Settings.


#include "AimComponent_Base.h"

#include "ComponentUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UAimComponent_Base::UAimComponent_Base()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
	playerControler = Cast<APlayer_Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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
	TempHorizCamSpeed = playerControler->CameraFeel.HorizontalCamSpeed;
	TempVertCamSpeed = playerControler->CameraFeel.VerticalCamSpeed;
	
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
	HitPawnsDistToCenter.Empty();
	
	FVector2d viewportSize = {1.0f, 1.0f};
	GEngine->GameViewport->GetViewportSize(viewportSize);
	FVector WorldLocation  = {0, 0, 0};
	FVector WorldDirection = {0, 0, 0};
	playerControler->DeprojectScreenPositionToWorld((viewportSize/2).X, (viewportSize/2).Y, WorldLocation, WorldDirection);
	
	const FVector Start = WorldLocation + (AimFeel.StartOffset * WorldDirection);
	const FVector End = WorldLocation + (WorldDirection * AimFeel.AssistRange);
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if(UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(), Start, End, AimFeel.HeadshotRadius, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None,HitPawns, false))
	{
		for (FHitResult ArrayElement : HitPawns)
		{
			FVector2d screenPosition = {0, 0};
			playerControler->ProjectWorldLocationToScreen(ArrayElement.ImpactPoint, screenPosition);
			
			HitPawnsDistToCenter.Add(UKismetMathLibrary::Distance2D(viewportSize/2, screenPosition));
		}
		int indexOfMinValue = 0;
		float valueOfMinValue = 0.0f;
		UKismetMathLibrary::MinOfFloatArray(HitPawnsDistToCenter, indexOfMinValue, valueOfMinValue);
		
		FHitResult chosenHit = HitPawns[indexOfMinValue];
		FVector2d screenLocation = {0, 0};
		playerControler->ProjectWorldLocationToScreen(chosenHit.ImpactPoint, screenLocation);
		FVector2d L_EngagedPawnScreenLoc = screenLocation;
		AActor* L_EngagedPawn = chosenHit.GetActor();

		if (/*Implement Interface BPI Damageable*/ false)
		{
			bPawnFound = true;
			InLocation = L_EngagedPawnScreenLoc;
			bDoesImplementInterface = true;
			BaseSpotLocation = L_EngagedPawnScreenLoc;
			WeakspotLocation = L_EngagedPawnScreenLoc;
		
			return;
		}
		else
		{
			bPawnFound = true;
			InLocation = L_EngagedPawnScreenLoc;
			bDoesImplementInterface = false;
			BaseSpotLocation = {0, 0};
			WeakspotLocation = {0, 0};
		
			return;
		}
	}
	else
	{
		bPawnFound = false;
		InLocation = {-1, -1};
		bDoesImplementInterface = false;
		BaseSpotLocation = {0, 0};
		WeakspotLocation = {0, 0};
		
		return;
	}
	
	return;
}


FVector2d UAimComponent_Base::SetCrosshairLocation(bool bPawnFound, FVector2d InLocation, bool bDoesImplementInterface,
	FVector2d BaseSpotLocation, FVector2d WeakspotLocation)
{
	FVector2d viewportSize = {0, 0};
	GEngine->GameViewport->GetViewportSize(viewportSize);
	FVector2d viewportCenter = viewportSize / 2.0f;
	
	float PawnDistToCenter = UKismetMathLibrary::Distance2D(InLocation, viewportCenter);


	if(bPawnFound && PawnDistToCenter <= AimFeel.BendShotRadius)
	{
		if(bDoesImplementInterface)
		{
			if(UKismetMathLibrary::Distance2D(WeakspotLocation, viewportCenter) <= AimFeel.HeadshotRadius)
			{
				// Set State "Locking on Weakspot"
				
				playerControler->CameraFeel.HorizontalCamSpeed = TempHorizCamSpeed / AimFeel.WeakFactor;
				playerControler->CameraFeel.VerticalCamSpeed = TempVertCamSpeed / AimFeel.WeakFactor;

				return WeakspotLocation;
			}
			else if(UKismetMathLibrary::Distance2D(BaseSpotLocation, viewportCenter) <= AimFeel.BaseShotRadius)
				{
					// Set State "Locking on Basespot"
					
					playerControler->CameraFeel.HorizontalCamSpeed = TempHorizCamSpeed / AimFeel.BaseFactor;
					playerControler->CameraFeel.VerticalCamSpeed = TempVertCamSpeed / AimFeel.BaseFactor;

					return BaseSpotLocation;
				}
		}
		else
		{
			// Set State to "Not Engaged"
			
			playerControler->CameraFeel.HorizontalCamSpeed = TempHorizCamSpeed;
			playerControler->CameraFeel.VerticalCamSpeed = TempVertCamSpeed;
			
			if(PawnDistToCenter <= AimFeel.BaseShotRadius)
			{
				// Set State "Simple Engaged"
				
				playerControler->CameraFeel.HorizontalCamSpeed = TempHorizCamSpeed / AimFeel.SimpleFactor;
				playerControler->CameraFeel.VerticalCamSpeed = TempVertCamSpeed / AimFeel.SimpleFactor;
				
				return InLocation;
			}
			else
			{
				// Set State "Bending Crosshair"
				
				playerControler->CameraFeel.HorizontalCamSpeed = TempHorizCamSpeed / AimFeel.BendFactor;
				playerControler->CameraFeel.VerticalCamSpeed = TempVertCamSpeed / AimFeel.BendFactor;
				
				return viewportCenter + (UKismetMathLibrary::Normal2D((InLocation - viewportCenter)) *
					(AimFeel.BaseShotRadius * (AimFeel.BendShotRadius - PawnDistToCenter)) / (AimFeel.BendShotRadius - AimFeel.BaseShotRadius));
			}
		}
	}
	else
	{
		if (PawnDistToCenter <= AimFeel.MagneticRadius)
		{
			// set state to "Magnetic Crosshair"
			
			playerControler->CameraFeel.HorizontalCamSpeed = TempHorizCamSpeed / AimFeel.MagneticFactor;
			playerControler->CameraFeel.VerticalCamSpeed = TempVertCamSpeed / AimFeel.MagneticFactor;

		}
		else
		{
			// Set State to "Not Engaged"

			playerControler->CameraFeel.HorizontalCamSpeed = TempHorizCamSpeed;
			playerControler->CameraFeel.VerticalCamSpeed = TempVertCamSpeed;
		}
		
		return viewportCenter;
	}

	return viewportCenter;
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

