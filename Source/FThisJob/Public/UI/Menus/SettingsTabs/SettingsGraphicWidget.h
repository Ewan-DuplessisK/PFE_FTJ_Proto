#pragma once

//

#include"CoreMinimal.h"
#include"SettingsTabBase.h"
#include"SettingsGraphicWidget.generated.h"

//
class UDropdownSettings;
class USliderSettings;
class UCheckBoxSettings;
//

UCLASS() class FTHISJOB_API USettingsGraphicWidget : public USettingsTabBase
{
    GENERATED_BODY()

    private:

    protected:
    UPROPERTY(meta=(BindWidget))
    UDropdownSettings* GlobalQuality;
    UPROPERTY(meta=(BindWidget))
    USliderSettings* ResolutionScale;
    UPROPERTY(meta=(BindWidget))
    UDropdownSettings* Framerate;
    UPROPERTY(meta=(BindWidget))
    UCheckBoxSettings* VSync;
    UPROPERTY(meta=(BindWidget))
    UCheckBoxSettings* MotionBlur;
    UPROPERTY(meta=(BindWidget))
    UDropdownSettings* Display;
    UPROPERTY(meta=(BindWidget))
    UDropdownSettings* ScreenResolution;
    UPROPERTY(meta=(BindWidget))
    UDropdownSettings* AntiAliasing;
    UPROPERTY(meta=(BindWidget))
    USliderSettings* Brightness;


    UFUNCTION() void OnGlobalQualityChanged(UWidget* Widget, int32 Index);
    UFUNCTION() void OnResolutionScaleChanged(float Value);
    UFUNCTION() void OnFramerateChanged(UWidget* Widget, int32 Index);
    UFUNCTION() void OnVSyncChanged(bool bValue);
    UFUNCTION() void OnMotionBlurChanged(bool bValue);
    UFUNCTION() void OnDisplayChanged(UWidget* Widget, int32 Index);
    UFUNCTION() void OnScreenResolutionChanged(UWidget* Widget, int32 Index);
    UFUNCTION() void OnAntiAliasingChanged(UWidget* Widget, int32 Index);
    UFUNCTION() void OnBrightnessChanged(float Value);

    void ApplyWithFocusRestore(UWidget* Widget);
    void ApplyAndSave();

public:

    virtual void NativeConstruct() override;
    virtual void NativeOnActivated() override;
    virtual void NativeOnDeactivated() override;
    virtual void SetupSettingsValues(USettingsSave * SettingSave) override;
};