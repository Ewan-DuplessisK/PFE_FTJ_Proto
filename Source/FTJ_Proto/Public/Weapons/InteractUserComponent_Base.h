// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractUserComponent_Base.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTJ_PROTO_API UInteractUserComponent_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractUserComponent_Base();

	// Refs
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class APlayer_Controller* PlayerControllerRef = nullptr;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class AGame_Character* PlayerCharacterRef = nullptr;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	class UInteractibleComponent_Base* Closest;
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere)
	TArray<class UInteractibleComponent_Base*> Overlapping;

protected:
	UPROPERTY(BlueprintReadWrite)
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Interact")
	class UInputAction* InputActionInteract;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void Interact();
	void HandleInteract(UInteractibleComponent_Base* Interact);
	UFUNCTION()
	void OwnerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OwnerEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UInteractibleComponent_Base* FindClosest();
};
