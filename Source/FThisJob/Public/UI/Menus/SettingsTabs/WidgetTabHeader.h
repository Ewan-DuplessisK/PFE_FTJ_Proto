#pragma once

//

#include"CoreMinimal.h"
#include"CommonUserWidget.h"
#include"WidgetTabHeader.generated.h"

//

class UCommonTextBlock;
class UImage;
class UCommonTextStyle;
class USwitcherTabSettings;

//

UCLASS() class FTHISJOB_API UWidgetTabHeader : public UCommonUserWidget
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UCommonTextBlock * CommonTextBlock;
    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UImage * TabImage;
    UPROPERTY(EditAnywhere , Category = "TabHeader") UTexture2D * UnSelectedTabTexture;
    UPROPERTY(EditAnywhere , Category = "TabHeader") UTexture2D * SelectedTabTexture;

    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (BindWidget) , Category = "TabHeader") FText Text;
    UPROPERTY() int Index;

    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "TabHeader|TextStyle") TSubclassOf<UCommonTextStyle> NormalTextStyle;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "TabHeader|TextStyle") TSubclassOf<UCommonTextStyle> HoveredTextStyle;

    UPROPERTY(BlueprintReadOnly) bool isSelected;
    USwitcherTabSettings * Switcher;

    public:

    private:

    protected:
    
    public:

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual FReply NativeOnMouseButtonDown(FGeometry const& InGeometry , FPointerEvent const& InMouseEvent) override;
    virtual void NativeOnMouseEnter(FGeometry const& InGeometry , FPointerEvent const& InMouseEvent) override;
    virtual void NativeOnMouseLeave(FPointerEvent const& InMouseEvent) override;

    //Get/SetIndex()
    void SetIndex(int NewIndex);
    int GetIndex() const;

    void Toggle(bool bToggle);
    void SetIsSelected(bool bIsSelected);
};