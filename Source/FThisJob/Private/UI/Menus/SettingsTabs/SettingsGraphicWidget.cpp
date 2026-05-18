//Header

#include"UI/Menus/SettingsTabs/SettingsGraphicWidget.h"

#include"UI/SettingsSave.h"
#include"BaseGameInstance.h"
#include "CommonAnimatedSwitcher.h"
#include"Components/CheckBox.h"
#include "Components/Slider.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/UIElements/CheckBoxSettings.h"
#include "UI/UIElements/DropdownSettings.h"
#include "UI/UIElements/SliderSettings.h"

//Private

void USettingsGraphicWidget::ApplyWithFocusRestore(UWidget* Widget)
{
    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (Settings)
    {
        Settings->ApplySettings(false);
    }

    if (Widget)
    {
        Widget->SetFocus();
    }
}

void USettingsGraphicWidget::ApplyAndSave()
{
    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (Settings)
    {
        Settings->ApplySettings(false);
        Settings->SaveSettings();
    }
}

//Protected

//Public

void USettingsGraphicWidget::OnGlobalQualityChanged(UWidget* Widget, int32 Index)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    USettingsSave* SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);
    SettingsSave->SetGlobalQuality(GlobalQuality->GetSelectedOption().IntValue);

    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (!Settings) return;
    Settings->SetOverallScalabilityLevel(GlobalQuality->GetSelectedOption().IntValue);
    ApplyWithFocusRestore(GlobalQuality);
}

void USettingsGraphicWidget::OnResolutionScaleChanged(float Value)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    USettingsSave* SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);
    SettingsSave->SetResolutionScale(Value);

    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (!Settings) return;
    Settings->SetResolutionScaleValueEx(ResolutionScale->GetSlider()->GetValue());
    ApplyWithFocusRestore(ResolutionScale);
}

void USettingsGraphicWidget::OnFramerateChanged(UWidget* Widget, int32 Index)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    USettingsSave* SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);
    SettingsSave->SetFramerate(Framerate->GetSelectedOption().IntValue);

    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (!Settings) return;
    Settings->SetFrameRateLimit(Framerate->GetSelectedOption().IntValue);
    ApplyWithFocusRestore(Framerate);
}

void USettingsGraphicWidget::OnVSyncChanged(bool bValue)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    USettingsSave* SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);
    SettingsSave->SetIsVSync(bValue);

    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (!Settings) return;
    Settings->SetVSyncEnabled(bValue);
}

void USettingsGraphicWidget::OnMotionBlurChanged(bool bValue)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    USettingsSave* SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);
    SettingsSave->SetIsMotionBlur(bValue);

    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), bValue ? "r.MotionBlurQuality 4" : "r.MotionBlurQuality 0");
}

void USettingsGraphicWidget::OnDisplayChanged(UWidget* Widget, int32 Index)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    USettingsSave* SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);
    SettingsSave->SetDisplay(Display->GetSelectedOption().WindowModeValue);

    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (!Settings) return;
    Settings->SetFullscreenMode(Display->GetSelectedOption().WindowModeValue);
    ApplyWithFocusRestore(Display);
}

void USettingsGraphicWidget::OnScreenResolutionChanged(UWidget* Widget, int32 Index)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    USettingsSave* SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);
    SettingsSave->SetScreenResolution(ScreenResolution->GetSelectedOption().IntPointValue);

    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (!Settings) return;
    Settings->SetScreenResolution(ScreenResolution->GetSelectedOption().IntPointValue);
    ApplyWithFocusRestore(ScreenResolution);
}

void USettingsGraphicWidget::OnAntiAliasingChanged(UWidget* Widget, int32 Index)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    USettingsSave* SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);
    SettingsSave->SetAntiAliasing(AntiAliasing->GetSelectedOption().IntValue);

    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), FString::Printf(TEXT("r.AntiAliasingMethod %d"), AntiAliasing->GetSelectedOption().IntValue));
}

void USettingsGraphicWidget::OnBrightnessChanged(float Value)
{
    UBaseGameInstance* GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    USettingsSave* SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);
    SettingsSave->SetBrightness(Value);

    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), FString::Printf(TEXT("r.Gamma %.2f"), Value));
}

