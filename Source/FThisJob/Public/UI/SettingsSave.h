#pragma once

//

#include"CoreMinimal.h"
#include"GameFramework/SaveGame.h"
#include"SettingsSave.generated.h"

//

class USettingsDataAsset;

//

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsChanged);

//

UCLASS() class FTHISJOB_API USettingsSave : public USaveGame
{
    GENERATED_BODY()

    private:
    
    protected:

    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") float HorizontalSensitivity;
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") float VerticalSensitivity;
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") int32 HorizontalAxisIndex;
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") int32 VerticalAxisIndex;
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") bool Vibration;
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") bool CameraShake;
    UPROPERTY(EditDefaultsOnly , Category = "Gameplay") bool CrosshairVisibility;

    UPROPERTY(EditDefaultsOnly , Category = "Audio") float MasterVolume;
    UPROPERTY(EditDefaultsOnly , Category = "Audio") float VoicesVolume;
    UPROPERTY(EditDefaultsOnly , Category = "Audio") float SFXVolume;
    UPROPERTY(EditDefaultsOnly , Category = "Audio") float MusicVolume;
    
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") int32 GlobalQuality;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") float ResolutionScale;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") int32 Framerate;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") bool bIsVSync;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") bool bIsMotionBlur;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") TEnumAsByte<EWindowMode::Type> Display;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") FIntPoint ScreenResolution;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") int32 AntiAliasing;
    UPROPERTY(EditDefaultsOnly , Category = "Graphics") float Brightness;


    public:

    UPROPERTY(EditDefaultsOnly , BlueprintCallable , BlueprintAssignable , Category = "Events") FOnSettingsChanged OnSettingsChanged;

    private:

    protected:

    public:

    UFUNCTION() void InitializeFromDefaults(USettingsDataAsset * DefaultData);

    UFUNCTION(BlueprintCallable) float GetHorizontalSensitivity() const;
    UFUNCTION(blueprintCallable) float GetVerticalSensitivity() const;
    UFUNCTION(BlueprintCallable) int32 GetHorizontalAxis() const;
    UFUNCTION(blueprintCallable) int32 GetVerticalAxis() const;
    UFUNCTION(BlueprintCallable) bool GetVibration() const;
    UFUNCTION(BlueprintCallable) bool GetCameraShake() const;
    UFUNCTION(BlueprintCallable) bool GetCrosshairVisibility() const;
    
    UFUNCTION(BlueprintCallable) float GetMasterVolume() const;
    UFUNCTION(BlueprintCallable) float GetVoicesVolume() const;
    UFUNCTION(BlueprintCallable) float GetSFXVolume() const;
    UFUNCTION(BlueprintCallable) float GetMusicVolume() const;
    
    UFUNCTION(BlueprintCallable) int32 GetGlobalQuality() const;
    UFUNCTION(blueprintCallable) float GetResolutionScale() const;
    UFUNCTION(blueprintCallable) int32 GetFramerate() const;
    UFUNCTION(blueprintCallable) bool GetIsVSync() const;
    UFUNCTION(blueprintCallable) bool GetIsMotionBlur() const;
    UFUNCTION(blueprintCallable) TEnumAsByte<EWindowMode::Type> GetDisplay() const;
    UFUNCTION(blueprintCallable) FIntPoint const& GetScreenResolution() const;
    UFUNCTION(blueprintCallable) int32 GetAntiAliasing() const;
    UFUNCTION(blueprintCallable) float GetBrightness() const;


    UFUNCTION() void SetHorizontalSensitivity(float Value);
    UFUNCTION() void SetVerticalSensitivity(float Value);
    UFUNCTION() void SetHorizontalAxis(int32 Index);
    UFUNCTION() void SetVerticalAxis(int32 Index);
    UFUNCTION() void SetVibration(bool bValue);
    UFUNCTION() void SetCameraShake(bool bValue);
    UFUNCTION() void SetCrosshairVisibility(bool bValue);
    
    UFUNCTION() void SetMasterVolume(float Value);
    UFUNCTION() void SetVoicesVolume(float Value);
    UFUNCTION() void SetSFXVolume(float Value);
    UFUNCTION() void SetMusicVolume(float Value);

    UFUNCTION() void SetGlobalQuality(int32 Value);
    UFUNCTION() void SetResolutionScale(float Value);
    UFUNCTION() void SetFramerate(int32 Value);
    UFUNCTION() void SetIsVSync(bool Value);
    UFUNCTION() void SetIsMotionBlur(bool Value);
    UFUNCTION() void SetDisplay(TEnumAsByte<EWindowMode::Type> Value);
    UFUNCTION() void SetScreenResolution(FIntPoint const& Value);
    UFUNCTION() void SetAntiAliasing(int32 Value);
    UFUNCTION() void SetBrightness(float Value);
};