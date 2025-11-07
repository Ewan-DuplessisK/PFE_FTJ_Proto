#include"Prop/FTJ_Prop_PropCompBase.h"

void UFTJ_Prop_PropCompBase::Hit_Implementation
(
    UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
)
{
    
}

void UFTJ_Prop_PropCompBase::CallReversedHit
(
    UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
)
{
    //Wrap as FHitResult::GetReversedHit() is blueprint-incompatible
    Hit(InThisComponent , InActor , InThatComponent , InImpulse , FHitResult::GetReversedHit(InResult) , InTraitArray);
}