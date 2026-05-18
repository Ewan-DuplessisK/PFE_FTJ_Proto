#include"Prop/FTJ_Prop_ChaosComp.h"

#include"Prop/FTJ_Prop_ChaosAct.h"

#include"GeometryCollection/GeometryCollectionComponent.h"

void UFTJ_Prop_ChaosComp::Hit_Implementation
(
    UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult , TArray<EFTJ_Prop_Trait> const& InTraitArray
)
{
    Super::Hit_Implementation(InThisComponent , InActor , InThatComponent , InImpulse , InResult , InTraitArray);
    FVector FeedbackLocation{InResult.ImpactPoint};
    if(AFTJ_Prop_ChaosAct * ChaosOwner = GetOwner<AFTJ_Prop_ChaosAct>())
    {
        if(UGeometryCollectionComponent * GeometryCollectionComponent = ChaosOwner->GetGeometryCollectionComponent())
        {
            FeedbackLocation = GeometryCollectionComponent->GetComponentLocation();
        }
        else
        {
            FeedbackLocation = ChaosOwner->GetActorLocation();
        }
    }
    BreakFeedback(FeedbackLocation);
}

void UFTJ_Prop_ChaosComp::BreakFeedback_Implementation(FVector Location)
{
}