#include"Prop/FTJ_Prop_PhysicsKickableCompBase.h"

#include"Prop/FTJ_Prop_PhysicsKickableActBase.h"

void UFTJ_Prop_PhysicsKickableCompBase::Hit_Implementation
(
    UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
)
{
    //Check the impulse to be above a certain threshold
    if(InImpulse.Size() > 500.0)
    {
        //Erase just as an example and for testing reasons
        GetOwner()->Destroy();
    }
}