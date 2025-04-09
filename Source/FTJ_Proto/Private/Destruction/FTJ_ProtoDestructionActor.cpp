#include"Destruction/FTJ_ProtoDestructionActor.h"

#include"GeometryCollection/GeometryCollectionComponent.h"

void AFTJ_ProtoDestructionActor::BeginPlay()
{
    //Logic in Actor
    Super::BeginPlay();
    //The entire world
    FBox Box{FVector{-1'000'000'000} , FVector{+1'000'000'000}};
    //Makes Geometry Collection static automatically from the very beginning to avoid invalid collision with entities
    GeometryCollectionComponent->SetAnchoredByBox(Box , true);
}