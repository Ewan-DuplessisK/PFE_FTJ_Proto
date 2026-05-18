#pragma once

#include"CoreMinimal.h"
#include"CommonUserWidget.h"
#include"SwitcherTabSettings.generated.h"

//

class UHorizontalBox;
class UCommonActivatableWidgetSwitcher;
class UImage;

//

UCLASS() class FTHISJOB_API USwitcherTabSettings : public UCommonUserWidget
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY(Meta = (BindWidget)) USettingsTabBase * GameplayTab;
    UPROPERTY(Meta = (BindWidget)) USettingsTabBase * AudioTab;
    UPROPERTY(Meta = (BindWidget)) USettingsTabBase * GraphicsTab;
    //UPROPERTY(Meta = (BindWidget)) USettingsTabBase * AccessibilityTab;
    UPROPERTY(Meta = (BindWidget)) USettingsTabBase * ControlTab;

    //Tab Header
    UPROPERTY(Meta = (BindWidget)) UWidgetTabHeader * GameplayTabHeader;
    UPROPERTY(Meta = (BindWidget)) UWidgetTabHeader * AudioTabHeader;
    UPROPERTY(Meta = (BindWidget)) UWidgetTabHeader * GraphicsTabHeader;
    //UPROPERTY(Meta = (BindWidget)) UWidgetTabHeader * AccessibilityTabHeader;
    UPROPERTY(Meta = (BindWidget)) UWidgetTabHeader * ControlTabHeader;

    UPROPERTY(Meta = (BindWidget)) UHorizontalBox* TabHeaderBox;
    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UCommonActivatableWidgetSwitcher * AnimatedSwitcher;

    UPROPERTY(Meta = (BindWidget)) UImage * LeftSwitchImage;
    UPROPERTY(Meta = (BindWidget)) UImage * RightSwitchImage;

    UPROPERTY(EditDefaultsOnly) UTexture * NormalLeftSwitchTexture;
    UPROPERTY(EditDefaultsOnly) UTexture * PressedLeftSwitchTexture;
    UPROPERTY(EditDefaultsOnly) UTexture * NormalRightSwitchTexture;
    UPROPERTY(EditDefaultsOnly) UTexture * PressedRightSwitchTexture;

    public:
    
    private:

    protected:

    UFUNCTION() void ToLeftTab() const;
    UFUNCTION() void ToRightTab() const;
    
    public:

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& InGeometry , float InDeltaTime) override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry , const FKeyEvent& InKeyEvent) override;
    virtual FReply NativeOnKeyUp(const FGeometry& InGeometry , const FKeyEvent& InKeyEvent) override;

    class UHorizontalBox * GetTabHeaderBox() const;
    class UCommonAnimatedSwitcher * GetAnimatedSwitcher() const;

    void HandleTransitioningChanged(bool bIsTransitioning);
    UFUNCTION(BlueprintCallable) void SetIndex(int Index) const;
    UFUNCTION() void SetFocusOnElement() const;

    UFUNCTION() USettingsTabBase * GetGameplayTab() const;
    UFUNCTION() USettingsTabBase * GetAudioTab() const;
    UFUNCTION() USettingsTabBase * GetGraphicsTab() const;
    //UFUNCTION() USettingsTabBase * GetAccessibilityTab() const;
    UFUNCTION() USettingsTabBase * GetControlTab() const;

    UFUNCTION() UWidgetTabHeader * GetGameplayTabHeader() const;
    UFUNCTION() UWidgetTabHeader * GetAudioTabHeader() const;
    UFUNCTION() UWidgetTabHeader * GetGraphicsTabHeader() const;
    //UFUNCTION() UWidgetTabHeader * GetAccessibilityTabHeader() const;
    UFUNCTION() UWidgetTabHeader * GetControlTabHeader() const;
};