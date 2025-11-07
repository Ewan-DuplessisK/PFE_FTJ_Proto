#include"CombatManager/FTJ_CombatManager_SlotBase.h"

#include"CombatManager/FTJ_CombatManager_CreatureBase.h"
#include"CombatManager/FTJ_CombatManager_GridBase.h"

bool FFTJ_CombatManager_SlotBase::IsEqual(UFTJ_CombatManager_CreatureBase const*const InCreature) const
{
    //Just check their equality directly
    return(Creature == InCreature);
}

bool FFTJ_CombatManager_SlotBase::IsAttacking() const
{
    //Return it safely
    return(AttackWeight != 0);
}

bool FFTJ_CombatManager_SlotBase::IsFurtherThanCreature(UFTJ_CombatManager_CreatureBase const*const InCreature , UFTJ_CombatManager_GridBase const*const InGrid) const
{
    //Optimize using a squared distance
    return(FVector::DistSquared2D(Creature->GetComponentLocation() , InGrid->GetComponentLocation()) > FVector::DistSquared2D(InCreature->GetComponentLocation() , InGrid->GetComponentLocation()));
}

bool FFTJ_CombatManager_SlotBase::IsFurtherThan(FFTJ_CombatManager_SlotBase const& InSlot , UFTJ_CombatManager_GridBase const*const InGrid) const
{
    //Optimize using a squared distance
    return
    (
        FVector::DistSquared2D(Creature->GetComponentLocation() , InGrid->GetComponentLocation()) > FVector::DistSquared2D(InSlot.Creature->GetComponentLocation() , InGrid->GetComponentLocation())
    );
}

bool FFTJ_CombatManager_SlotBase::IsValid() const
{
    //Use :: avoiding the recursion
    return(::IsValid(Creature));
}

FFTJ_CombatManager_SlotBase::FFTJ_CombatManager_SlotBase()
{
    //Just copy defaults into fields
    Creature = nullptr;
    ApproachWeight = 0;
    AttackWeight = 0;
}

void FFTJ_CombatManager_SlotBase::UnassignIfInvalid(int32 & OutApproachCapacity , int32 & OutAttackCapacity)
{
    //Check creature validity
    if(Creature && !::IsValid(Creature))
    {
        //Restore grid capacities
        OutApproachCapacity += ApproachWeight;
        OutAttackCapacity += AttackWeight;
        //Just copy defaults into fields
        Creature = nullptr;
        ApproachWeight = 0;
        AttackWeight = 0;
    }
}

bool FFTJ_CombatManager_SlotBase::TryAssignApproach(UFTJ_CombatManager_CreatureBase const*const InCreature)
{
    //Check creature existence
    if(!Creature)
    {
        //Just copy values
        Creature = InCreature;
        ApproachWeight = InCreature->GetApproachWeight();
        AttackWeight = 0;
        return(true);
    }
    else
    {
        //Do nothing otherwise
        return(false);
    }
}

void FFTJ_CombatManager_SlotBase::AssignAttack(int32 const InAttackWeight)
{
    //Just copy a parameter directly
    AttackWeight = InAttackWeight;
}

int32 FFTJ_CombatManager_SlotBase::UnassignApproach()
{
    //Just copy default value here
    Creature = nullptr;
    //Return a weight being reserved
    int32 Buffer{ApproachWeight};
    ApproachWeight = 0;
    return(Buffer);
}

int32 FFTJ_CombatManager_SlotBase::UnassignAttack()
{
    //Return a weight being reserved
    int32 Buffer{AttackWeight};
    AttackWeight = 0;
    return(Buffer);
}