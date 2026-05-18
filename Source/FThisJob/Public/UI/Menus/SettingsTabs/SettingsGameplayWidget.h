#pragma once

//

#include"CoreMinimal.h"
#include"SettingsTabBase.h"
#include"SettingsGameplayWidget.generated.h"

//

class USliderSettings;
class UCheckBoxSettings;
class UDropdownSettings;

//

UCLASS() class FTHISJOB_API USettingsGameplayWidget : public USettingsTabBase
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY(Meta = (BindWidget)) USliderSettings * HorizontalSensitivitySlider;
    UPROPERTY(Meta = (BindWidget)) USliderSettings * VerticalSensitivitySlider;
    UPROPERTY(BlueprintReadOnly ,Meta = (BindWidget)) UCheckBoxSettings * VibrationCheckBox;
    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) UCheckBoxSettings * CrosshairCheckBox;
    UPROPERTY(Meta = (BindWidget)) UCheckBoxSettings * CameraShakeCheckBox;
    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) UDropdownSettings * InvertVerticalDropdown;
    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) UDropdownSettings * InvertHorizontalDropdown;

    public:

    private:

    protected:

    UFUNCTION() void OnHorizontalSensitivitySliderValueChanged(float Value);
    UFUNCTION() void OnVerticalSensitivitySliderValueChanged(float Value);
    UFUNCTION() void OnHorizontalAxisDropdownChanged(UWidget* Widget, int32 Index);
    UFUNCTION() void OnVerticalAxisDropdownChanged(UWidget* Widget, int32 Index);
    UFUNCTION() void OnVibrationChanged(bool bValue);
    UFUNCTION() void OnCrosshairChanged(bool bValue);
    UFUNCTION() void OnCameraShakeChanged(bool bValue);

    public:

    virtual void NativeConstruct() override;
    virtual void SetupSettingsValues(USettingsSave * SettingSave) override;
};