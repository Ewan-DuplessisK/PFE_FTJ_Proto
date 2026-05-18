#pragma once

//

#include"CoreMinimal.h"
#include"UObject/NoExportTypes.h"
#include"FTJ_ScoringSystem_DataBase.generated.h"

//

class UFTJ_ScoringSystem_RankBase;

//

//The UFTJ_ScoringSystem_Data's base compatibility layer.
UCLASS(Blueprintable , EditInlineNew) class FTHISJOB_API UFTJ_ScoringSystem_DataBase : public UObject
{
    GENERATED_BODY()

    private :

    protected :

    public :

    //The time passed before starting to subtract from the gauge after increasing the score level.
    UPROPERTY(EditDefaultsOnly) float GaugeDecreaseImmunityDuration;

    //The score levels' sorted list.
    UPROPERTY(EditDefaultsOnly , Instanced) TArray<UFTJ_ScoringSystem_RankBase *> RankArray;

    private :

    protected :

    public :
};