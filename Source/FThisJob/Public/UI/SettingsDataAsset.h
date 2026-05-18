#pragma once

//

#include"CoreMinimal.h"
#include"Engine/DataAsset.h"
#include"SettingsDataAsset.generated.h"

//

UCLASS() class FTHISJOB_API USettingsDataAsset : public UDataAsset
{
    GENERATED_BODY()

    private:

    protected:

    public:

    UPROPERTY(EditDefaultsOnly , Category = "Gameplay" , Meta = (ClampMin = "1.0" , ClampMax = "5.0" , DisplayPrecision = "2")) float HorizontalSensitivity{1.2};
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay" , Meta = (ClampMin = "1.0" , ClampMax = "5.0" , DisplayPrecision = "2")) float VerticalSensitivity{0.7};
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay", Meta = (ToolTip = "0 = Normal / 1 = Inverted")) int32 HorizontalAxisIndex{0};
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay", Meta = (ToolTip = "0 = Normal / 1 = Inverted")) int32 VerticalAxisIndex{0};
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") bool Vibration{true};
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") bool CrosshairVisibility{true};
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") bool CameraShake;

    UPROPERTY(EditDefaultsOnly , Category = "Graphics", Meta = (ToolTip = "0 = Low / 1 = Medium / 2 = High / 3 = Ultra / -1 = Custom")) int32 GlobalQuality;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") float ResolutionScale;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics", Meta = (ToolTip = "0 = 30 / 1 = 60 / 2 = 120 / 3 = 144 / 4 = Unlimited")) int32 Framerate;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") bool VSync;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") bool MotionBlur;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") TEnumAsByte<EWindowMode::Type> Display;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics", Meta = (ToolTip = "0 = 1920 x 1080 / 1 = 1680 x 1050 / 2 = 1600 x 900 / 3 = 1440 x 1080 /\n4 = 1440 x 900 / 5 = 1280 x 960 / 6 = 1280 x 800 / 7 = 1280 x 720 /\n8 = 800 x 600 / 9 = 720 x 480 / 10 = 640 x 480")) FIntPoint ScreenResolution;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics", Meta = (ToolTip = "0 = None / 1 = FXAA / 2 = TAA / 4 = TSR")) int32 AntiAliasing;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") float Brightness;
    

    UPROPERTY(EditDefaultsOnly , Category = "Audio", Meta = (ClampMin = "0.", ClampMax = "100.0")) float MasterVolume{100.0};
    UPROPERTY(EditDefaultsOnly , Category = "Audio", Meta = (ClampMin = "0.", ClampMax = "100.0")) float VoicesVolume{100.0};
    UPROPERTY(EditDefaultsOnly , Category = "Audio", Meta = (ClampMin = "0.", ClampMax = "100.0")) float SFXVolume{100.0};
    UPROPERTY(EditDefaultsOnly , Category = "Audio", Meta = (ClampMin = "0.", ClampMax = "100.0")) float MusicVolume{100.0};

    UPROPERTY(EditDefaultsOnly , Category = "Accessibility") TArray<FString> Language;
    UPROPERTY(EditDefaultsOnly , Category = "Accessibility" , Meta = (ClampMin = "0." , ClampMax = "100.0")) float SubtitleBackgroundOpacity{100.0};
    UPROPERTY(EditDefaultsOnly , Category = "Accessibility" , Meta = (ClampMin = "0." , ClampMax = "100.0")) float SubtitleSize{50.0};

    private:

    protected:

    public:
};