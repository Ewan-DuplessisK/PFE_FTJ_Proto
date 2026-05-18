//Header

#include"UI/Menus/SettingsTabs/SettingsAudioWidget.h"

#include"UI/SettingsSave.h"
#include"UI/UIElements/SliderSettings.h"

#include"BaseGameInstance.h"
#include"Components/Slider.h"

//Private

//Protected

void USettingsAudioWidget::OnMasterVolumeSliderValueChanged(float Value)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetMasterVolume(Value);
}

void USettingsAudioWidget::OnVoicesVolumeSliderValueChanged(float Value)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetVoicesVolume(Value);
}

void USettingsAudioWidget::OnSFXVolumeSliderValueChanged(float Value)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetSFXVolume(Value);
}

void USettingsAudioWidget::OnMusicVolumeSliderValueChanged(float Value)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetMusicVolume(Value);
}

//Public

void USettingsAudioWidget::NativeConstruct()
{
    Super::NativeConstruct();
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    check(MasterVolumeSlider);
    MasterVolumeSlider->SetNumberSlider(SettingsSave->GetMasterVolume());
    MasterVolumeSlider->GetSlider()->OnValueChanged.AddUniqueDynamic(this , &USettingsAudioWidget::OnMasterVolumeSliderValueChanged);
    
    check(VoicesVolumeSlider);
    VoicesVolumeSlider->SetNumberSlider(SettingsSave->GetVoicesVolume());
    VoicesVolumeSlider->GetSlider()->OnValueChanged.AddUniqueDynamic(this , &USettingsAudioWidget::OnVoicesVolumeSliderValueChanged);
    
    check(SFXVolumeSlider);
    SFXVolumeSlider->SetNumberSlider(SettingsSave->GetSFXVolume());
    SFXVolumeSlider->GetSlider()->OnValueChanged.AddUniqueDynamic(this , &USettingsAudioWidget::OnSFXVolumeSliderValueChanged);
    
    check(MusicVolumeSlider);
    MusicVolumeSlider->SetNumberSlider(SettingsSave->GetMusicVolume());
    MusicVolumeSlider->GetSlider()->OnValueChanged.AddUniqueDynamic(this , &USettingsAudioWidget::OnMusicVolumeSliderValueChanged);
}

void USettingsAudioWidget::SetupSettingsValues(class USettingsSave* SettingSave)
{
    Super::SetupSettingsValues(SettingSave);
    MasterVolumeSlider->GetSlider()->SetValue(SettingSave->GetMasterVolume());
    VoicesVolumeSlider->GetSlider()->SetValue(SettingSave->GetVoicesVolume());
    SFXVolumeSlider->GetSlider()->SetValue(SettingSave->GetSFXVolume());
    MusicVolumeSlider->GetSlider()->SetValue(SettingSave->GetMusicVolume());
}