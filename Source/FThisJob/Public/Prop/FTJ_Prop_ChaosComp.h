#pragma once

#include"CoreMinimal.h"
#include"Prop/FTJ_Prop_ChaosCompBase.h"
#include"FTJ_Prop_ChaosComp.generated.h"

//A destructible logic.
UCLASS(Blueprintable) class FTHISJOB_API UFTJ_Prop_ChaosComp : public UFTJ_Prop_ChaosCompBase
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
    virtual void Hit_Implementation
    (
        UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
    )
    override;

    //Public functions
    public :
    UFUNCTION(BlueprintNativeEvent)
    void BreakFeedback(FVector Location);
};