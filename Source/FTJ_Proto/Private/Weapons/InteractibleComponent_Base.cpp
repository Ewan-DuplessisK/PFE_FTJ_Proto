// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/InteractibleComponent_Base.h"

#include "Weapons/InteractableWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

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
	AddOverlapCollision();
	AddWidget();
	
}


// Called every frame
void UInteractibleComponent_Base::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

USphereComponent* UInteractibleComponent_Base::AddOverlapCollision()
{
	USphereComponent* tmp = Cast<USphereComponent>(GetOwner()->AddComponentByClass(USphereComponent::StaticClass(),false,{},false));
	tmp->AttachToComponent(Mesh,{EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,true},NAME_None);
	tmp->SetSphereRadius(CollisionRadius,true);
	tmp->SetCollisionProfileName("Interactable",true);
	return tmp;
}

void UInteractibleComponent_Base::ShowBillboard(bool State, bool Passive)
{
	WidgetComponent->SetVisibility(State,false);
	if(State)
	{
		WidgetComponent->GetWidget()->SetColorAndOpacity(FLinearColor{1.f,1.f,1.f,Passive?0.3f:1.f});
	}
}

void UInteractibleComponent_Base::AddWidget()
{
	WidgetComponent = Cast<UWidgetComponent>(GetOwner()->AddComponentByClass(InteractibleWidgetComponentClass,false,{},false));
	WidgetComponent->SetWidget(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(),0),InteractibleWidgetClass));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetVisibility(false,false);
	Cast<UInteractableWidget>(WidgetComponent->GetWidget())->Title=Title;
}

