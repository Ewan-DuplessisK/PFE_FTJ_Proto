#pragma once

#include"CoreMinimal.h"
#include"CommonUserWidget.h"
#include"SliderSettings.generated.h"

//

class ABaseHUD;
class USlider;
class UCommonTextBlock;
class UCommonTextStyle;

//

UCLASS() class FTHISJOB_API USliderSettings : public UCommonUserWidget
{
    GENERATED_BODY()

    private:

    UPROPERTY() float LastCall;

    protected:

    //Slider
    UPROPERTY() ABaseHUD * HUD;
    UPROPERTY(BlueprintReadWrite , Meta = (BindWidget)) USlider * Slider;
    UPROPERTY() USlider * CurrentSlider;
    bool bEnabled{true};

    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UIElement|Slider|Values") float SliderMin;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UIElement|Slider|Values") float SliderMax;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category="UIElement|Slider|Values") float SliderStepSize;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UIElement|Slider|Values") float SliderTempDefaultValue;

    //Text
    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UCommonTextBlock * CommonTextBlock;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UIElement|Slider|Text") FText Text;
    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UCommonTextBlock * ValueCommonTextBlock;

    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UIElement|Slider|Text") TSubclassOf<UCommonTextStyle> NormalTextStyle;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UIElement|Slider|Text") TSubclassOf<UCommonTextStyle> HoveredTextStyle;

    UPROPERTY() bool bIsHolding;
    UPROPERTY() float HoldTimer;
    UPROPERTY() float HoldRepeatDelay{0.2f};
    UPROPERTY() float HoldRepeatRate{0.05};
    UPROPERTY() int AxisDirection;
    UPROPERTY() float RepeatAccumulator;

    public:

    private:
    
    protected:

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry , const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

    UFUNCTION() void OnSliderValueChanged(float Value);
    UFUNCTION() void OnSliderMouseCaptureBegin();
    UFUNCTION() void OnSliderMouseCaptureEnd();

    public:
    UFUNCTION(BlueprintImplementableEvent) void OnHoveredSound();
    
    USlider * GetSlider() const;
    UCommonTextBlock * GetValueCommonTextBlock() const;

    UFUNCTION() void SetNumberSlider(float Value) const;
    UFUNCTION() void Increment(float StepAmount);
};