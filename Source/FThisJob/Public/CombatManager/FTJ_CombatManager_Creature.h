#pragma once

#include"CoreMinimal.h"
#include"CombatManager/FTJ_CombatManager_CreatureBase.h"
#include"FTJ_CombatManager_Creature.generated.h"

//A grid-assignable enemy.
UCLASS(Blueprintable) class FTHISJOB_API UFTJ_CombatManager_Creature : public UFTJ_CombatManager_CreatureBase
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
    using UFTJ_CombatManager_CreatureBase::UFTJ_CombatManager_CreatureBase;

    //Protected functions
    protected :

    //Public functions
    public :
    //Go to UFTJ_CombatManager_CreatureBase::IsSpotValid.
    virtual bool IsSpotValid_Implementation(FVector const& InSpot , FVector const& InGrid) const override;
};