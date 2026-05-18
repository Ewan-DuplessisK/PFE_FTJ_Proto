// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool_Component.h"
#include "SuckablePropParent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "PropZoneParent.generated.h"

UCLASS()
class FTHISJOB_API APropZoneParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropZoneParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SwitchPropIn_Parent(int32 InstanceIndex, UStaticMesh* MeshOverride, bool Init, FTransform ZoneTransform, FVector ZoneExtend);

	UFUNCTION(BlueprintCallable)
	void PopulateZone_Parent(UHierarchicalInstancedStaticMeshComponent* InHISM, FTransform ZoneTransform, FVector ZoneExtend);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UHierarchicalInstancedStaticMeshComponent* HISM;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<int>CurrSpawnedInstances_Parent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UObjectPool_Component* Pool_Parent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TSubclassOf<ASuckablePropParent>> PropClasses;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<UStaticMesh*,uint8> Sounds;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMesh* StaticMesh_Parent;
};
