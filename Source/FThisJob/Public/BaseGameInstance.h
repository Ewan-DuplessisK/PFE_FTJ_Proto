#pragma once

//

#include"CoreMinimal.h"
#include"Engine/GameInstance.h"
#include"BaseGameInstance.generated.h"

//

class USettingsDataAsset;

//

UCLASS() class FTHISJOB_API UBaseGameInstance : public UGameInstance
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY() TObjectPtr<USettingsSave> SettingsSave;
    
    public:

    UPROPERTY(EditDefaultsOnly) USettingsDataAsset * SettingsDataAsset;

    private:
    
    virtual void Init() override;
    void OnMapLoaded(UWorld * World);
    UFUNCTION(BlueprintCallable) void ApplySettings();

    protected:

    public:

    UFUNCTION(BlueprintCallable) USettingsSave * GetSettingsSave() const;
    UFUNCTION(BlueprintImplementableEvent) void MapSettingsData();
};