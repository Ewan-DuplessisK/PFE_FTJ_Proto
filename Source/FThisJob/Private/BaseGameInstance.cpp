//Header

#include"BaseGameInstance.h"

#include"UI/SettingsSave.h"

#include"GameFramework/GameUserSettings.h"
#include"GameFramework/SaveGame.h"
#include"Kismet/GameplayStatics.h"

//Private

void UBaseGameInstance::Init()
{
    Super::Init();
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this , &UBaseGameInstance::OnMapLoaded);
    auto Save{UGameplayStatics::LoadGameFromSlot(TEXT("Settings") , 0)};
    if(!Save)
    {
        Save = UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass());
        check(Save);
        SettingsSave = Cast<USettingsSave>(Save);
        check(SettingsSave);
        SettingsSave->InitializeFromDefaults(SettingsDataAsset);
    }
    check(Save)
    SettingsSave = Cast<USettingsSave>(Save);
    ApplySettings();
    /*
    SettingsSave->OnSettingsChanged.AddDynamic(this, &UBaseGameInstance::MapSettingsData);
    MapSettingsData();
    */
}

void UBaseGameInstance::OnMapLoaded(UWorld * World)
{
    if(GEngine && GEngine->GameViewport)
    {
        FSlateApplication::Get().SetAllUserFocusToGameViewport();
    }
}

void UBaseGameInstance::ApplySettings()
{
    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer
    (
        Timer , [&]
        {
            UGameUserSettings* Settings = GEngine->GetGameUserSettings();
            check(Settings);
            Settings->SetOverallScalabilityLevel(SettingsSave->GetGlobalQuality());
            Settings->SetFullscreenMode(SettingsSave->GetDisplay());
            Settings->SetScreenResolution(SettingsSave->GetScreenResolution());
            Settings->SetResolutionScaleValueEx(SettingsSave->GetResolutionScale());
            Settings->SetFrameRateLimit(SettingsSave->GetFramerate());
            UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld() , FString::Printf(TEXT("r.AntiAliasingMethod %d") , SettingsSave->GetAntiAliasing()));
            UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld() , FString::Printf(TEXT("r.Gamma %.2f") , SettingsSave->GetBrightness()));
            Settings->SetVSyncEnabled(SettingsSave->GetIsVSync());
            UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld() , SettingsSave->GetIsMotionBlur() ? "r.MotionBlurQuality 4" : "r.MotionBlurQuality 0");
            Settings->ApplySettings(false);
        }
        , 0.5 , false , -1.0
    );
}

//Protected

//Public

USettingsSave * UBaseGameInstance::GetSettingsSave() const
{
    return(SettingsSave);
}