#pragma once

//

#include"CoreMinimal.h"
#include"GameFramework/HUD.h"
#include"BaseHUD.generated.h"

//

class UBaseMenuWidget;
class USettingsMenuWidget;
class UGameLayoutWidget;

//

UCLASS() class FTHISJOB_API ABaseHUD : public AHUD
{
    GENERATED_BODY()

    private:
    
    protected:

    UPROPERTY(BlueprintReadWrite) UBaseMenuWidget * PreviousWidgetInstance{nullptr};
    UPROPERTY(BlueprintReadWrite) USettingsMenuWidget * SettingsMenuWidgetInstance{nullptr};
    UPROPERTY(BlueprintReadWrite) UCommonActivatableWidget * QuitPanelInstance{nullptr};
    
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Widget|Menus") TSubclassOf<UBaseMenuWidget> PreviousWidgetClass;
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Widget|Menus") TSubclassOf<USettingsMenuWidget> SettingsMenuWidgetClass;
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Widget|Menus") TSubclassOf<UCommonActivatableWidget> QuitPanelClass;

    UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Widget|Layout") TSubclassOf<UGameLayoutWidget> GameLayoutWidgetClass;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Widget|Menus") TObjectPtr<UGameLayoutWidget> GameLayoutWidget{nullptr};

    public:

    private:
    
    protected:

    virtual void BeginPlay() override;
    
    public:

    UFUNCTION() virtual UBaseMenuWidget * GetPreviousWidget();
    UFUNCTION() virtual USettingsMenuWidget * GetSettingsMenuWidget() const;
    UFUNCTION(BlueprintCallable) UCommonActivatableWidgetStack * GetWidgetStack() const;

    UFUNCTION(BlueprintCallable) UCommonActivatableWidget * PushWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass);
    UFUNCTION(BlueprintCallable) void PopWidget(UCommonActivatableWidget * Widget);

    UFUNCTION(BlueprintCallable) void OpenSettings();
    UFUNCTION(BlueprintCallable) void OpenQuitPanel();

    UFUNCTION(BlueprintCallable) void CloseSettings();
    UFUNCTION(BlueprintCallable) void CloseQuitPanel();
};