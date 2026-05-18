#pragma once

//

#include"CoreMinimal.h"
#include"CommonActivatableWidget.h"
#include"BaseMenuWidget.generated.h"

//

class UVerticalBox;
class UMainMenuButton;

//

UCLASS() class FTHISJOB_API UBaseMenuWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()

    private:

    protected:

    //Widgets Button
    UPROPERTY(BlueprintReadWrite , Meta = (BindWidget)) UMainMenuButton * ChangeLevelButton;
    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) UMainMenuButton * SettingsButton;
    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) UMainMenuButton * QuitButton;

    //Variables for GD
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Menus" , Meta = (AllowedClasses = "World")) TSoftObjectPtr<UWorld> NewLevel;
    
    public:

    private:

    protected:

    //Buttons Functions
    UFUNCTION() virtual void OnChangeLevelClicked();
    UFUNCTION() virtual void OnSettingsClicked();
    UFUNCTION() virtual void OnQuitClicked();

    UFUNCTION(BlueprintImplementableEvent) void Quit();
    UFUNCTION(BlueprintCallable) virtual void UnQuit();

    UFUNCTION(BlueprintCallable) void OpenSettings();
    UFUNCTION(BlueprintCallable) void OpenQuitPanel();
    
    public:

    virtual void NativeConstruct() override;

    virtual UMainMenuButton * GetFocusedButton() const;
    virtual UVerticalBox * GetMenuVerticalBox() const;
};