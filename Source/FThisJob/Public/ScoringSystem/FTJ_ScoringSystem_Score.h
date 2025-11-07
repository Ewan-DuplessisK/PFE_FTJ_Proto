#pragma once

#include"CoreMinimal.h"
#include"ScoringSystem/FTJ_ScoringSystem_ScoreBase.h"
#include"FTJ_ScoringSystem_Score.generated.h"

//An enumerated score change description.
UENUM(BlueprintType) enum struct EFTJ_ScoringManager_Message : uint8
{
    Test
};

//A value which is increased depending on the multiplier which is affected by its percentage.
UCLASS(Blueprintable) class FTHISJOB_API UFTJ_ScoringSystem_Score : public UFTJ_ScoringSystem_ScoreBase
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
    using UFTJ_ScoringSystem_ScoreBase::UFTJ_ScoringSystem_ScoreBase;

    //Protected functions
    protected :

    //Public functions
    public :
    /*
        Modifies the score passing an FText as a message.
        Uses UE_LOG(LogTemp , Log , ...) by default but you can change it.
        Override to transfer its output or to record messages.

        @param InScoreIncrease A value which will be added to the score.
        @param InMultiplierPercentageIncrease A value which will be added to the MultiplierPercentage.
        @param InMessage A human-readable score change description.
    */
    UFUNCTION(BlueprintCallable , BlueprintNativeEvent) void IncreaseWithText(int32 const InScoreIncrease , int32 const InMultiplierPercentageIncrease , FText const& InMessage);
    //Go to IncreaseWithText.
    void IncreaseWithText_Implementation(int32 const InScoreIncrease , int32 const InMultiplierPercentageIncrease , FText const& InMessage);
    /*
        Modifies the score passing an EFTJ_ScoringManager_Message  as a message.
        Uses UE_LOG(LogTemp , Log , ...) by default but you can change it.
        Override to transfer its output or to record messages.
        Extend the EFTJ_ScoringManager_Message enumeration to add new messages here.

        @param InScoreIncrease A value which will be added to the score.
        @param InMultiplierPercentageIncrease A value which will be added to the MultiplierPercentage.
        @param InMessage An enumerated score change description.
    */
    UFUNCTION(BlueprintCallable , BlueprintNativeEvent) void IncreaseWithEnumeration(int32 const InScoreIncrease , int32 const InMultiplierPercentageIncrease , EFTJ_ScoringManager_Message const InMessage);
    //Go to IncreaseWithEnumeration.
    void IncreaseWithEnumeration_Implementation(int32 const InScoreIncrease , int32 const InMultiplierPercentageIncrease , EFTJ_ScoringManager_Message const InMessage);
};