#pragma once

//

#include"CoreMinimal.h"
#include"CommonButtonBase.h"
#include"MainMenuButton.generated.h"

//

class UOverlay;
class UCommonTextBlock;

//

UCLASS() class FTHISJOB_API UMainMenuButton : public UCommonButtonBase
{
    GENERATED_BODY()

    private:
    
    protected:

    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UOverlay * Overlay;
    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UCommonTextBlock * TextBlock;

    UPROPERTY(EditAnywhere , BlueprintReadOnly, Meta = (BindWidget, MultiLine = True)) FText Text;
    UPROPERTY(EditAnywhere , BlueprintReadWrite) FMargin TextPadding;

    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Button|TextStyle") TSubclassOf<UCommonTextStyle> NormalTextStyle;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Button|TextStyle") TSubclassOf<UCommonTextStyle> HoveredTextStyle;
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Button|TextStyle") TSubclassOf<UCommonTextStyle> PressedTextStyle;

    public:

    private:

    protected:
    
    public:

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeOnHovered() override;
    virtual void NativeOnUnhovered() override;
    virtual void NativeOnPressed() override;
};