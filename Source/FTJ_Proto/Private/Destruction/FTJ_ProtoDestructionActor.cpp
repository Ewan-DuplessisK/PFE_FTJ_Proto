#include"Destruction/FTJ_ProtoDestructionActor.h"

#include"GeometryCollection/GeometryCollectionComponent.h"

void AFTJ_ProtoDestructionActor::BeginPlay()
{
    //Logic in Actor
    Super::BeginPlay();
    //Makes Geometry Collection static automatically from the very beginning to avoid invalid collision with entities
    GeometryCollectionComponent->SetAnchoredByIndex(0 , true);
}