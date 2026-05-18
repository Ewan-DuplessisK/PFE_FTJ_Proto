#pragma once

//

#include"CoreMinimal.h"
#include"UObject/NoExportTypes.h"
#include"FTJ_ScoringSystem_RankBase.generated.h"

//

//The UFTJ_ScoringSystem_Rank's base compatibility layer.
UCLASS(Blueprintable , EditInlineNew) class FTHISJOB_API UFTJ_ScoringSystem_RankBase : public UObject
{
    GENERATED_BODY()

    private :

    protected :

    public :

    //The value which is affecting the score and which is itself affected by the gauge.
    UPROPERTY(EditDefaultsOnly) float Multiplier;

    //The value subtracted from the gauge every 1 second.
    UPROPERTY(EditDefaultsOnly) float GaugeDecreaseRate;

    private :

    protected :

    public :
};