#pragma once

#include"CoreMinimal.h"
#include"GeometryCollection/GeometryCollectionActor.h"
#include"FTJ_ProtoDestructionActor.generated.h"

struct FChaosRemovalEvent;

UCLASS() class FTJ_PROTO_API AFTJ_ProtoDestructionActor : public AGeometryCollectionActor
{
    GENERATED_BODY()

    //Private variables
    private :

    //Protected variables
    protected :

    //Public variables
    public :
    int32 Removed;

    //UProperties
    public :

    //Private functions
    private :

    //Protected functions
    protected :
    //Makes Geometry Collection static automatically from the very beginning to avoid invalid collision with entities
    virtual void BeginPlay() override;

    //Public functions
    public :

    //UFunctions
    public :
    //Registers piece removals
    UFUNCTION() void OnRemoved(FChaosRemovalEvent const& InRemoval);
};