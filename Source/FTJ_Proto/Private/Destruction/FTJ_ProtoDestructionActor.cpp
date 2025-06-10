#include"Destruction/FTJ_ProtoDestructionActor.h"

#include"GeometryCollection/GeometryCollectionComponent.h"

void AFTJ_ProtoDestructionActor::BeginPlay()
{
    //Delegates to Actor
    Super::BeginPlay();
    //Makes Geometry Collection static automatically from the very beginning to avoid invalid collision with entities
    GeometryCollectionComponent->SetAnchoredByIndex(0 , true);
    //Enables removal notifications for subscription
    GeometryCollectionComponent->SetNotifyRemovals(true);
    //Subscribes to removals
    GeometryCollectionComponent->OnChaosRemovalEvent.AddDynamic(this , &AFTJ_ProtoDestructionActor::OnRemoved);
    //Unregisters any removals
    Removed = 0;
}

void AFTJ_ProtoDestructionActor::DestructionFeedback_Implementation(){}

void AFTJ_ProtoDestructionActor::OnRemoved(FChaosRemovalEvent const& InRemoval)
{
    //Registers new removal
    Removed++;
    //Checks if decaying is above certain percentage as Chaos doesn't notify about all the removals
    if(Removed >= (GeometryCollectionComponent->RestCollection->GetBreadthFirstTransformIndices().Num() - 1) * 0.95)
    {
        //Destroy on decay
        Destroy();
    }
}
