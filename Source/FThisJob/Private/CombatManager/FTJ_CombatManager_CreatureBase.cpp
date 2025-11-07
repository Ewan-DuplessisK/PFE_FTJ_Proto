#include"CombatManager/FTJ_CombatManager_CreatureBase.h"

#include"CombatManager/FTJ_CombatManager_GridBase.h"

UFTJ_CombatManager_CreatureBase::UFTJ_CombatManager_CreatureBase()
{

}

int32 UFTJ_CombatManager_CreatureBase::GetApproachWeight() const
{
    //Just return a copy directly
    return(ApproachWeight);
}

EFTJ_CombatManager_ApproachRegistrationResult UFTJ_CombatManager_CreatureBase::TryRegisterApproach(UFTJ_CombatManager_GridBase *const InGrid , FVector & OutSpot) const
{
    //Just pass to the grid
    return(InGrid->TryRegisterApproach(this , OutSpot));
}

EFTJ_CombatManager_ApproachDeregistrationResult UFTJ_CombatManager_CreatureBase::TryDeregisterApproach(UFTJ_CombatManager_GridBase *const InGrid) const
{
    //Just pass to the grid
    return(InGrid->TryDeregisterApproach(this));
}

EFTJ_CombatManager_AttackRegistrationResult UFTJ_CombatManager_CreatureBase::TryRegisterAttack(UFTJ_CombatManager_GridBase *const InGrid , int32 const InAttackWeight) const
{
    //Just pass to the grid
    return(InGrid->TryRegisterAttack(this , InAttackWeight));
}

EFTJ_CombatManager_AttackDeregistrationResult UFTJ_CombatManager_CreatureBase::TryDeregisterAttack(UFTJ_CombatManager_GridBase *const InGrid) const
{
    //Just pass to the grid
    return(InGrid->TryDeregisterAttack(this));
}

bool UFTJ_CombatManager_CreatureBase::IsSpotValid_Implementation(FVector const& InSpot , FVector const& InGrid) const
{
    //Don't check navigation, collision or other additional tests by default and just allow any spot
    return(true);
}

UFTJ_CombatManager_CreatureBase::UFTJ_CombatManager_CreatureBase(int32 const InApproachWeight)
{
    //Just copy a parameter directly
    ApproachWeight = InApproachWeight;
}