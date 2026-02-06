#include"Progress/FTJ_Progress_ProgressBase.h"

bool UFTJ_Progress_ProgressBase::ShouldCreateSubsystem(UObject * InOwner) const
{
    //Call the base and check if the subsystem has a correct class to be initialized
    return(Super::ShouldCreateSubsystem(InOwner) && GetClass() == ClassOfSubsystemToInitialize);
}

void UFTJ_Progress_ProgressBase::Initialize(FSubsystemCollectionBase & InCollection)
{
    //Delegate to USubsystem
    Super::Initialize(InCollection);
    //End the creation, transferring the control to a blueprint
    InitializeBlueprint();
}

void UFTJ_Progress_ProgressBase::Deinitialize()
{
    //Begin the destruction, transferring the control to a blueprint
    DeinitializeBlueprint();
    //Delegate to USubsystem
    Super::Deinitialize();
}