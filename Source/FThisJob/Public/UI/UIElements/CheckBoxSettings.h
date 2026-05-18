#pragma once

//

#include"CoreMinimal.h"
#include"CommonUserWidget.h"
#include"CheckBoxSettings.generated.h"

//

class UCheckBox;
class UCommonTextBlock;
class UCommonTextStyle;

//

UCLASS() class FTHISJOB_API UCheckBoxSettings : public UCommonUserWidget
{
    GENERATED_BODY()

    private:

    protected:

    public:

    //Text
    UPROPERTY(BlueprintReadWrite , Meta = (BindWidget)) UCheckBox * CheckBox;
    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UCommonTextBlock * CommonTextBlock;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UIElement|CheckBox|Name") FText Text;

    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UIElement|CheckBox|Text") TSubclassOf<UCommonTextStyle> NormalTextStyle;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "UIElement|CheckBox|Text") TSubclassOf<UCommonTextStyle> HoveredTextStyle;
    
    private:

    protected:

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeOnMouseEnter(FGeometry const& InGeometry , FPointerEvent const& InMouseEvent) override;
    virtual void NativeOnMouseLeave(FPointerEvent const& InMouseEvent) override;
    
    public:

    UFUNCTION(BlueprintCallable)
    UCheckBox * GetCheckBox() const;

    UFUNCTION(BlueprintImplementableEvent)
    void OnHoveredSound();
};