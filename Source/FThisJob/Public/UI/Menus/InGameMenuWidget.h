#pragma once

//

#include"CoreMinimal.h"
#include"CommonActivatableWidget.h"
#include"InGameMenuWidget.generated.h"

//

UCLASS() class FTHISJOB_API UInGameMenuWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()

    private:

    protected:

    public:

    private:

    virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

    protected:

    public:
};