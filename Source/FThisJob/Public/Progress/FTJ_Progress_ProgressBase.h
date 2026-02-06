#pragma once

#include"CoreMinimal.h"
#include"Subsystems/GameInstanceSubsystem.h"
#include"FTJ_Progress_ProgressBase.generated.h"

//A UFTJ_Progress_Progress base compatibility layer.
UCLASS() class FTHISJOB_API UFTJ_Progress_ProgressBase : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    //Private variables
    private :
    //The system type to create only the final one.
    UPROPERTY(EditDefaultsOnly , AdvancedDisplay) TSubclassOf<UFTJ_Progress_ProgressBase> ClassOfSubsystemToInitialize;

    //Protected variables
    protected :

    //Public variables
    public :

    //Private functions
    private :

    //Protected functions
    protected :
    /*
        Calls the base and checks if the subsystem has a correct class to be initialized.
        For parameters and the return value, go to USubsystem::ShouldCreateSubsystem.
    */
    virtual bool ShouldCreateSubsystem(UObject * InOwner) const override;
    /*
        Calls the base and transfers the control to InitializeBlueprint.
        For parameters, go to USubsystem::Initialize.
    */
    virtual void Initialize(FSubsystemCollectionBase & InCollection) override;
    /*
        Transfers the control to DeinitializeBlueprint and calls the base.
        For parameters, go to USubsystem::Deinitialize.
    */
    virtual void Deinitialize() override;
    //Ends the subsystem creation after its C++ Initialize counterpart.
    UFUNCTION(BlueprintImplementableEvent) void InitializeBlueprint();
    //Begins the subsystem destruction before its C++ Deinitialize counterpart.
    UFUNCTION(BlueprintImplementableEvent) void DeinitializeBlueprint();

    //Public functions
    public :
};