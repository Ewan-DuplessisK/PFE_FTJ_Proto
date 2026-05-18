#pragma once

//

#include"CoreMinimal.h"
#include"UI/Menus/BaseMenuWidget.h"
#include"PauseMenuWidget.generated.h"

//

UCLASS() class FTHISJOB_API UPauseMenuWidget : public UBaseMenuWidget
{
    GENERATED_BODY()

    private:

    protected:

    //Widgets Buttons
    UPROPERTY(BlueprintReadOnly,Meta = (BindWidget)) UMainMenuButton * ResumeButton;
    
    UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) UVerticalBox * MenuVerticalBox;

    public:
    
    private:

    virtual void NativeConstruct() override;
    virtual FReply NativeOnKeyDown(FGeometry const& InGeometry , FKeyEvent const& InKeyEvent) override;
    virtual UWidget * NativeGetDesiredFocusTarget() const override;
    virtual void NativeOnActivated() override;

    virtual UMainMenuButton * GetFocusedButton() const override;
    virtual UVerticalBox * GetMenuVerticalBox() const override;
    virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

    //Buttons Functions
    UFUNCTION() void OnResumeClicked() const;
    virtual void OnSettingsClicked() override;
    virtual void OnChangeLevelClicked() override;
    virtual void OnQuitClicked() override;

    virtual void UnQuit() override;

    protected:
    UFUNCTION(BlueprintImplementableEvent)
    void OnMainMenuImplementation();
    UFUNCTION(BlueprintImplementableEvent)
    void OnQuitImplementation();

    public:
};