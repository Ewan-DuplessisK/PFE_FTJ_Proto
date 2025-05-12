// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "InteractibleComponent_Base.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTJ_PROTO_API UInteractibleComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractibleComponent_Base();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* Mesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	class UWidgetComponent* WidgetComponent;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Collisions")
	float CollisionRadius = 100.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Widget")
	TSubclassOf<class UWidgetComponent> InteractibleWidgetComponentClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Widget")
	TSubclassOf<class UInteractableWidget> InteractibleWidgetClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Name")
	FText Title = FText::FromString("Interact");
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	USphereComponent* AddOverlapCollision();
	void ShowBillboard(bool State, bool Passive);
	void AddWidget();
};
