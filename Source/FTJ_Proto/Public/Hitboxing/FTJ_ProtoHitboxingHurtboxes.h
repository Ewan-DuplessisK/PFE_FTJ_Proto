#pragma once

#include"CoreMinimal.h"
#include"Hitboxing/FTJ_ProtoHitboxingHitboxes.h"
#include"FTJ_ProtoHitboxingHurtboxes.generated.h"

UCLASS() class FTJ_PROTO_API UFTJ_ProtoHitboxingHurtboxes : public UFTJ_ProtoHitboxingHitboxes
{
    GENERATED_BODY()

    //Private variables
    private :

    //Protected variables
    protected :

    //Public variables
    public :
    //Attackbox overlapped earlier
    FName Attackbox;
    //Hurtbox overlapped earlier
    FName Hurtbox;

    //UProperties
    public :

    //Private functions
    private :

    //Protected functions
    protected :
    //Subscribes to overlaps
    virtual void BeginPlay() override;

    //Public functions
    public :

    //UFunctions
    public :
    //Registers hitbox overlaps
    UFUNCTION() void OnOverlapped(UPrimitiveComponent * InOverlapped , AActor * InActor , UPrimitiveComponent * InOther , int32 InBody , bool bInSweep , FHitResult const& InSweep);
};