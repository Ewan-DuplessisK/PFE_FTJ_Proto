#pragma once

#include"CoreMinimal.h"
#include"Engine/StaticMeshActor.h"
#include"FTJ_Prop_PhysicsKickableActBase.generated.h"

//An AFTJ_Prop_PhysicsKickableAct base compatibility layer.
UCLASS() class FTHISJOB_API AFTJ_Prop_PhysicsKickableActBase : public AStaticMeshActor
{
    GENERATED_BODY()

    //Private variables
    private :

    //Protected variables
    protected :

    //Public variables
    public :

    //Private functions
    private :
    //Subscribes to mesh hit events.
    void BeginPlay() override;
    /*
        Checks the hit correctness and executes the scripted logic.

        @param Go to UPrimitiveComponent::OnComponentHit.
    */
    UFUNCTION() void OnHit(UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult);

    //Protected functions
    protected :

    //Public functions
    public :
};