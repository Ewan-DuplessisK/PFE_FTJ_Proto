#pragma once

#include"CoreMinimal.h"
#include"FTJ_CombatManager_SlotBase.generated.h"

class UFTJ_CombatManager_CreatureBase;
class UFTJ_CombatManager_GridBase;

//A slot's base for compatibility.
USTRUCT(BlueprintType) struct FFTJ_CombatManager_SlotBase
{
    GENERATED_BODY()

    //Private variables
    private :

    //Protected variables
    protected :
    //A grid-assignable enemy.
    UPROPERTY(BlueprintReadOnly) UFTJ_CombatManager_CreatureBase const* Creature;
    //A score to show an enemy type, its strength.
    UPROPERTY(BlueprintReadOnly) int32 ApproachWeight;
    //A score to show an attack type, its strength.
    UPROPERTY(BlueprintReadOnly) int32 AttackWeight;

    //Public variables
    public :

    //Private functions
    private :

    //Protected functions
    protected :

    //Public functions
    public :
    /*
        Checks enemy equivalency.

        @param InCreature A grid-assignable enemy.

        @return True if a creature located right inside this slot is the same as an InCreature.
    */
    bool IsEqual(UFTJ_CombatManager_CreatureBase const*const InCreature) const;
    /*
        Checks enemy offensiveness.

        @return True if a creature located right inside this slot has got an attack still registered.
    */
    bool IsAttacking() const;
    /*
        Checks this slot's creature and the parameter one's locations relative to the grid passed here.

        @param InCreature A grid-assignable enemy.
        @param InGrid 8 slots around the player to register enemies to.

        @return True if this slot's creature is further from the grid than the one passed here.
    */
    bool IsFurtherThanCreature(UFTJ_CombatManager_CreatureBase const*const InCreature , UFTJ_CombatManager_GridBase const*const InGrid) const;
    /*
        Checks this slot's creature and the parameter's one locations relative to the grid passed here.

        @param InSlot A grid element.
        @param InGrid 8 slots around the player to register enemies to.

        @return True if this slot's creature is further from the grid than the one's passed here.
    */
    bool IsFurtherThan(FFTJ_CombatManager_SlotBase const& InSlot , UFTJ_CombatManager_GridBase const*const InGrid) const;
    /*
        Checks creature state.

        @return True if non-null and existing.
    */
    bool IsValid() const;
    //Implements C++ constructor by copying default initializers into fields
    FFTJ_CombatManager_SlotBase();
    /*
        If a creature is destroyed then removes it and restores grid capacities, does nothing otherwise.

        @param OutApproachCapacity A score to restrict an enemy number/type, their strength.
        @param OutAttackCapacity A score to restrict an attack number/type, their strength.
    */
    void UnassignIfInvalid(int32 & OutApproachCapacity , int32 & OutAttackCapacity);
    /*
        If a slot is empty then it puts an enemy inside it, does nothing otherwise.

        @param InCreature A grid-assignable enemy.

        @return True if registered.
    */
    bool TryAssignApproach(UFTJ_CombatManager_CreatureBase const*const InCreature);
    /*
        Binds an offense.

        @param InAttackWeight A score to show an attack type, its strength.
    */
    void AssignAttack(int32 const InAttackWeight);
    /*
        Deregisters a creature

        @return Approach weight reserved by it
    */
    int32 UnassignApproach();
    /*
        Deregisters an offense.

        @return Attack weight reserved by it
    */
    int32 UnassignAttack();


    bool operator==(const FFTJ_CombatManager_SlotBase& rhs) const
    {
        return rhs.IsEqual(this->Creature);
    }
};