// Fill out your copyright notice in the Description page of Project Settings.


#include "PropZoneParent.h"

// Sets default values
APropZoneParent::APropZoneParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APropZoneParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APropZoneParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APropZoneParent::SwitchPropIn_Parent(int32 InstanceIndex, UStaticMesh* MeshOverride, bool Init, FTransform ZoneTransform, FVector ZoneExtend){
	if (!IsValid(HISM))
	{
		return;
	}

	const int32 InstanceCount = HISM->GetInstanceCount();
	if (InstanceIndex < 0 || InstanceIndex >= InstanceCount)
	{
		return;
	}
	
	FTransform CurrTransform;
	if (!HISM->GetInstanceTransform(InstanceIndex, CurrTransform, true))
	{
		return;
	}
	FBox LocalBox (-ZoneExtend,ZoneExtend);
	
	if (!LocalBox.IsInside(ZoneTransform.InverseTransformPosition(CurrTransform.GetLocation()))) return;
	
	CurrSpawnedInstances_Parent.AddUnique(InstanceIndex);

	if (!IsValid(Pool_Parent)) return;
	if (PropClasses.Num() < 3)
	{
		UE_LOG(LogTemp, Error, TEXT("PropZoneParent: PropClasses must contain at least 3 classes (Light/Medium/Heavy)."));
		return;
	}
	
	UStaticMesh* SourceMesh = HISM->GetStaticMesh();
	if (!IsValid(SourceMesh))
	{
		return;
	}

	FString PropSize;
	SourceMesh->GetName().Split(TEXT("-"), nullptr, &PropSize, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	AActor* SpawnedActor = nullptr;
	
	if (PropSize == "Light")SpawnedActor = Pool_Parent->SpawnFromPool(CurrTransform,PropClasses[0]);
	else if (PropSize == "Medium")SpawnedActor = Pool_Parent->SpawnFromPool(CurrTransform,PropClasses[1]);
	else if (PropSize == "Heavy")SpawnedActor = Pool_Parent->SpawnFromPool(CurrTransform,PropClasses[2]);
	else return;

	if (!IsValid(SpawnedActor)) return;

	ASuckablePropParent* Prop = Cast<ASuckablePropParent>(SpawnedActor);
	if (!IsValid(Prop))
	{
		return;
	}

	Prop->Origin = HISM->GetOwner();
	if (IsValid(Prop->StaticMeshComp))
	{
		Prop->StaticMeshComp->SetStaticMesh(MeshOverride);
	}
	uint8* tmp = Sounds.Find(MeshOverride);
	if (tmp!=nullptr)Prop->SoundType = *tmp;

	if (!Init)
	{
		HISM->RemoveInstance(InstanceIndex);
	}
	
}

void APropZoneParent::PopulateZone_Parent(UHierarchicalInstancedStaticMeshComponent* InHISM, FTransform ZoneTransform, FVector ZoneExtend){
	if (!IsValid(InHISM))
	{
		UE_LOG(LogTemp, Error, TEXT("PopulateZone_Parent: InHISM is invalid"));
		return;
	}
	
	HISM = InHISM;
	StaticMesh_Parent = HISM->GetStaticMesh();
	if (!IsValid(StaticMesh_Parent))
	{
		UE_LOG(LogTemp,Error,TEXT("StaticMesh Invalid"));
		return;
	}
	CurrSpawnedInstances_Parent = {};
	int LastIndex = HISM->GetInstanceCount();
	
	for (int i=0;i<LastIndex;i++)
	{
		SwitchPropIn_Parent(i,StaticMesh_Parent,true,ZoneTransform,ZoneExtend);
	}

	CurrSpawnedInstances_Parent.Sort([](int a,int b){return a>b;});

	for (int index : CurrSpawnedInstances_Parent)
	{
		HISM->RemoveInstance(index);
	}

	
}

