//Header

#include"UI/Menus/SettingsTabs/SettingsGameplayWidget.h"

#include"UI/SettingsSave.h"
#include"UI/UIElements/SliderSettings.h"
#include"UI/UIElements/CheckBoxSettings.h"

#include"BaseGameInstance.h"
#include "CommonAnimatedSwitcher.h"
#include"Components/Slider.h"
#include"Components/CheckBox.h"
#include "UI/UIElements/DropdownSettings.h"

//Private

//Protected

void USettingsGameplayWidget::OnHorizontalSensitivitySliderValueChanged(float Value)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetHorizontalSensitivity(Value);
}

void USettingsGameplayWidget::OnVerticalSensitivitySliderValueChanged(float Value)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetVerticalSensitivity(Value);
}

void USettingsGameplayWidget::OnHorizontalAxisDropdownChanged(UWidget* Widget, int32 Index)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetHorizontalAxis(Index);
}

void USettingsGameplayWidget::OnVerticalAxisDropdownChanged(UWidget* Widget, int32 Index)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetVerticalAxis(Index);
}

void USettingsGameplayWidget::OnVibrationChanged(bool bValue)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetVibration(bValue);
}

void USettingsGameplayWidget::OnCrosshairChanged(bool bValue)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetCrosshairVisibility(bValue);
}

void USettingsGameplayWidget::OnCameraShakeChanged(bool bValue)
{
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    SettingsSave->SetCameraShake(bValue);
}

//Public

void USettingsGameplayWidget::NativeConstruct()
{
    Super::NativeConstruct();
    auto GI{Cast<UBaseGameInstance>(GetWorld()->GetGameInstance())};
    check(GI);
    
    auto SettingsSave{GI->GetSettingsSave()};
    check(SettingsSave);
    
    check(HorizontalSensitivitySlider);
    check(VerticalSensitivitySlider);
    check(VibrationCheckBox);
    check(CameraShakeCheckBox);
    check(CrosshairCheckBox);
    
    HorizontalSensitivitySlider->SetNumberSlider(SettingsSave->GetHorizontalSensitivity());
    VerticalSensitivitySlider->SetNumberSlider(SettingsSave->GetVerticalSensitivity());
    InvertHorizontalDropdown->GetSwitcher()->SetActiveWidgetIndex(SettingsSave->GetHorizontalAxis());
    InvertVerticalDropdown->GetSwitcher()->SetActiveWidgetIndex(SettingsSave->GetVerticalAxis());
    VibrationCheckBox->GetCheckBox()->SetIsChecked(SettingsSave->GetVibration());
    CameraShakeCheckBox->GetCheckBox()->SetIsChecked(SettingsSave->GetCameraShake());
    CrosshairCheckBox->GetCheckBox()->SetIsChecked(SettingsSave->GetCrosshairVisibility());
    
    HorizontalSensitivitySlider->GetSlider()->OnValueChanged.AddUniqueDynamic(this , &USettingsGameplayWidget::OnHorizontalSensitivitySliderValueChanged);
    VerticalSensitivitySlider->GetSlider()->OnValueChanged.AddUniqueDynamic(this , &USettingsGameplayWidget::OnVerticalSensitivitySliderValueChanged);
    InvertHorizontalDropdown->GetSwitcher()->OnActiveWidgetIndexChanged.AddUObject(this, &USettingsGameplayWidget::OnHorizontalAxisDropdownChanged);
    InvertVerticalDropdown->GetSwitcher()->OnActiveWidgetIndexChanged.AddUObject(this, &USettingsGameplayWidget::OnVerticalAxisDropdownChanged);
    VibrationCheckBox->GetCheckBox()->OnCheckStateChanged.AddUniqueDynamic(this , &USettingsGameplayWidget::OnVibrationChanged);
    CrosshairCheckBox->GetCheckBox()->OnCheckStateChanged.AddUniqueDynamic(this, &USettingsGameplayWidget::OnCrosshairChanged);
    CameraShakeCheckBox->GetCheckBox()->OnCheckStateChanged.AddUniqueDynamic(this , &USettingsGameplayWidget::OnCameraShakeChanged);
}

void USettingsGameplayWidget::SetupSettingsValues(USettingsSave * SettingSave)
{
    Super::SetupSettingsValues(SettingSave);
    HorizontalSensitivitySlider->GetSlider()->SetValue(SettingSave->GetHorizontalSensitivity());
    VerticalSensitivitySlider->GetSlider()->SetValue(SettingSave->GetVerticalSensitivity());
    VibrationCheckBox->GetCheckBox()->SetIsChecked(SettingSave->GetVibration());
    CameraShakeCheckBox->GetCheckBox()->SetIsChecked(SettingSave->GetCameraShake());
    CrosshairCheckBox->GetCheckBox()->SetIsChecked(SettingSave->GetCrosshairVisibility());
}