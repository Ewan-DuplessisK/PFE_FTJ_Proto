#pragma once

#include"CoreMinimal.h"
#include"Components/SceneComponent.h"
#include"FTJ_CombatManager_CreatureBase.generated.h"

class UFTJ_CombatManager_GridBase;

//The TryRegisterApproach function return value pointing out the errors.
UENUM(BlueprintType) enum struct EFTJ_CombatManager_ApproachRegistrationResult : uint8
{
    Success
    ,
    ApproachCapacityIsTooLow
    ,
    GridHasNoMoreSlots
    ,
    CreatureIsAttacking
    ,
    OccupiedSlotIsInvalidNow
};

//The TryDeregisterApproach function return value pointing out the errors.
UENUM(BlueprintType) enum struct EFTJ_CombatManager_ApproachDeregistrationResult : uint8
{
    Success
    ,
    CreatureIsNotOnGrid
    ,
    CreatureIsAttacking
};

//The TryRegisterAttack function return value pointing out the errors.
UENUM(BlueprintType) enum struct EFTJ_CombatManager_AttackRegistrationResult : uint8
{
    Success
    ,
    CreatureIsNotOnGrid
    ,
    CreatureAlreadyAttacks
    ,
    AttackCapacityIsTooLow
    ,
    CreatureNeedsToBeCloser
};

//The TryDeregisterAttack function return value pointing out the errors.
UENUM(BlueprintType) enum struct EFTJ_CombatManager_AttackDeregistrationResult : uint8
{
    Success
    ,
    CreatureIsNotOnGrid
    ,
    CreatureDoesNotAttackYet
};

//A creature's base for compatibility.
UCLASS() class FTHISJOB_API UFTJ_CombatManager_CreatureBase : public USceneComponent
{
    GENERATED_BODY()
	
    //Private variables
    private :

    //Protected variables
    protected :
    //A score to show an enemy type, its strength.
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (ExposeOnSpawn = True)) int32 ApproachWeight;

    //Public variables
    public :

    //Private functions
    private :

    //Protected functions
    protected :
    //Implements C++ constructor as a stub for Unreal Engine.
    UFTJ_CombatManager_CreatureBase();

    //Public functions
    public :
    /*
        Implements the ApproachWeight field getter.

        @return A score to show an enemy type, its strength.
    */
    int32 GetApproachWeight() const;
    /*
        Requests an approach.

        @param InGrid 8 slots around the player to register enemies to.
        @param OutSpot A registered world location to place a creature to.

        @return If its result is Success, the OutSpot parameter is a registered world location, reach it.
                Otherwise, its result is a reason of an error.
    */
    UFUNCTION(BlueprintCallable , BlueprintPure = False) EFTJ_CombatManager_ApproachRegistrationResult TryRegisterApproach(UFTJ_CombatManager_GridBase *const InGrid , FVector & OutSpot) const;
    /*
        Cancels an approach.

        @param InGrid 8 slots around the player to register enemies to.

        @return If its result is Success then cancel an approach.
                Otherwise, its result is a reason of an error.
    */
    UFUNCTION(BlueprintCallable , BlueprintPure = False) EFTJ_CombatManager_ApproachDeregistrationResult TryDeregisterApproach(UFTJ_CombatManager_GridBase *const InGrid) const;
    /*
        Requests an attack.

        @param InGrid 8 slots around the player to register enemies to
        @param InAttackWeight A score to show an attack type, its strength.

        @return If its result is Success then attack the player.
                If its result is CreatureNeedsToBeCloser then go to TryRegisterApproach.
                Otherwise, its result is a reason of an error.
    */
    UFUNCTION(BlueprintCallable , BlueprintPure = False) EFTJ_CombatManager_AttackRegistrationResult TryRegisterAttack(UFTJ_CombatManager_GridBase *const InGrid , int32 const InAttackWeight) const;
    /*
        Cancels an attack.

        @param InGrid 8 slots around the player to register enemies to.

        @return If its result is Success then cancel an attack.
                Otherwise, its result is a reason of an error.
    */
    UFUNCTION(BlueprintCallable , BlueprintPure = False) EFTJ_CombatManager_AttackDeregistrationResult TryDeregisterAttack(UFTJ_CombatManager_GridBase *const InGrid) const;
    /*
        Tests a suggested world location.

        @param InSpot A suggested spot world location.
        @param InGrid A player’s grid world location.

        @return Checks if an enemy is able to reach a spot, returns false if is unable.
                Checks if a spot allows an enemy to attack the player, returns false if doesn’t.
                Can run any additional tests.
                Returns true only if all the tests are successful.
    */
    UFUNCTION(BlueprintNativeEvent) bool IsSpotValid(FVector const& InSpot , FVector const& InGrid) const;
    //Go to IsSpotValid.
    virtual bool IsSpotValid_Implementation(FVector const& InSpot , FVector const& InGrid) const;
    /*
        Implements C++ constructor by copying its parameters into fields

        @param InApproachWeight A score to show an enemy type, its strength.
    */
    UFTJ_CombatManager_CreatureBase(int32 const InApproachWeight);
};