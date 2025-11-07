#include"Prop/FTJ_Prop_ChaosActBase.h"

#include"Prop/FTJ_Prop_PropCompBase.h"

#include"GeometryCollection/GeometryCollectionComponent.h"

void AFTJ_Prop_ChaosActBase::BeginPlay()
{
    //Delegate to Actor
    Super::BeginPlay();
    //Subscribe to hits
    GetGeometryCollectionComponent()->OnComponentHit.AddDynamic(this , &AFTJ_Prop_ChaosActBase::OnHit);
    //Enable removal notifications
    GeometryCollectionComponent->SetNotifyRemovals(true);
    //Subscribe to removals
    GeometryCollectionComponent->OnChaosRemovalEvent.AddDynamic(this , &AFTJ_Prop_ChaosActBase::OnPieceRemoved);
    //Unregister any removals
    RemovedPieceCount = 0;
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
    //Check the decaying percentage as Chaos doesn't send everything
    if(RemovedPieceCount >= (GeometryCollectionComponent->RestCollection->GetBreadthFirstTransformIndices().Num() - 1) * 0.95)
    {
        //Erase after decaying
        Destroy();
    }
}