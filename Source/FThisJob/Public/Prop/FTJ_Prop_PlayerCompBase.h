#pragma once

#include"CoreMinimal.h"
#include"Prop/FTJ_Prop_PropComp.h"
#include"FTJ_Prop_PlayerCompBase.generated.h"

//A UFTJ_Prop_PlayerComp base compatibility layer.
UCLASS() class FTHISJOB_API UFTJ_Prop_PlayerCompBase : public UFTJ_Prop_PropComp
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
    //Go to UFTJ_Prop_PropCompBase::Hit().
    virtual void Hit_Implementation
    (
        UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
    )
    override;

    //Public functions
    public :
};