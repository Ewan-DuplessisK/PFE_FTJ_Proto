#include"CombatManager/FTJ_CombatManager_Creature.h"

bool UFTJ_CombatManager_Creature::IsSpotValid_Implementation(FVector const& InSpot , FVector const& InGrid) const
{
    //Just call base
    return(Super::IsSpotValid_Implementation(InSpot , InGrid));
}