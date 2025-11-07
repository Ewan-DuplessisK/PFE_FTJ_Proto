#include"CombatManager/FTJ_CombatManager_GridBase.h"

#include"CombatManager/FTJ_CombatManager_CreatureBase.h"
#include"CombatManager/FTJ_CombatManager_SlotBase.h"

FIntVector2 UFTJ_CombatManager_GridBase::GetLeft(FIntVector2 const& InVector) const
{
    //Evaluate a (X + Y ; Y - X) vector and clamp it between -1 and +1, extracting a left vector
    return(FIntVector2{FMath::Clamp(InVector.X + InVector.Y , -1 , 1) , FMath::Clamp(InVector.Y - InVector.X , -1 , 1)});
}

FIntVector2 UFTJ_CombatManager_GridBase::GetRight(FIntVector2 const& InVector) const
{
    //Evaluate a (X - Y ; Y + X) vector and clamp it between -1 and +1, extracting a right vector
    return(FIntVector2{FMath::Clamp(InVector.X - InVector.Y , -1 , 1) , FMath::Clamp(InVector.Y + InVector.X , -1 , 1)});
}

FIntVector2 UFTJ_CombatManager_GridBase::GetOpposite(FIntVector2 const& InVector) const
{
    //Just negate it
    return(FIntVector2{-InVector.X , -InVector.Y});
}

FVector UFTJ_CombatManager_GridBase::GetSpot(FIntVector2 const& InVector) const
{
    //Evaluate (GridPosition + AttackRadius * SpotDirection) extracting the slot center (spot world location)
    return(GetComponentLocation() + AttackRadius * FVector{static_cast<double>(InVector.X) , static_cast<double>(InVector.Y) , 0.0}.GetUnsafeNormal2D());
}

bool UFTJ_CombatManager_GridBase::IsSpotValid(UFTJ_CombatManager_CreatureBase const*const InCreature , FIntVector2 const& InVector) const
{
    //Just pass to a slot
    return(InCreature->IsSpotValid(GetSpot(InVector) , GetComponentLocation()));
}

void UFTJ_CombatManager_GridBase::UnassignIfInvalid()
{
    //Iterate through slots
    for(FFTJ_CombatManager_SlotBase & Slot : SlotArray)
    {
        //Just pass to a slot
        Slot.UnassignIfInvalid(ApproachCapacity , AttackCapacity);
    }
}

bool UFTJ_CombatManager_GridBase::TryAssign(UFTJ_CombatManager_CreatureBase const*const InCreature , FIntVector2 const& InVector , FVector & OutSpot)
{
    //Convert an index from base 3 to base 10 and add 1 to its digits
    int32 Index{3 * (InVector.Y + 1) + (InVector.X + 1)};
    //Fix the (0 ; 0) vector problem which is absent under an index 4 shifting everything aftewards
    Index -= Index > 4;
    //Register a creature, may refuse
    bool bIsAssigned{SlotArray[Index].TryAssignApproach(InCreature)};
    //Check registration success
    if(bIsAssigned)
    {
        OutSpot = GetSpot(InVector);
    }
    //Just return it by copy
    return(bIsAssigned);
}

UFTJ_CombatManager_GridBase::UFTJ_CombatManager_GridBase()
{
    //Allocate 8 slots
    SlotArray.SetNum(8);
}

TArray<FFTJ_CombatManager_SlotBase> UFTJ_CombatManager_GridBase::GetDeregisteringSlotArray(UFTJ_CombatManager_CreatureBase const*const InCreature) const
{
    //An array buffer for deregistering
    TArray<FFTJ_CombatManager_SlotBase> DeregisteringSlotArray;
    //Iterate through slots
    for(FFTJ_CombatManager_SlotBase const& Slot : SlotArray)
    {
        //Test by distance
        if(Slot.IsValid() && Slot.IsFurtherThanCreature(InCreature , this))
        {
            //Add only the further ones
            DeregisteringSlotArray.Emplace(Slot);
        }
    }
    //Sort by distance
    DeregisteringSlotArray.Sort([&](FFTJ_CombatManager_SlotBase const& InA , FFTJ_CombatManager_SlotBase const& InB){return(InA.IsFurtherThan(InB , this));});
    //Return by copy
    return(DeregisteringSlotArray);
}

UFTJ_CombatManager_GridBase::UFTJ_CombatManager_GridBase(int32 const InApproachCapacity , int32 const InAttackCapacity , int32 const InApproachRadius , int32 const InAttackRadius) : UFTJ_CombatManager_GridBase{}
{
    //Just copy parameters into fields
    ApproachCapacity = InApproachCapacity;
    AttackCapacity = InAttackCapacity;
    ApproachRadius = InApproachRadius;
    AttackRadius = InAttackRadius;
}

