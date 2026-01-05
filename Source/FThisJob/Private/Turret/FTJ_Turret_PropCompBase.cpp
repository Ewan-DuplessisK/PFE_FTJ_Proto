#include"Turret/FTJ_Turret_PropCompBase.h"

#include"HitInterface.h"

void UFTJ_Turret_PropCompBase::Hit_Implementation
(
    UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
)
{
    if(InImpulse.Size() < 50.0 || !GetOwner()->Implements<UHitInterface>())
    {
        return;
    }
    IHitInterface::Execute_GetHit(GetOwner() , InImpulse.Size() / 100.0 , 0.0 , (GetOwner()->GetActorLocation() - InActor->GetActorLocation()).GetSafeNormal() , 0.0 , InActor);
}