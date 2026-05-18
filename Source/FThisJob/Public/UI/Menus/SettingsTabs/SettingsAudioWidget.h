#pragma once

//

#include"CoreMinimal.h"
#include"SettingsTabBase.h"
#include"SettingsAudioWidget.generated.h"

//

class USliderSettings;

//

UCLASS() class FTHISJOB_API USettingsAudioWidget : public USettingsTabBase
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) USliderSettings * MasterVolumeSlider;
    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) USliderSettings * VoicesVolumeSlider;
    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) USliderSettings * SFXVolumeSlider;
    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) USliderSettings * MusicVolumeSlider;

    public:

    private:

    protected:

    UFUNCTION() void OnMasterVolumeSliderValueChanged(float Value);
    UFUNCTION() void OnVoicesVolumeSliderValueChanged(float Value);
    UFUNCTION() void OnSFXVolumeSliderValueChanged(float Value);
    UFUNCTION() void OnMusicVolumeSliderValueChanged(float Value);
    
    public:

    virtual void NativeConstruct() override;
    virtual void SetupSettingsValues(USettingsSave * SettingSave) override;
};