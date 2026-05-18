#pragma once

//

#include"CoreMinimal.h"
#include"UI/BaseHUD.h"
#include"MainMenuHUD.generated.h"

//

enum class ECommonInputType : uint8;

//

UCLASS() class FTHISJOB_API AMainMenuHUD : public ABaseHUD
{
    GENERATED_BODY()

    private:

    protected:

    public:

    private:
    
    protected:

    virtual void BeginPlay() override;
    UFUNCTION() void HandleInputMethodChanged(ECommonInputType NewInputType) const;

    virtual UBaseMenuWidget * GetPreviousWidget() override;
    virtual USettingsMenuWidget * GetSettingsMenuWidget() const override;

    public:
};
