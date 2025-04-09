#include "Destruction/FTJ_ProtoDestructionComponent.h"

#include"GeometryCollection/GeometryCollectionComponent.h"

bool UFTJ_ProtoDestructionComponent::Hit(UPrimitiveComponent * InComponent , FHitResult InHit , float InRadius , int32 InDepth , float InFactor , float InStrain , FVector InVelocity)
{
    //Works with geometry collection components (destructibles) only, this functions returns true if cast is valid
    if(auto Component{Cast<UGeometryCollectionComponent>(InComponent)})
    {
        Component->RemoveAllAnchors();
        //Applies external strain to specific piece of geometry collection in efforts to break it down
        Component->ApplyExternalStrain(InHit.Item , InHit.Location , InRadius , InDepth , InFactor , InStrain);
        //Applies linear velocity on specific piece which tries to separate other pieces and move them
        Component->ApplyLinearVelocity(InHit.Item , InVelocity);
        //Component is destructible (damage was applied), you can perform any additional post-hit actions (if any)
        return(true);
    }
    else
    {
        //Component isn't destructible (damage wasn't applied), you need to handle hit by yourself (if needed)
        return(false);
    }
}