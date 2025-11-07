#pragma once

#include"CoreMinimal.h"
#include"Components/SceneComponent.h"
#include"FTJ_CombatManager_GridBase.generated.h"

enum struct EFTJ_CombatManager_ApproachRegistrationResult : uint8;
enum struct EFTJ_CombatManager_ApproachDeregistrationResult : uint8;
enum struct EFTJ_CombatManager_AttackRegistrationResult : uint8;
enum struct EFTJ_CombatManager_AttackDeregistrationResult : uint8;

struct FFTJ_CombatManager_SlotBase;

class UFTJ_CombatManager_CreatureBase;

//A grid's base for compatibility.
UCLASS() class FTHISJOB_API UFTJ_CombatManager_GridBase : public USceneComponent
{
    GENERATED_BODY()
	
    //Private variables
    private :
    //8 slots around the player to register enemies to.
    TArray<FFTJ_CombatManager_SlotBase> SlotArray;

    //Protected variables
    protected :
    //A score to restrict an enemy number/type, their strength.
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (ExposeOnSpawn = True)) int32 ApproachCapacity;
    //A score to restrict an attack number/type, their strength.
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (ExposeOnSpawn = True)) int32 AttackCapacity;
    //A maximal distance an enemy can attack the player.
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (ExposeOnSpawn = True)) int32 ApproachRadius;
    //A minimal distance an enemy can attack the player.
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (ExposeOnSpawn = True)) int32 AttackRadius;

    //Public variables
    public :

    //Private functions
    private :
    /*
        Evaluates a counter-clockwise oriented vector

        @param InVector An integral vector clamped within the bounds of a (-1 ; -1) vector and a (+1 ; +1) vector

        @return A vector which is left to an InVector vector
    */
    FIntVector2 GetLeft(FIntVector2 const& InVector) const;
    /*
        Evaluates a clockwise oriented vector

        @param InVector An integral vector clamped within the bounds of a (-1 ; -1) vector and a (+1 ; +1) vector

        @return A vector which is right to an InVector vector
    */
    FIntVector2 GetRight(FIntVector2 const& InVector) const;
    /*
        Evaluates an inverse oriented vector

        @param InVector An integral vector clamped within the bounds of a (-1 ; -1) vector and a (+1 ; +1) vector

        @return A vector which is opposite to an InVector vector
    */
    FIntVector2 GetOpposite(FIntVector2 const& InVector) const;
    /*
        Evaluates a slot center position

        @param InVector An integral vector clamped within the bounds of a (-1 ; -1) vector and a (+1 ; +1) vector

        @return A suggested world location to place a creature to.
    */
    FVector GetSpot(FIntVector2 const& InVector) const;
    /*
        Tests a suggested world location.

        @param InCreature A grid-assignable enemy.
        @param InVector An integral vector clamped within the bounds of a (-1 ; -1) vector and a (+1 ; +1) vector

        @return Checks if an enemy is able to reach a spot, returns false if is unable.
                Checks if a spot allows an enemy to attack the player, returns false if doesn’t.
                Can run any additional tests.
                Returns true only if all the tests are successful.
    */
    bool IsSpotValid(UFTJ_CombatManager_CreatureBase const*const InCreature , FIntVector2 const& InVector) const;
    //If some creatures are destroyed then removes them and restores grid capacities, does nothing otherwise.
    void UnassignIfInvalid();
    /*
        If a slot is empty then it puts an enemy inside it, does nothing otherwise.

        @param InCreature A grid-assignable enemy.
        @param InVector An integral vector clamped within the bounds of a (-1 ; -1) vector and a (+1 ; +1) vector
        @param OutSpot A registered world location to place a creature to.

        @return True if registered.
    */
    bool TryAssign(UFTJ_CombatManager_CreatureBase const*const InCreature , FIntVector2 const& InVector , FVector & OutSpot);

    //Protected functions
    protected :
    //Implements C++ constructor as a stub for Unreal Engine and as the SlotArray field initializer.
    UFTJ_CombatManager_GridBase();

    //Public functions
    public :
    /*
        Gathers an array containing only valid slots further than the parameter starting from the furthest.

        @param InCreature A grid-assignable enemy.

        @return A linear array containing only existing slots and not all the 8 around the player.
    */
    UFUNCTION(BlueprintCallable) TArray<FFTJ_CombatManager_SlotBase> GetDeregisteringSlotArray(UFTJ_CombatManager_CreatureBase const*const InCreature) const;
    /*
        Implements C++ constructor by copying its parameters into fields

        @param InApproachCapacity A score to restrict an enemy number/type, their strength.
        @param InAttackCapacity A score to restrict an attack number/type, their strength.
        @param InApproachRadius A maximal distance an enemy can attack the player.
        @param InAttackRadius A minimal distance an enemy can attack the player.
    */
    UFTJ_CombatManager_GridBase(int32 const InApproachCapacity , int32 const InAttackCapacity , int32 const InApproachRadius , int32 const InAttackRadius);
    /*
        Requests an approach.

        @param InCreature A grid-assignable enemy.
        @param OutSpot A registered world location to place a creature to.

        @return If its result is Success, the OutSpot parameter is a registered world location, reach it.
                Otherwise, its result is a reason of an error.
    */
    EFTJ_CombatManager_ApproachRegistrationResult TryRegisterApproach(UFTJ_CombatManager_CreatureBase const*const InCreature , FVector & OutSpot);
    /*
        Cancels an approach.

        @param InCreature A grid-assignable enemy.

        @return If its result is Success then cancel an approach.
                Otherwise, its result is a reason of an error.
    */
    EFTJ_CombatManager_ApproachDeregistrationResult TryDeregisterApproach(UFTJ_CombatManager_CreatureBase const*const InCreature);
    /*
        Requests an attack.

        @param InCreature A grid-assignable enemy.
        @param InAttackWeight A score to show an attack type, its strength.

        @return If its result is Success then attack the player.
                If its result is CreatureNeedsToBeCloser then go to TryRegisterApproach.
                Otherwise, its result is a reason of an error.
    */
    EFTJ_CombatManager_AttackRegistrationResult TryRegisterAttack(UFTJ_CombatManager_CreatureBase const*const InCreature , int32 const InAttackWeight);
    /*
        Cancels an attack.

        @param InCreature A grid-assignable enemy.

        @return If its result is Success then cancel an attack.
                Otherwise, its result is a reason of an error.
    */
    EFTJ_CombatManager_AttackDeregistrationResult TryDeregisterAttack(UFTJ_CombatManager_CreatureBase const*const InCreature);
};