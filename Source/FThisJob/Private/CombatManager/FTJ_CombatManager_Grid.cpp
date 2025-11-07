#include"CombatManager/FTJ_CombatManager_Grid.h"

#include "CombatManager/FTJ_CombatManager_CreatureBase.h"
#include "CombatManager/FTJ_CombatManager_Slot.h"

TArray<FFTJ_CombatManager_SlotBase> UFTJ_CombatManager_Grid::GetDeregisteringSlot(UFTJ_CombatManager_CreatureBase const*const InCreature) const
{
	TArray<FFTJ_CombatManager_SlotBase>SlotArrayB = GetDeregisteringSlotArray(InCreature);
	
	//Sort by distance
	SlotArrayB.Sort(
		[&](FFTJ_CombatManager_SlotBase const& InA , FFTJ_CombatManager_SlotBase const& InB)
		{return(Slot_IsCloserThan(SlotArrayB.Find(InA),SlotArrayB.Find(InB),this,InCreature));}
	);

	return SlotArrayB;
}

bool UFTJ_CombatManager_Grid::Slot_IsCloserThan(int Index,int OtherIndex,UFTJ_CombatManager_Grid const*const InGrid, UFTJ_CombatManager_CreatureBase const*const InCreature) const
{

	FVector2D Direction,OtherDirection;
	if (Index<4)Direction=FVector2D{(double)(Index%3-1),(double)(Index-Index%3-1)};
	else Direction=FVector2D{(double)((Index+1)%3-1),(double)(Index-Index%3)};
	
	if (Index<4)OtherDirection=FVector2D{(double)(Index%3-1),(double)(Index-Index%3-1)};
	else OtherDirection=FVector2D{(double)((Index+1)%3-1),(double)(Index-Index%3)};

	FVector SpotPos = InGrid->GetComponentLocation() + InGrid->GetAttackRadius() * FVector{static_cast<double>(Direction.X) , static_cast<double>(Direction.Y) , 0.0}.GetUnsafeNormal2D();
	FVector OtherSpotPos = InGrid->GetComponentLocation() + InGrid->GetAttackRadius() * FVector{static_cast<double>(Direction.X) , static_cast<double>(Direction.Y) , 0.0}.GetUnsafeNormal2D();
	
	//Optimize using a squared distance
	return
	(
		FVector::DistSquared2D(SpotPos , InCreature->GetComponentLocation()) > FVector::DistSquared2D(OtherSpotPos , InCreature->GetComponentLocation())
	);
}