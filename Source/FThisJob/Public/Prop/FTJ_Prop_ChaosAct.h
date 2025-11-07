#pragma once

#include"CoreMinimal.h"
#include"Prop/FTJ_Prop_ChaosActBase.h"
#include"FTJ_Prop_ChaosAct.generated.h"

//A destructible prop.
UCLASS() class FTHISJOB_API AFTJ_Prop_ChaosAct : public AFTJ_Prop_ChaosActBase
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

    //Protected functions
    protected :

    //Public functions
    public :
    UFUNCTION(BlueprintNativeEvent)
    void DestructionFeedback();
};