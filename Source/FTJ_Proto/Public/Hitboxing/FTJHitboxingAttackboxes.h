#pragma once

#include"Hitboxing/FTJHitboxingHit.h"

#include"CoreMinimal.h"
#include"Hitboxing/FTJHitboxingHitboxes.h"
#include"FTJHitboxingAttackboxes.generated.h"

//Hitbox overlap event
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFTJHitboxingAttackboxesHitEvent , FFTJHitboxingHit const& , InHit);

//Sending damage hitboxes
UCLASS() class FTJ_PROTO_API UFTJHitboxingAttackboxes : public UFTJHitboxingHitboxes
{
    GENERATED_BODY()

    //Private variables
    private :

    //Protected variables
    protected :

    //Public variables
    public :
    //Hitbox overlap data
    FFTJHitboxingHit HitResult;

    //UProperties
    public :
    //Hitbox overlap event
    UPROPERTY(BlueprintAssignable) FFTJHitboxingAttackboxesHitEvent HitEvent;

    //Private functions
    private :

    //Protected functions
    protected :
    //Subscribes to overlaps
    virtual void BeginPlay() override;

    //Public functions
    public :
    //Configures valid preset
    UFTJHitboxingAttackboxes();

    //UFunctions
    public :
    //Enables overlap registration
    UFUNCTION(BlueprintCallable) virtual void Enable();
    //Disables overlap registration
    UFUNCTION(BlueprintCallable) virtual void Disable();
    //Registers hitbox overlaps
    UFUNCTION() void OnHit(UPrimitiveComponent * InOverlapped , AActor * InActor , UPrimitiveComponent * InOther , int32 InBody , bool bInSweep , FHitResult const& InSweep);
};