EFTJ_CombatManager_ApproachRegistrationResult UFTJ_CombatManager_GridBase::TryRegisterApproach(UFTJ_CombatManager_CreatureBase const*const InCreature , FVector & OutSpot)
{
    //Remove destroyed creatures
    UnassignIfInvalid();
    //Iterate through slots
    for(int32 SlotIndex{0} ; SlotIndex < SlotArray.Num() ; SlotIndex++)
    {
        //Check enemy equivalency
        if(SlotArray[SlotIndex].IsEqual(InCreature))
        {
            //Check enemy offensiveness
            if(SlotArray[SlotIndex].IsAttacking())
            {
                return(EFTJ_CombatManager_ApproachRegistrationResult::CreatureIsAttacking);
            }
            //Don't modify the iterating index
            int32 Index{SlotIndex};
            //Fix the (0 ; 0) vector problem which is absent under an index 4 shifting everything aftewards
            Index += Index >= 4;
            //Convert an index from base 10 to base 3 and subtract 1 from its digits
            FIntVector2 Mapping{(Index % 3) - 1 , (Index / 3) - 1};
            //Check a slot occupied earlier
            if(IsSpotValid(InCreature , Mapping))
            {
                //Optimize spot re-registration
                OutSpot = GetSpot(Mapping);
                return(EFTJ_CombatManager_ApproachRegistrationResult::Success);
            }
            else
            {
                return(EFTJ_CombatManager_ApproachRegistrationResult::OccupiedSlotIsInvalidNow);
            }
        }
    }
    //Check placement possibility
    if(InCreature->GetApproachWeight() <= ApproachCapacity)
    {
        //Add grid damage
        ApproachCapacity -= InCreature->GetApproachWeight();
        //Evaluate spot position in slots relative to the grid
        FVector Direction{(InCreature->GetComponentLocation() - GetComponentLocation()).GetUnsafeNormal2D()};
        FIntVector2 Mapping{FMath::RoundToInt32(Direction.X) , FMath::RoundToInt32(Direction.Y)};
        //Check the closest available slot
        if(IsSpotValid(InCreature , Mapping) && TryAssign(InCreature , Mapping , OutSpot))
        {
            return(EFTJ_CombatManager_ApproachRegistrationResult::Success);
        }
        else
        {
            //Iterate through all the neighbors
            for(FIntVector2 Left{GetLeft(Mapping)} , Right{GetRight(Mapping)} ; Left != Right ; Left = GetLeft(Left) , Right = GetRight(Right))
            {
                //Check left and right slots
                if((IsSpotValid(InCreature , Left) && TryAssign(InCreature , Left , OutSpot)) || (IsSpotValid(InCreature , Right) && TryAssign(InCreature , Right , OutSpot)))
                {
                    return(EFTJ_CombatManager_ApproachRegistrationResult::Success);
                }
            }
            //Check the furthest available slot
            if(IsSpotValid(InCreature , GetOpposite(Mapping)) && TryAssign(InCreature , GetOpposite(Mapping) , OutSpot))
            {
                return(EFTJ_CombatManager_ApproachRegistrationResult::Success);
            }
            else
            {
                return(EFTJ_CombatManager_ApproachRegistrationResult::GridHasNoMoreSlots);
            }
        }
    }
    else
    {
        return(EFTJ_CombatManager_ApproachRegistrationResult::ApproachCapacityIsTooLow);
    }
}

EFTJ_CombatManager_ApproachDeregistrationResult UFTJ_CombatManager_GridBase::TryDeregisterApproach(UFTJ_CombatManager_CreatureBase const*const InCreature)
{
    //Iterate through slots
    for(FFTJ_CombatManager_SlotBase & Slot : SlotArray)
    {
        //Check enemy equivalency
        if(Slot.IsEqual(InCreature))
        {
            //Check enemy offensiveness
            if(Slot.IsAttacking())
            {
                return(EFTJ_CombatManager_ApproachDeregistrationResult::CreatureIsAttacking);
            }
            else
            {
                //Reduce grid damage
                ApproachCapacity += Slot.UnassignApproach();
                return(EFTJ_CombatManager_ApproachDeregistrationResult::Success);
            }
        }
    }
    return(EFTJ_CombatManager_ApproachDeregistrationResult::CreatureIsNotOnGrid);
}

EFTJ_CombatManager_AttackRegistrationResult UFTJ_CombatManager_GridBase::TryRegisterAttack(UFTJ_CombatManager_CreatureBase const*const InCreature , int32 const InAttackWeight)
{
    //Remove destroyed creatures
    UnassignIfInvalid();
    //Iterate through slots
    for(FFTJ_CombatManager_SlotBase & Slot : SlotArray)
    {
        //Check enemy equivalency
        if(Slot.IsEqual(InCreature))
        {
            //Check enemy offensiveness
            if(Slot.IsAttacking())
            {
                return(EFTJ_CombatManager_AttackRegistrationResult::CreatureAlreadyAttacks);
            }
            //Check offense possibility
            else if(InAttackWeight <= AttackCapacity)
            {
                //Check attack distance
                if((InCreature->GetComponentLocation() - GetComponentLocation()).Size2D() > ApproachRadius)
                {
                    return(EFTJ_CombatManager_AttackRegistrationResult::CreatureNeedsToBeCloser);
                }
                //Add grid damage
                AttackCapacity -= InAttackWeight;
                //Put in the attacking state
                Slot.AssignAttack(InAttackWeight);
                return(EFTJ_CombatManager_AttackRegistrationResult::Success);
            }
            else
            {
                return(EFTJ_CombatManager_AttackRegistrationResult::AttackCapacityIsTooLow);
            }
        }
    }
    return(EFTJ_CombatManager_AttackRegistrationResult::CreatureIsNotOnGrid);
}

EFTJ_CombatManager_AttackDeregistrationResult UFTJ_CombatManager_GridBase::TryDeregisterAttack(UFTJ_CombatManager_CreatureBase const*const InCreature)
{
    //Iterate through slots
    for(FFTJ_CombatManager_SlotBase & Slot : SlotArray)
    {
        //Check enemy equivalency
        if(Slot.IsEqual(InCreature))
        {
            //Check enemy offensiveness
            if(!Slot.IsAttacking())
            {
                return(EFTJ_CombatManager_AttackDeregistrationResult::CreatureDoesNotAttackYet);
            }
            else
            {
                //Reduce grid damage
                AttackCapacity += Slot.UnassignAttack();
                return(EFTJ_CombatManager_AttackDeregistrationResult::Success);
            }
        }
    }
    return(EFTJ_CombatManager_AttackDeregistrationResult::CreatureIsNotOnGrid);
}