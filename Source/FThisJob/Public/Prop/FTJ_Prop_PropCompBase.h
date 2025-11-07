#pragma once

#include"CoreMinimal.h"
#include"Components/SceneComponent.h"
#include"FTJ_Prop_PropCompBase.generated.h"

//A UFTJ_Prop_PropComp base compatibility layer.
UCLASS() class FTHISJOB_API UFTJ_Prop_PropCompBase : public UActorComponent
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

    //Protected functions
    protected :
    /*
        Checks the hit correctness and executes the scripted logic.

        @param Go to UPrimitiveComponent::OnComponentHit.
        @param InTraitArray An array which can be populated with any EFTJ_Prop_Trait values to indicate some specific behavior.
    */
    UFUNCTION(BlueprintCallable , BlueprintNativeEvent) void Hit
    (
        UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
    );
    //Go to UFTJ_Prop_PropCompBase::Hit().
    virtual void Hit_Implementation
    (
        UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
    );

    //Public functions
    public :
    /*
        Wraps UFTJ_Prop_PropCompBase::Hit() to be blueprint-compatible.

        @param Go to UFTJ_Prop_PropCompBase::Hit().
    */
    UFUNCTION(BlueprintCallable) void CallReversedHit
    (
        UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
    );
};