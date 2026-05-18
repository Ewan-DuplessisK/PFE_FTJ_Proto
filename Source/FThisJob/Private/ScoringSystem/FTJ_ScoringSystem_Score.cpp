//Header

#include"ScoringSystem/FTJ_ScoringSystem_Score.h"

//Public

void UFTJ_ScoringSystem_Score::IncreaseWithText_Implementation(float InScoreIncrease , float InGaugeIncrease , bool bInIsMultiplierIgnored , FText const& InMessage)
{
    //Use UE_LOG(LogTemp , Log , ...) by default but you can modify it
    Increase(InScoreIncrease , InGaugeIncrease , bInIsMultiplierIgnored);
    UE_LOG(LogTemp , Log , TEXT("%s") , *InMessage.ToString())
}

void UFTJ_ScoringSystem_Score::IncreaseWithEnumeration_Implementation(float InScoreIncrease , float InGaugeIncrease , bool bInIsMultiplierIgnored , EFTJ_ScoringManager_IncreaseMessage const InMessage)
{
    //Use UE_LOG(LogTemp , Log , ...) by default but you can modify it
    IncreaseWithText(InScoreIncrease , InGaugeIncrease , bInIsMultiplierIgnored , FText::FromString(UEnum::GetValueAsString(InMessage)));
}

//

void UFTJ_ScoringSystem_Score::DecreaseWithText_Implementation(float InGaugeDecrease , bool bInIsMultiplierIgnored , FText const& InMessage)
{
    //Use UE_LOG(LogTemp , Log , ...) by default but you can modify it
    Decrease(InGaugeDecrease , bInIsMultiplierIgnored);
    UE_LOG(LogTemp , Log , TEXT("%s") , *InMessage.ToString())
}

void UFTJ_ScoringSystem_Score::DecreaseWithEnumeration_Implementation(float InGaugeDecrease , bool bInIsMultiplierIgnored , EFTJ_ScoringManager_DecreaseMessage const InMessage)
{
    //Use UE_LOG(LogTemp , Log , ...) by default but you can modify it
    DecreaseWithText(InGaugeDecrease , bInIsMultiplierIgnored , FText::FromString(UEnum::GetValueAsString(InMessage)));
}