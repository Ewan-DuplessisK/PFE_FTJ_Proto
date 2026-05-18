#pragma once

//

#include"CoreMinimal.h"
#include"BaseMenuWidget.h"
#include"MainMenuWidget.generated.h"

//

UCLASS() class FTHISJOB_API UMainMenuWidget : public UBaseMenuWidget
{
    GENERATED_BODY()

    private:

    protected:

    public:

    UPROPERTY(BlueprintReadWrite) bool bHasBeenActivatedAlready;
    
    private:

    protected:

    virtual void OnChangeLevelClicked() override;
    virtual void OnQuitClicked() override;
    virtual void OnSettingsClicked() override;

    public:

    virtual void NativeConstruct() override;
    virtual void NativeOnActivated() override;

    virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
    virtual class UMainMenuButton* GetFocusedButton() const override;
    
    UFUNCTION(BlueprintImplementableEvent) void SwitchCameraPlay();
    UFUNCTION(BlueprintImplementableEvent) void SwitchCameraSettings();
    UFUNCTION(BlueprintImplementableEvent) void SwitchCameraQuit();
    UFUNCTION(BlueprintImplementableEvent) void SwitchCameraDefault();

    virtual void UnQuit() override;
};