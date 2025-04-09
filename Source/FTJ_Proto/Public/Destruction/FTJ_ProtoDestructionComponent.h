#pragma once

#include"CoreMinimal.h"
#include"Components/ActorComponent.h"
#include"FTJ_ProtoDestructionComponent.generated.h"

struct FChaosBreakEvent;

UCLASS(Blueprintable) class FTJ_PROTO_API UFTJ_ProtoDestructionComponent : public UActorComponent
{
    GENERATED_BODY()

    //Private variables
    private :

    //Protected variables
    protected :

    //Public variables
    public :

    //UProperties
    public :

    //Private functions
    private :

    //Protected functions
    protected :

    //Public functions
    public :

    //UFunctions
    public : 
    /*
        Applies external strain and linear velocity, if InComponent is destructible, nothing otherwise (handle by yourself)
        Returns true if InComponent is destructible (damage was applied), you can perform additional post-hit actions
        Returns false if InComponent isn't destructible (damage wasn't applied), you should handle hit by yourself
        @param InComponent Touched actor's component (Event Hit's Other Comp for example), function returns true if it's destructible
        @param InHit Hit result of your actor with touched actor (Event Hit's Hit or whatever you use)
        @param InRadius Radius from location point to apply strain (damage) to (using center of mass of pieces)
        @param InDepth How many levels of connection (layers) to follow to propagate (to apply) strain (damage) through
        @param InFactor When using propagation, factor to multiply strain from one level to other, allowing falloff effect
        @param InStrain Damage to apply to specific piece of geometry collection in efforts to break it down
        @param InVelocity Velocity to apply on specific peace which tries to separate other pieces and move them
    */
    UFUNCTION(BlueprintCallable) virtual bool Hit(UPrimitiveComponent * InComponent , FHitResult InHit , float InRadius , int32 InDepth , float InFactor , float InStrain , FVector InVelocity);
};