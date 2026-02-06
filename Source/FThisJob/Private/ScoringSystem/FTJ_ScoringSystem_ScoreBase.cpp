#include"ScoringSystem/FTJ_ScoringSystem_ScoreBase.h"

#include"ScoringSystem/FTJ_ScoringSystem_Score.h"

UFTJ_ScoringSystem_ScoreBase::UFTJ_ScoringSystem_ScoreBase()
{
    //Just copy defaults into fields and also don't forget that the multiplier starts with 1
    Score = 0;
    Multiplier = 1;
    MultiplierPercentage = 0;
}

bool UFTJ_ScoringSystem_ScoreBase::ShouldCreateSubsystem(UObject * InOwner) const
{
    return(Super::ShouldCreateSubsystem(InOwner) && GetClass() == ClassOfSubsystemToInitialize);
}

void UFTJ_ScoringSystem_ScoreBase::Initialize(FSubsystemCollectionBase & InCollection)
{
    Super::Initialize(InCollection);
    InitializeBlueprint();
}

void UFTJ_ScoringSystem_ScoreBase::Deinitialize()
{
    DeinitializeBlueprint();
    Super::Deinitialize();
}

int32 UFTJ_ScoringSystem_ScoreBase::GetScore() const
{
    //Just return a copy directly
    return(Score);
}

int32 UFTJ_ScoringSystem_ScoreBase::GetMultiplier() const
{
    //Just return a copy directly
    return(Multiplier);
}

int32 UFTJ_ScoringSystem_ScoreBase::GetMultiplierPercentage() const
{
    //Just return a copy directly
    return(MultiplierPercentage);
}

UFTJ_ScoringSystem_ScoreBase::UFTJ_ScoringSystem_ScoreBase
(
    float const InMultiplierPercentageDecreaseDelay
    ,
    float const InMultiplierPercentageDecreaseRate
    ,
    int32 const InMultiplierPercentageDecrease
)
: UFTJ_ScoringSystem_ScoreBase{}
{
    //Just copy parameters into fields
    MultiplierPercentageDecreaseDelay = InMultiplierPercentageDecreaseDelay;
    MultiplierPercentageDecreaseRate = InMultiplierPercentageDecreaseRate;
    MultiplierPercentageDecrease = InMultiplierPercentageDecrease;
}

void UFTJ_ScoringSystem_ScoreBase::Increase(int32 const InScoreIncrease , int32 const InMultiplierPercentageIncrease)
{
    //Increase the score itself before increasing the multiplier percentage
    Score += InScoreIncrease * Multiplier;
    //Do it without a buffer
    MultiplierPercentage += InMultiplierPercentageIncrease;
    //Check the multiplier percentage overflow
    if(MultiplierPercentage >= 100)
    {
        //Don't forget about the surplus
        MultiplierPercentage -= 100;
        //Increase only on the oversflow
        Multiplier++;
    }
    //Configure the timer manipulating the multiplier percentage decrease process
    GetWorld()->GetTimerManager().SetTimer
    (
        MultiplierPercentageDecreaseTimer
        ,
        [&]
        {
            //Do it every MultiplierPercentageDecreaseRate seconds
            MultiplierPercentage -= MultiplierPercentageDecrease;
            //Check the multiplier percentage underflow
            if(MultiplierPercentage < 0)
            {
                //Don't forget about the deficiency
                MultiplierPercentage += 100;
                //Decrease only on the underflow
                Multiplier--;
                //Check the decrease halt threshold
                if(Multiplier == 0)
                {
                    //Restore default values
                    MultiplierPercentage = 0;
                    Multiplier = 1;
                    GetWorld()->GetTimerManager().ClearTimer(MultiplierPercentageDecreaseTimer);
                }
            }
        }
        ,
        MultiplierPercentageDecreaseRate
        ,
        true
        ,
        MultiplierPercentageDecreaseDelay
    );
}

void UFTJ_ScoringSystem_ScoreBase::SetScore(int32 InValue)
{
    Score = InValue;
}

void UFTJ_ScoringSystem_ScoreBase::SetMultiplier(int32 InValue)
{
    Multiplier = InValue;
}

void UFTJ_ScoringSystem_ScoreBase::SetMultiplierPercentage(int32 InValue)
{
    MultiplierPercentage = InValue;
}