#pragma once

//

#include"CoreMinimal.h"
#include"ScoringSystem/FTJ_ScoringSystem_ScoreBase.h"
#include"FTJ_ScoringSystem_Score.generated.h"

//

//The enumerated score increase description.
UENUM(BlueprintType) enum struct EFTJ_ScoringManager_IncreaseMessage : uint8
{
    Test
};

//The enumerated score decrease description.
UENUM(BlueprintType) enum struct EFTJ_ScoringManager_DecreaseMessage : uint8
{
    Test
};

//

//The value which is modified depending on the multiplier which is affected by its gauge.
UCLASS() class FTHISJOB_API UFTJ_ScoringSystem_Score : public UFTJ_ScoringSystem_ScoreBase
{
    GENERATED_BODY()

    private :

    protected :

    public :

    private :

    protected :

    public :

    /*
        Increases the score passing an FText as a message.
        Uses UE_LOG(LogTemp , Log , ...) by default but you can modify it.
        Override to transfer its output or to record messages.
        @param InScoreIncrease The value which will be added to the score.
        @param InGaugeIncrease The value which will be added to the gauge.
        @param InMessage The human-readable score increase description.
    */
    UFUNCTION(BlueprintCallable , BlueprintNativeEvent) void IncreaseWithText(float InScoreIncrease , float InGaugeIncrease , bool bInIsMultiplierIgnored , FText const& InMessage);

    /*
        Increases the score passing an EFTJ_ScoringManager_IncreaseMessage as a message.
        Uses UE_LOG(LogTemp , Log , ...) by default but you can modify it.
        Override to transfer its output or to record messages.
        Extend the EFTJ_ScoringManager_IncreaseMessage enumeration to add new messages here.
        @param InScoreIncrease The value which will be added to the score.
        @param InGaugeIncrease The value which will be added to the gauge.
        @param InMessage The enumerated score increase description.
    */
    UFUNCTION(BlueprintCallable , BlueprintNativeEvent) void IncreaseWithEnumeration(float InScoreIncrease , float InGaugeIncrease , bool bInIsMultiplierIgnored , EFTJ_ScoringManager_IncreaseMessage const InMessage);

    //
    
    /*
        Decreases the score passing an FText as a message.
        Uses UE_LOG(LogTemp , Log , ...) by default but you can modify it.
        Override to transfer its output or to record messages.
        @param InGaugeDecrease The value which will be subtracted from the gauge.
        @param InMessage The human-readable score decrease description.
    */
    UFUNCTION(BlueprintCallable , BlueprintNativeEvent) void DecreaseWithText(float InGaugeDecrease , bool bInIsMultiplierIgnored , FText const& InMessage);

    /*
        Decreases the score passing an EFTJ_ScoringManager_DecreaseMessage as a message.
        Uses UE_LOG(LogTemp , Log , ...) by default but you can modify it.
        Override to transfer its output or to record messages.
        Extend the EFTJ_ScoringManager_DecreaseMessage enumeration to add new messages here.
        @param InGaugeDecrease The value which will be subtracted from the gauge.
        @param InMessage The enumerated score decrease description.
    */
    UFUNCTION(BlueprintCallable , BlueprintNativeEvent) void DecreaseWithEnumeration(float InGaugeDecrease , bool bInIsMultiplierIgnored , EFTJ_ScoringManager_DecreaseMessage const InMessage);
};