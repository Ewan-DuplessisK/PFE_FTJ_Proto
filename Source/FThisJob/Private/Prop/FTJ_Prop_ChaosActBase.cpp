#include"Prop/FTJ_Prop_ChaosActBase.h"

#include"Prop/FTJ_Prop_PropCompBase.h"

#include"GeometryCollection/GeometryCollectionComponent.h"

void AFTJ_Prop_ChaosActBase::BeginPlay()
{
    //Delegate to Actor
    Super::BeginPlay();

    //Unregister any removals (must be done before enabling notifications)
    RemovedPieceCount = 0;

    UGeometryCollectionComponent * GeometryComponent = GetGeometryCollectionComponent();
    if(!IsValid(GeometryComponent))
    {
        return;
    }
    //Subscribe to hits
    GeometryComponent->OnComponentHit.AddDynamic(this , &AFTJ_Prop_ChaosActBase::OnHit);
    //Enable removal notifications
    GeometryComponent->SetNotifyRemovals(true);
    //Subscribe to removals
    GeometryComponent->OnChaosRemovalEvent.AddDynamic(this , &AFTJ_Prop_ChaosActBase::OnPieceRemoved);
}

void AFTJ_Prop_ChaosActBase::OnHit(UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult)
{
    //Check actor correctness because it can be already destroyed
    if(!IsValid(InActor))
    {
        return;
    }
    //Cast to Prop, every physical actor must have it
    auto Component{InActor->GetComponentByClass<UFTJ_Prop_PropCompBase>()};
    //Check component correctness because one can forget to attach
    if(!IsValid(Component))
    {
        return;
    }
    //Tranfer the control to a wrapper to be blueprint-compatible
    Component->CallReversedHit(InThatComponent , this , InThisComponent , InImpulse , InResult , {});
}

void AFTJ_Prop_ChaosActBase::OnPieceRemoved(FChaosRemovalEvent const& InEvent)
{
    //Register a removal
    RemovedPieceCount++;

    if(!IsValid(GeometryCollectionComponent) || GeometryCollectionComponent->RestCollection == nullptr)
    {
        return;
    }

    const int32 TransformCount = GeometryCollectionComponent->RestCollection->GetBreadthFirstTransformIndices().Num();
    const int32 PieceCount = FMath::Max(0 , TransformCount - 1);
    const int32 DestroyThreshold = FMath::CeilToInt(PieceCount * 0.95f);
    //Check the decaying percentage as Chaos doesn't send everything
    if(RemovedPieceCount >= DestroyThreshold)
    {
        //Erase after decaying
        Destroy();
    }
}