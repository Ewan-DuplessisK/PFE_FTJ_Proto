//Header

#include"ScoringSystem/FTJ_ScoringSystem_ScoreBase.h"

#include"ScoringSystem/FTJ_ScoringSystem_DataBase.h"
#include"ScoringSystem/FTJ_ScoringSystem_RankBase.h"

//Private

bool UFTJ_ScoringSystem_ScoreBase::ShouldCreateSubsystem(UObject * InOwner) const
{
    //Call the base and check if the subsystem has a correct class to be initialized
    return(Super::ShouldCreateSubsystem(InOwner) && GetClass() == ClassOfSubsystemToInitialize);
}

//

void UFTJ_ScoringSystem_ScoreBase::Initialize(FSubsystemCollectionBase & InCollection)
{
    //Delegate to USubsystem
    Super::Initialize(InCollection);
    //End the creation, transferring the control to a blueprint
    InitializeBlueprint();
    Unpause();
}

void UFTJ_ScoringSystem_ScoreBase::Deinitialize()
{
    Pause();
    //Begin the destruction, transferring the control to a blueprint
    DeinitializeBlueprint();
    //Delegate to USubsystem
    Super::Deinitialize();
}

//

float UFTJ_ScoringSystem_ScoreBase::PredictRankIndex(float InGaugeIncrease) const
{
    return(FMath::Clamp(RankIndex + InGaugeIncrease , 0.0 , Data->RankArray.Num() - UE_DOUBLE_KINDA_SMALL_NUMBER));
}

void UFTJ_ScoringSystem_ScoreBase::ConfigureGaugeDecreaseTimer(float InDelay)
{
    //Configure the timer manipulating the multiplier gauge decrease process
    GetWorld()->GetTimerManager().SetTimer
    (
        GaugeDecreaseTimer , [&]
        {
            //Replace Tick by a timer
            Decrease(Data->RankArray[RankIndex]->GaugeDecreaseRate * GetWorld()->GetTimerManager().GetTimerElapsed(GaugeDecreaseTimer) , false);
        }
        , 0.001 , true , InDelay
    );
}

//

float UFTJ_ScoringSystem_ScoreBase::GetMultiplier() const
{
    return(Data->RankArray[RankIndex]->Multiplier);
}

float UFTJ_ScoringSystem_ScoreBase::GetGauge() const
{
    return(RankIndex - FMath::TruncToInt(RankIndex));
}

//Public

void UFTJ_ScoringSystem_ScoreBase::Increase(float InScoreIncrease , float InGaugeIncrease , bool bInIsMultiplierIgnored)
{
    //Increase the score itself before increasing the multiplier gauge
    Score += InScoreIncrease * (bInIsMultiplierIgnored ? 1.0 : Data->RankArray[RankIndex]->Multiplier);
    //Check the multiplier gauge bounds
    if(auto Transition{FMath::TruncToInt(PredictRankIndex(InGaugeIncrease)) - FMath::TruncToInt(RankIndex)} ; Transition)
    {
        //Check the multiplier gauge underflow
        if(Transition < 0)
        {
            //Check trance state
            if(RankIndex >= Data->RankArray.Num() - 1)
            {
                //Decrease only on the underflow
                RankIndex = PredictRankIndex(-1.0);
                OnTransitionedTrance(false);
            }
            OnTransitionedLower();
        }
        //Check the multiplier gauge overflow
        else
        {
            //Check trance state
            if(PredictRankIndex(InGaugeIncrease) >= Data->RankArray.Num() - 1)
            {
                //Increase only on the overflow
                RankIndex = PredictRankIndex(+1.0);
                OnTransitionedTrance(true);
            }
            //Configure the timer manipulating the multiplier gauge decrease process
            else
            {
                ConfigureGaugeDecreaseTimer(Data->GaugeDecreaseImmunityDuration);
            }
            OnTransitionedHigher();
        }
    }
    //Do it without a buffer
    RankIndex = PredictRankIndex(InGaugeIncrease);
}

void UFTJ_ScoringSystem_ScoreBase::Decrease(float InGaugeDecrease , bool bInIsMultiplierIgnored)
{
    Increase(0.0 , -InGaugeDecrease , bInIsMultiplierIgnored);
}

//

void UFTJ_ScoringSystem_ScoreBase::Pause()
{
    GetWorld()->GetTimerManager().ClearTimer(GaugeDecreaseTimer);
}

void UFTJ_ScoringSystem_ScoreBase::Unpause()
{
    ConfigureGaugeDecreaseTimer();
}

//

void UFTJ_ScoringSystem_ScoreBase::Reset()
{
    RankIndex = 0.0;
}