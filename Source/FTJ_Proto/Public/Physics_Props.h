// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Physics_Props.generated.h"

UCLASS()
class FTJ_PROTO_API APhysics_Props : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysics_Props();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Mesh")
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Collisions")
	class UBoxComponent* OverlapPhysics;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	class UFTJ_ProtoDestructionComponent* DestructionComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void Launched(FVector force);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool isLaunched = false;

	UFUNCTION(Blueprintable)
	void OnPhysicsOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/*UFUNCTION(Blueprintable)
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,const FHitResult& Hit);*/

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Physics Vars")
	float DampingFactor = .5f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Physics Vars")
	float TransmissionFactor = .8f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Physics Vars")
	float PropLandSpeedThreshold = 1.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Physics Vars")
	int Damage = 1;

	UFUNCTION(BlueprintNativeEvent)
	void HitFeedBack();

};
