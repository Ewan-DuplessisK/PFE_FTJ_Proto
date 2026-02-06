#pragma once

#include"CoreMinimal.h"
#include"Subsystems/GameInstanceSubsystem.h"
#include"FTJ_ScoringSystem_ScoreBase.generated.h"

//A score's base for compatibility.
UCLASS() class FTHISJOB_API UFTJ_ScoringSystem_ScoreBase : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    //Private variables
    private :
    UPROPERTY(EditDefaultsOnly , AdvancedDisplay) TSubclassOf<UFTJ_ScoringSystem_ScoreBase> ClassOfSubsystemToInitialize;
    //A value which is increased depending on the multiplier which is affected by its percentage.
    int32 Score;
    //A value which is affecting the score and which is itself affected by the percentage.
    int32 Multiplier;
    //A value which increments the multiplier when hitting 99 and resets itself (and vice versa).
    int32 MultiplierPercentage;
    //A timer handle manipulating the multiplier percentage decrease process.
    FTimerHandle MultiplierPercentageDecreaseTimer;

    //Protected variables
    protected :
    //Time passed before starting to subtract the MultiplierPercentageDecrease from the MultiplierPercentage.
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (ExposeOnSpawn = True)) float MultiplierPercentageDecreaseDelay;
    //Time between subtractions of the MultiplierPercentageDecrease from the MultiplierPercentage.
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (ExposeOnSpawn = True)) float MultiplierPercentageDecreaseRate;
    //A value which is subtracted from the MultiplierPercentage every MultiplierPercentageDecreaseRate seconds after passing MultiplierPercentageDecreaseDelay seconds.
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (ExposeOnSpawn = True)) int32 MultiplierPercentageDecrease;

    //Public variables
    public :

    //Private functions
    private :

    //Protected functions
    protected :
    //Implements C++ constructor as a stub for Unreal Engine and as the Multiplier field initializer.
    UFTJ_ScoringSystem_ScoreBase();
    virtual bool ShouldCreateSubsystem(UObject * InOwner) const override;
    virtual void Initialize(FSubsystemCollectionBase & InCollection) override;
    virtual void Deinitialize() override;
    UFUNCTION(BlueprintImplementableEvent) void InitializeBlueprint();
    UFUNCTION(BlueprintImplementableEvent) void DeinitializeBlueprint();

    //Public functions
    public :
    /*
        Implements the Score field getter.

        @return A value which is increased depending on the multiplier which is affected by its percentage.
    */
    UFUNCTION(BlueprintCallable) int32 GetScore() const;
    /*
        Implements the Multiplier field getter.

        @return A value which is affecting the score and which is itself affected by the percentage.
    */
    UFUNCTION(BlueprintCallable) int32 GetMultiplier() const;
    /*
        Implements the MultiplierPercentage field getter.

        @return A value which increments the multiplier when hitting 99 and resets itself (and vice versa).
    */
    UFUNCTION(BlueprintCallable) int32 GetMultiplierPercentage() const;
    /*
        Implements C++ constructor by copying its parameters into fields.

        @param InMultiplierPercentageDecreaseDelay Time passed before starting to subtract the MultiplierPercentageDecrease from the MultiplierPercentage.
        @param InMultiplierPercentageDecreaseRate Time between subtractions of the MultiplierPercentageDecrease from the MultiplierPercentage.
        @param InMultiplierPercentageDecrease A value which is subtracted from the MultiplierPercentage every MultiplierPercentageDecreaseRate seconds after passing MultiplierPercentageDecreaseDelay seconds.
    */
    UFTJ_ScoringSystem_ScoreBase(float const InMultiplierPercentageDecreaseDelay , float const InMultiplierPercentageDecreaseRate , int32 const InMultiplierPercentageDecrease);
    /*
        Just modifies the score itself.

        @param InScoreIncrease A value which will be added to the score.
        @param InMultiplierPercentageIncrease A value which will be added to the MultiplierPercentage.
    */
    UFUNCTION(BlueprintCallable) void Increase(int32 const InScoreIncrease , int32 const InMultiplierPercentageIncrease);
    UFUNCTION(BlueprintCallable) void SetScore(int32 InValue);
    UFUNCTION(BlueprintCallable) void SetMultiplier(int32 InValue);
    UFUNCTION(BlueprintCallable) void SetMultiplierPercentage(int32 InValue);
};