void USettingsGraphicWidget::NativeConstruct()
{
    Super::NativeConstruct();

    auto GI = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    check(GI);
    auto SettingsSave = GI->GetSettingsSave();
    check(SettingsSave);

    for(int32 Index{0} ; Index < GlobalQuality->GetEntries().Num() ; Index++)
    {
        if(GlobalQuality->GetEntries()[Index].IntValue == SettingsSave->GetGlobalQuality())
        {
           GlobalQuality->GetSwitcher()->SetActiveWidgetIndex(Index);
        }
    }
    ResolutionScale->GetSlider()->SetValue(SettingsSave->GetResolutionScale());
    for(int32 Index{0} ; Index < Framerate->GetEntries().Num() ; Index++)
    {
        if(Framerate->GetEntries()[Index].IntValue == SettingsSave->GetFramerate())
        {
           Framerate->GetSwitcher()->SetActiveWidgetIndex(Index);
        }
    }
    VSync->GetCheckBox()->SetIsChecked(SettingsSave->GetIsVSync());
    MotionBlur->GetCheckBox()->SetIsChecked(SettingsSave->GetIsMotionBlur());
    for(int32 Index{0} ; Index < Display->GetEntries().Num() ; Index++)
    {
        if(Display->GetEntries()[Index].WindowModeValue == SettingsSave->GetDisplay())
        {
           Display->GetSwitcher()->SetActiveWidgetIndex(Index);
        }
    }
    for(int32 Index{0} ; Index < ScreenResolution->GetEntries().Num() ; Index++)
    {
        if(ScreenResolution->GetEntries()[Index].IntPointValue == SettingsSave->GetScreenResolution())
        {
           ScreenResolution->GetSwitcher()->SetActiveWidgetIndex(Index);
        }
    }
    for(int32 Index{0} ; Index < AntiAliasing->GetEntries().Num() ; Index++)
    {
        if(AntiAliasing->GetEntries()[Index].IntValue == SettingsSave->GetAntiAliasing())
        {
           AntiAliasing->GetSwitcher()->SetActiveWidgetIndex(Index);
        }
    }
    Brightness->GetSlider()->SetValue(SettingsSave->GetBrightness());
}

void USettingsGraphicWidget::NativeOnActivated()
{
    Super::NativeOnActivated();

    GlobalQuality->GetSwitcher()->OnActiveWidgetIndexChanged.AddUObject(this, &USettingsGraphicWidget::OnGlobalQualityChanged);
    ResolutionScale->GetSlider()->OnValueChanged.AddUniqueDynamic(this, &USettingsGraphicWidget::OnResolutionScaleChanged);
    Framerate->GetSwitcher()->OnActiveWidgetIndexChanged.AddUObject(this, &USettingsGraphicWidget::OnFramerateChanged);
    VSync->GetCheckBox()->OnCheckStateChanged.AddUniqueDynamic(this, &USettingsGraphicWidget::OnVSyncChanged);
    MotionBlur->GetCheckBox()->OnCheckStateChanged.AddUniqueDynamic(this, &USettingsGraphicWidget::OnMotionBlurChanged);
    Display->GetSwitcher()->OnActiveWidgetIndexChanged.AddUObject(this, &USettingsGraphicWidget::OnDisplayChanged);
    ScreenResolution->GetSwitcher()->OnActiveWidgetIndexChanged.AddUObject(this, &USettingsGraphicWidget::OnScreenResolutionChanged);
    AntiAliasing->GetSwitcher()->OnActiveWidgetIndexChanged.AddUObject(this, &USettingsGraphicWidget::OnAntiAliasingChanged);
    Brightness->GetSlider()->OnValueChanged.AddUniqueDynamic(this, &USettingsGraphicWidget::OnBrightnessChanged);
}

void USettingsGraphicWidget::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();

    ApplyAndSave();

    GlobalQuality->GetSwitcher()->OnActiveWidgetIndexChanged.RemoveAll(this);
    ResolutionScale->GetSlider()->OnValueChanged.RemoveAll(this);
    Framerate->GetSwitcher()->OnActiveWidgetIndexChanged.RemoveAll(this);
    VSync->GetCheckBox()->OnCheckStateChanged.RemoveAll(this);
    MotionBlur->GetCheckBox()->OnCheckStateChanged.RemoveAll(this);
    Display->GetSwitcher()->OnActiveWidgetIndexChanged.RemoveAll(this);
    ScreenResolution->GetSwitcher()->OnActiveWidgetIndexChanged.RemoveAll(this);
    AntiAliasing->GetSwitcher()->OnActiveWidgetIndexChanged.RemoveAll(this);
    Brightness->GetSlider()->OnValueChanged.RemoveAll(this);

}

void USettingsGraphicWidget::SetupSettingsValues(USettingsSave* SettingSave)
{
    Super::SetupSettingsValues(SettingSave);

    /*
    GlobalQuality->GetSwitcher()->SetActiveWidgetIndex(SettingSave->GetGlobalQuality());
    ResolutionScale->GetSlider()->SetValue(SettingSave->GetResolutionScale());
    Framerate->GetSwitcher()->SetActiveWidgetIndex(SettingSave->GetFramerate());
    VSync->GetCheckBox()->SetIsChecked(SettingSave->GetIsVSync());
    MotionBlur->GetCheckBox()->SetIsChecked(SettingSave->GetIsMotionBlur());
    Display->GetSwitcher()->SetActiveWidgetIndex(SettingSave->GetDisplay());
    ScreenResolution->GetSwitcher()->SetActiveWidgetIndex(SettingSave->GetScreenResolution());
    AntiAliasing->GetSwitcher()->SetActiveWidgetIndex(SettingSave->GetAntiAliasing());
    Brightness->GetSlider()->SetValue(SettingSave->GetBrightness());
    */
}