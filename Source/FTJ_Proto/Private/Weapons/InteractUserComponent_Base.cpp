// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/InteractUserComponent_Base.h"

#include "EnhancedInputComponent.h"
#include "Game_Character.h"
#include "Weapons/InteractibleComponent_Base.h"
#include "Player_Controller.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInteractUserComponent_Base::UInteractUserComponent_Base()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UInteractUserComponent_Base::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacterRef = Cast<AGame_Character>(GetOwner());
	PlayerControllerRef = Cast<APlayer_Controller>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	//ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerControllerRef->InputComponent);
	if (!EnhancedInputComponent)
	{
		return;
	}
	EnhancedInputComponent->BindAction(InputActionInteract, ETriggerEvent::Triggered, this, &UInteractUserComponent_Base::Interact);
	GetOwner()->OnActorBeginOverlap.AddDynamic(this,&UInteractUserComponent_Base::OwnerBeginOverlap);
	GetOwner()->OnActorEndOverlap.AddDynamic(this,&UInteractUserComponent_Base::OwnerEndOverlap);
}

void UInteractUserComponent_Base::Interact()
{
	if(IsValid(Closest))
	{
		HandleInteract(Closest);
	}
}

void UInteractUserComponent_Base::HandleInteract(UInteractibleComponent_Base* Interact)
{
	
}

void UInteractUserComponent_Base::OwnerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp,Warning,TEXT("OwnerOverlap"));
	UInteractibleComponent_Base* Comp=Cast<UInteractibleComponent_Base>(OtherActor->GetComponentByClass(UInteractibleComponent_Base::StaticClass()));
	if(IsValid(Comp))
	{
		Overlapping.AddUnique(Comp);
		UE_LOG(LogTemp,Warning,TEXT("ValidComp"));
		Comp->ShowBillboard(true,true);
	}

}

void UInteractUserComponent_Base::OwnerEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp,Warning,TEXT("OwnerEndOverlap"));
	UInteractibleComponent_Base* Comp=Cast<UInteractibleComponent_Base>(OtherActor->GetComponentByClass(UInteractibleComponent_Base::StaticClass()));
	if(IsValid(Comp))
	{
		Overlapping.Remove(Comp);
		Comp->ShowBillboard(false,true);
	}
}




// Called every frame
void UInteractUserComponent_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UInteractibleComponent_Base* TmpClosest = FindClosest();
	if(IsValid(TmpClosest))
	{
		TmpClosest->ShowBillboard(true,false);
		if(IsValid(Closest))
		{
			if(Closest!=TmpClosest)
			{
				Closest->ShowBillboard(true,true);
			}
		}
		Closest=TmpClosest;
		
	}else
	{
		Closest=nullptr;
	}
}

UInteractibleComponent_Base* UInteractUserComponent_Base::FindClosest()
{
	float ClosestDistance=500.f;
	UInteractibleComponent_Base* TmpClosest = nullptr;
	if(Overlapping.Num()==1)return Overlapping[0];
	else
	{
		for(UInteractibleComponent_Base* Overlap : Overlapping)
		{
			float dis = FVector::Distance(PlayerCharacterRef->GetActorLocation()+PlayerCharacterRef->FirstPersonCameraComponent->GetRelativeLocation()+PlayerCharacterRef->FirstPersonCameraComponent->GetForwardVector()*100.f,Overlap->GetOwner()->GetActorLocation());
			if(PlayerCharacterRef->GetActorForwardVector().Dot(Overlap->GetOwner()->GetActorLocation()-PlayerCharacterRef->GetActorLocation()*(1.f,1.f,0.f))>0.f)
			{
				if(dis<ClosestDistance)
				{
					ClosestDistance=dis;
					TmpClosest = Overlap;
				}
			}
		}
		return TmpClosest;
	}
}