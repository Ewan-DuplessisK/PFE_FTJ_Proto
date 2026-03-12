// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;

	void OnMapLoaded(UWorld* World);
	
public:
	UPROPERTY(EditDefaultsOnly)
	class USettingsDataAsset* SettingsDataAsset = nullptr;

	UFUNCTION(BlueprintCallable)
	class USettingsSave* GetSettingsSave() const;

	UFUNCTION(BlueprintImplementableEvent)
	void MapSettingsData();

protected:
	UPROPERTY()
	TObjectPtr<class USettingsSave> SettingsSave = nullptr;
};
