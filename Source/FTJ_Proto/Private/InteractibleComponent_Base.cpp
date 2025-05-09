// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractibleComponent_Base.h"

#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UInteractibleComponent_Base::UInteractibleComponent_Base()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractibleComponent_Base::BeginPlay()
{
	Super::BeginPlay();

	Mesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	
}


// Called every frame
void UInteractibleComponent_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

USphereComponent* UInteractibleComponent_Base::AddOverlapCollision()
{
	USphereComponent* tmp = Cast<USphereComponent>(GetOwner()->AddComponentByClass(UStaticMeshComponent::StaticClass(),false,{},false));
	tmp->AttachToComponent(Mesh,{EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,true},NAME_None);
	tmp->SetSphereRadius(CollisionRadius,true);
	tmp->SetCollisionProfileName("Interactable",true);
	return tmp;
}

