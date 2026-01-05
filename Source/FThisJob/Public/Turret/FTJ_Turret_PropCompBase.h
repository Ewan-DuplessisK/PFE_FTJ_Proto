#pragma once

#include"CoreMinimal.h"
#include"Prop/FTJ_Prop_EnemyComp.h"
#include"FTJ_Turret_PropCompBase.generated.h"

UCLASS() class FTHISJOB_API UFTJ_Turret_PropCompBase : public UFTJ_Prop_EnemyComp
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
};