#pragma once

//

#include"CoreMinimal.h"
#include"UI/BaseHUD.h"
#include"GameHUD.generated.h"

//

class UPauseMenuWidget;
class UCommonActivatableWidget;
//

#define TOP_LEVEL 100000

//

UCLASS() class FTHISJOB_API AGameHUD : public ABaseHUD
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY(EditAnywhere , Category = "Widget|Menus") TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass;
    UPROPERTY(EditAnywhere , Category = "Widget|Menus") TSubclassOf<UCommonActivatableWidget> EndScreenClass;

    UPROPERTY(BlueprintReadWrite) TObjectPtr<UPauseMenuWidget> PauseMenuWidgetInstance{nullptr};
    UPROPERTY(EditAnywhere) TObjectPtr<UCommonActivatableWidget> EndScreen{nullptr};

    public:
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable) void RetryPanelToPause();
    
    private:

    protected:

    virtual void BeginPlay() override;

    virtual UBaseMenuWidget * GetPreviousWidget() override;
    virtual USettingsMenuWidget * GetSettingsMenuWidget() const override;
    UFUNCTION(BlueprintCallable) TSubclassOf<UCommonActivatableWidget> GetEndScreenClass();
    

    public:

    UFUNCTION(BlueprintNativeEvent,BlueprintCallable) void PauseGame();

    UFUNCTION(BlueprintImplementableEvent) void OnPauseGameSound();

    UFUNCTION(BlueprintNativeEvent,BlueprintCallable) void ResumeGame();

    UFUNCTION(BlueprintImplementableEvent) void OnResumeGameSound();
};