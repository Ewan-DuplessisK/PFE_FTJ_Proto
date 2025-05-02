#pragma once

#include"CoreMinimal.h"
#include"Hitboxing/FTJ_ProtoHitboxingHitboxes.h"
#include"Hitboxing/FTJ_ProtoHitboxingHit.h"
#include"FTJ_ProtoHitboxingAttackboxes.generated.h"

//Hitbox overlap event
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFTJ_ProtoHitboxingAttackboxesHitEvent , FFTJ_ProtoHitboxingHit const& , InHit);

UCLASS() class FTJ_PROTO_API UFTJ_ProtoHitboxingAttackboxes : public UFTJ_ProtoHitboxingHitboxes
{
    GENERATED_BODY()

    //Private variables
    private :

    //Protected variables
    protected :

    //Public variables
    public :
    //Hitbox overlap data
    FFTJ_ProtoHitboxingHit HitResult;

    //UProperties
    public :
    //Hitbox overlap event
    UPROPERTY(BlueprintAssignable) FFTJ_ProtoHitboxingAttackboxesHitEvent HitEvent;

    //Private functions
    private :

    //Protected functions
    protected :
    //Subscribes to overlaps
    virtual void BeginPlay() override;

    //Public functions
    public :
    //Configures valid preset
    UFTJ_ProtoHitboxingAttackboxes();

    //UFunctions
    public :
    //Enables overlap registration
    UFUNCTION(BlueprintCallable) virtual void Enable();
    //Disables overlap registration
    UFUNCTION(BlueprintCallable) virtual void Disable();
    //Registers hitbox overlaps
    UFUNCTION() void OnHit(UPrimitiveComponent * InOverlapped , AActor * InActor , UPrimitiveComponent * InOther , int32 InBody , bool bInSweep , FHitResult const& InSweep);
};