#pragma once

#include"CoreMinimal.h"
#include"CombatManager/FTJ_CombatManager_GridBase.h"
#include"FTJ_CombatManager_Grid.generated.h"

struct FFTJ_CombatManager_Slot;
//8 slots around the player to register enemies to.
UCLASS(Blueprintable) class FTHISJOB_API UFTJ_CombatManager_Grid : public UFTJ_CombatManager_GridBase
{
    GENERATED_BODY()
	
    //Private variables
    private :

    //Protected variables
    protected :

    //Public variables
    public :

    //Private functions
    private :
    //Inherit base constructors.
    using UFTJ_CombatManager_GridBase::UFTJ_CombatManager_GridBase;

    //Protected functions
    protected :

    //Public functions
    public :
	UFUNCTION(BlueprintCallable)
	TArray<FFTJ_CombatManager_SlotBase> GetDeregisteringSlot(UFTJ_CombatManager_CreatureBase const*const InCreature) const;
    bool Slot_IsCloserThan(int Index, int OtherIndex, UFTJ_CombatManager_Grid const* InGrid, UFTJ_CombatManager_CreatureBase const* InCreature) const;

    UFUNCTION(BlueprintCallable)
	int GetAttackRadius() const {return AttackRadius;}
};