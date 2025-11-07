#include"Prop/FTJ_Prop_WallActBase.h"

#include"Prop/FTJ_Prop_PropCompBase.h"

void AFTJ_Prop_WallActBase::BeginPlay()
{
    //Delegate to Actor
    Super::BeginPlay();
    //Subscribe to hits
    GetStaticMeshComponent()->OnComponentHit.AddDynamic(this , &AFTJ_Prop_WallActBase::OnHit);
}

void AFTJ_Prop_WallActBase::OnHit(UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult)
{
    //Check actor correctness because it can be already destroyed
    if(!IsValid(InActor))
    {
        return;
    }
    //Cast to Prop, every physical actor must have it
    auto Component{InActor->GetComponentByClass<UFTJ_Prop_PropCompBase>()};
    //Check component correctness because one can forget to attach
    if(!IsValid(Component))
    {
        return;
    }
    //Tranfer the control to a wrapper to be blueprint-compatible
    Component->CallReversedHit(InThatComponent , this , InThisComponent , InImpulse , InResult , {});
}