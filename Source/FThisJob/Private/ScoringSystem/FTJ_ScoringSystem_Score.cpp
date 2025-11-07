#include"ScoringSystem/FTJ_ScoringSystem_Score.h"

void UFTJ_ScoringSystem_Score::IncreaseWithText_Implementation(int32 const InScoreIncrease , int32 const InMultiplierPercentageIncrease , FText const& InMessage)
{
    //Use UE_LOG(LogTemp , Log , ...) by default but you can change it
    Increase(InScoreIncrease , InMultiplierPercentageIncrease);
    UE_LOG(LogTemp , Log , TEXT("%s") , *InMessage.ToString())
}

void UFTJ_ScoringSystem_Score::IncreaseWithEnumeration_Implementation(int32 const InScoreIncrease , int32 const InMultiplierPercentageIncrease , EFTJ_ScoringManager_Message const InMessage)
{
    //Use UE_LOG(LogTemp , Log , ...) by default but you can change it
    IncreaseWithText(InScoreIncrease , InMultiplierPercentageIncrease , FText::FromString(UEnum::GetValueAsString(InMessage)));
}