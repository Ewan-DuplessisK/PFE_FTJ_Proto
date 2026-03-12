// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"

#include "GameFramework/GameUserSettings.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SettingsSave.h"

class USettingsSave* UBaseGameInstance::GetSettingsSave() const
{
	return SettingsSave;
}

void UBaseGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(
		this, &UBaseGameInstance::OnMapLoaded);
	
	UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	check(Settings);
	Settings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	Settings->ApplySettings(false);
	
	USaveGame* Save = UGameplayStatics::LoadGameFromSlot(TEXT("Settings"), 0);
	if (!Save)
	{
		Save = UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass());
		check(Save);
		SettingsSave = Cast<USettingsSave>(Save);
		check(SettingsSave);
		SettingsSave->InitializeFromDefaults(SettingsDataAsset);
	}
	check(Save)
	SettingsSave = Cast<USettingsSave>(Save);

	SettingsSave->OnSettingsChanged.AddDynamic(this, &UBaseGameInstance::MapSettingsData);
	MapSettingsData();
}

void UBaseGameInstance::OnMapLoaded(UWorld* World)
{
	if (GEngine && GEngine->GameViewport)
	{
		FSlateApplication::Get().SetAllUserFocusToGameViewport();
	}
}
