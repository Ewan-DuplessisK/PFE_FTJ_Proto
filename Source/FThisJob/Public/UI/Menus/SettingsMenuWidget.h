#pragma once

//

#include"CoreMinimal.h"
#include"CommonActivatableWidget.h"
#include"SettingsMenuWidget.generated.h"

//

class USwitcherTabSettings;
class UMainMenuButton;

//

UCLASS() class FTHISJOB_API USettingsMenuWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY(Meta = (BindWidget)) USwitcherTabSettings * SwitcherTabSettings;
    UPROPERTY(Meta = (BindWidget)) UMainMenuButton * BackButton;

    public:

    private:

    protected:
    
    UFUNCTION(BlueprintCallable) void Return();
    UFUNCTION() virtual void OnBackClicked();

    public:

    virtual void NativeConstruct() override;
    virtual FReply NativeOnKeyDown(FGeometry const& InGeometry , FKeyEvent const& InKeyEvent) override;
    virtual void NativeOnFocusLost(FFocusEvent const& InFocusEvent) override;
    virtual void NativeOnActivated() override;

    UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)void OnReturnSound();
    
    class USwitcherTabSettings* GetSwitcherTabSettings() const;
    virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
    UFUNCTION(BlueprintImplementableEvent) void SwitchCameraDefault();
};