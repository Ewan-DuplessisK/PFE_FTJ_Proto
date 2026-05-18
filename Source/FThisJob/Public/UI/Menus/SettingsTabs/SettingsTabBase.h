#pragma once

//

#include"CoreMinimal.h"
#include"CommonActivatableWidget.h"
#include"SettingsTabBase.generated.h"

//

class UScrollBox;
class USettingsSave;

//

UCLASS() class FTHISJOB_API USettingsTabBase : public UCommonActivatableWidget
{
    GENERATED_BODY()

    private:
    
    protected:

    UPROPERTY(Meta = (BindWidget)) UScrollBox * ScrollBox;

    public:

    private:

    protected:

    virtual void NativeConstruct() override;
    
    public:

    virtual UWidget * NativeGetDesiredFocusTarget() const override;
    
    UFUNCTION(BlueprintCallable)
    virtual void SetupSettingsValues(USettingsSave * SettingSave);
    UScrollBox* GetScrollBox() const;
};