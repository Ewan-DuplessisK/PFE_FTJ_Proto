#pragma once

#include"CoreMinimal.h"
#include"GeometryCollection/GeometryCollectionActor.h"
#include"FTJ_Prop_ChaosActBase.generated.h"

struct FChaosRemovalEvent;

//An AFTJ_Prop_ChaosAct base compatibility layer.
UCLASS() class FTHISJOB_API AFTJ_Prop_ChaosActBase : public AGeometryCollectionActor
{
    GENERATED_BODY()

    //Private variables
    private :
    //A counter to destroy the destructuble upon fading out.
    int32 RemovedPieceCount;

    //Protected variables
    protected :

    //Public variables
    public :

    //Private functions
    private :
    //Subscribes to mesh hit events and configures piece removals.
    virtual void BeginPlay() override;
    /*
        Checks the hit correctness and executes the scripted logic.

        @param Go to UPrimitiveComponent::OnComponentHit.
    */
    UFUNCTION() void OnHit(UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult);
    /*
        Registers piece removals.

        @param Go to UGeometryCollectionComponent::OnChaosRemovalEvent.
    */
    UFUNCTION() void OnPieceRemoved(FChaosRemovalEvent const& InEvent);

    //Protected functions
    protected :

    //Public functions
    public :
};