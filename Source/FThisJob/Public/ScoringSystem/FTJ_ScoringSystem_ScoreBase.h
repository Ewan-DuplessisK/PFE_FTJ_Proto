#pragma once

//

#include"CoreMinimal.h"
#include"Subsystems/GameInstanceSubsystem.h"
#include"FTJ_ScoringSystem_ScoreBase.generated.h"

//

class UFTJ_ScoringSystem_DataBase;

//

//The UFTJ_ScoringSystem_Score's base compatibility layer.
UCLASS(Blueprintable) class FTHISJOB_API UFTJ_ScoringSystem_ScoreBase : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    private :

    //The timer handle manipulating the multiplier gauge decrease process.
    FTimerHandle GaugeDecreaseTimer;

    //The score information.
    UPROPERTY(EditDefaultsOnly , Instanced , AdvancedDisplay) UFTJ_ScoringSystem_DataBase * Data;

    //The system type to create only the final one.
    UPROPERTY(EditDefaultsOnly , AdvancedDisplay) TSubclassOf<UFTJ_ScoringSystem_ScoreBase> ClassOfSubsystemToInitialize;

    protected :

    //The value which is modified depending on the multiplier which is affected by its gauge.
    UPROPERTY(BlueprintReadWrite) float Score;
    //The value combining the rank and the gauge simultaneously.
    UPROPERTY(BlueprintReadWrite) float RankIndex;

    public :

    private :

    /*
        Calls the base and checks if the subsystem has a correct class to be initialized.
        For parameters and the return value, go to USubsystem::ShouldCreateSubsystem.
    */
    bool ShouldCreateSubsystem(UObject * InOwner) const override;

    //
    
    /*
        Calls the base and transfers the control to InitializeBlueprint.
        For parameters, go to USubsystem::Initialize.
    */
    void Initialize(FSubsystemCollectionBase & InCollection) override;

    /*
        Transfers the control to DeinitializeBlueprint and calls the base.
        For parameters, go to USubsystem::Deinitialize.
    */
    void Deinitialize() override;

    //
    
    /*
        Evaluates RankIndex achieved through modification.
        @param InGaugeIncrease The value which will be added to the gauge.
    */
    float PredictRankIndex(float InGaugeIncrease) const;

    /*
        Configures the timer manipulating the multiplier gauge decrease process.
        @param InDelay The time passed before starting to subtract from the gauge after increasing the score level.
    */
    void ConfigureGaugeDecreaseTimer(float InDelay = 0.0);

    //
    
    /*
        Extracts from RankIndex.
        @return The value which is affecting the score and which is itself affected by the gauge.
    */
    UFUNCTION(BlueprintCallable) float GetMultiplier() const;

    /*
        Extracts from RankIndex.
        @return The value which increments the multiplier when hitting 1.0 and resets itself (and vice versa).
    */
    UFUNCTION(BlueprintCallable) float GetGauge() const;

    protected :

    /*
        Fires on S+ rank reached.
        @param bInEntered The signal indicating whether the transitioning is to the trance (true) or from it (false).
    */
    UFUNCTION(BlueprintImplementableEvent) void OnTransitionedTrance(bool bInEntered);

    //

    //Ends the subsystem creation after its C++ Initialize counterpart.
    UFUNCTION(BlueprintImplementableEvent) void InitializeBlueprint();

    //Begins the subsystem destruction before its C++ Deinitialize counterpart.
    UFUNCTION(BlueprintImplementableEvent) void DeinitializeBlueprint();

    //

    UFUNCTION(BlueprintImplementableEvent) void OnTransitionedLower();

    UFUNCTION(BlueprintImplementableEvent) void OnTransitionedHigher();

    public :

    /*
        Just increases the score itself.
        @param InScoreIncrease The value which will be added to the score.
        @param InGaugeIncrease The value which will be added to the gauge.
    */
    UFUNCTION(BlueprintCallable) void Increase(float InScoreIncrease , float InGaugeIncrease , bool bInIsMultiplierIgnored);

    /*
        Just decreases the score itself.
        @param InGaugeDecrease The value which will be subtracted from the gauge.
    */
    UFUNCTION(BlueprintCallable) void Decrease(float InGaugeDecrease , bool bInIsMultiplierIgnored);
    
    //
    
    //Pauses the timer manipulating the multiplier gauge decrease process.
    UFUNCTION(BlueprintCallable) void Pause();

    //Unpauses the timer manipulating the multiplier gauge decrease process.
    UFUNCTION(BlueprintCallable) void Unpause();

    //

    //Sets default RankIndex.
    UFUNCTION(BlueprintCallable) void Reset();
};