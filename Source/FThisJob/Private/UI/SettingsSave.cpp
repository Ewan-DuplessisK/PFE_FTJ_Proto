//Header

#include"UI/SettingsSave.h"

#include"UI/SettingsDataAsset.h"

#include"Kismet/GameplayStatics.h"

//Private

//Protected

//Public

void USettingsSave::InitializeFromDefaults(USettingsDataAsset * DefaultData)
{
    if(!ensure(DefaultData))
    {
        return;
    }
    // General
    Vibration = DefaultData->Vibration;
    CameraShake = DefaultData->CameraShake;
    HorizontalSensitivity = DefaultData->HorizontalSensitivity;
    VerticalSensitivity = DefaultData->VerticalSensitivity;
    HorizontalAxisIndex = DefaultData->HorizontalAxisIndex;
    VerticalAxisIndex = DefaultData->VerticalAxisIndex;
    CrosshairVisibility = DefaultData->CrosshairVisibility;

    //Audio
    MasterVolume = DefaultData->MasterVolume;
    VoicesVolume = DefaultData->VoicesVolume;
    SFXVolume = DefaultData->SFXVolume;
    MusicVolume = DefaultData->MusicVolume;

    //Graphics
    GlobalQuality = DefaultData->GlobalQuality;
    ResolutionScale = DefaultData->ResolutionScale;
    Framerate = DefaultData->Framerate;
    bIsVSync = DefaultData->VSync;
    bIsMotionBlur = DefaultData->MotionBlur;
    Display = DefaultData->Display;
    ScreenResolution = DefaultData->ScreenResolution;
    AntiAliasing = DefaultData->AntiAliasing;
    Brightness = DefaultData->Brightness;
}

//

float USettingsSave::GetHorizontalSensitivity() const
{
    return(HorizontalSensitivity);
}

float USettingsSave::GetVerticalSensitivity() const
{
    return(VerticalSensitivity);
}

int32 USettingsSave::GetHorizontalAxis() const
{
    return(HorizontalAxisIndex);
}

int32 USettingsSave::GetVerticalAxis() const
{
    return(VerticalAxisIndex);
}

bool USettingsSave::GetVibration() const
{
    return(Vibration);
}

bool USettingsSave::GetCameraShake() const
{
    return(CameraShake);
}

bool USettingsSave::GetCrosshairVisibility() const
{
    return CrosshairVisibility;
}

float USettingsSave::GetMasterVolume() const
{
    return(MasterVolume);
}

float USettingsSave::GetVoicesVolume() const
{
    return(VoicesVolume);
}

float USettingsSave::GetSFXVolume() const
{
    return(SFXVolume);
}

float USettingsSave::GetMusicVolume() const
{
    return(MusicVolume);
}

int32 USettingsSave::GetGlobalQuality() const
{
    return(GlobalQuality);
}

float USettingsSave::GetResolutionScale() const
{
    return(ResolutionScale);
}

int32 USettingsSave::GetFramerate() const
{
    return(Framerate);
}

bool USettingsSave::GetIsVSync() const
{
    return(bIsVSync);
}

bool USettingsSave::GetIsMotionBlur() const
{
    return(bIsMotionBlur);
}

TEnumAsByte<EWindowMode::Type> USettingsSave::GetDisplay() const
{
    return(Display);
}

FIntPoint const& USettingsSave::GetScreenResolution() const
{
    return(ScreenResolution);
}

int32 USettingsSave::GetAntiAliasing() const
{
    return(AntiAliasing);
}

float USettingsSave::GetBrightness() const
{
    return(Brightness);
}

//

void USettingsSave::SetHorizontalSensitivity(float Value)
{
    HorizontalSensitivity = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this , TEXT("Settings") , 0);
}

void USettingsSave::SetVerticalSensitivity(float Value)
{
    VerticalSensitivity = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this , TEXT("Settings") , 0);
}

void USettingsSave::SetHorizontalAxis(int32 Index)
{
    HorizontalAxisIndex = Index;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"),0);
}

void USettingsSave::SetVerticalAxis(int32 Index)
{
    VerticalAxisIndex = Index;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"),0);
}

void USettingsSave::SetVibration(bool bValue)
{
    Vibration = bValue;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this , TEXT("Settings") , 0);
}

void USettingsSave::SetCameraShake(bool bValue)
{
    CameraShake = bValue;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this , TEXT("Settings") , 0);
}

void USettingsSave::SetCrosshairVisibility(bool bValue)
{
    CrosshairVisibility = bValue;;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this , TEXT("Settings") , 0);
}

void USettingsSave::SetMasterVolume(float Value)
{
    MasterVolume = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this , TEXT("Settings") , 0);
}

void USettingsSave::SetVoicesVolume(float Value)
{
    VoicesVolume = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this , TEXT("Settings") , 0);
}

void USettingsSave::SetSFXVolume(float Value)
{
    SFXVolume = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this , TEXT("Settings") , 0);
}

void USettingsSave::SetMusicVolume(float Value)
{
    MusicVolume = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this , TEXT("Settings") , 0);
}

void USettingsSave::SetGlobalQuality(int32 Value)
{
    GlobalQuality = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetResolutionScale(float Value)
{
    ResolutionScale = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetFramerate(int32 Value)
{
    Framerate = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetIsVSync(bool Value)
{
    bIsVSync = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetIsMotionBlur(bool Value)
{
    bIsMotionBlur = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetDisplay(TEnumAsByte<EWindowMode::Type> Value)
{
    Display = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetScreenResolution(FIntPoint const& Value)
{
    ScreenResolution = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetAntiAliasing(int32 Value)
{
    AntiAliasing = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}

void USettingsSave::SetBrightness(float Value)
{
    Brightness = Value;
    OnSettingsChanged.Broadcast();
    UGameplayStatics::SaveGameToSlot(this, TEXT("Settings"), 0);
}
