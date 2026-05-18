#pragma once

//

#include"CoreMinimal.h"
#include"UIElementButton.h"
#include"DropdownSettings.generated.h"

//

class UCommonAnimatedSwitcher;
class UCommonTextBlock;
class UCommonTextBlockDropdown;
class UMainMenuButton;

//

UENUM(BlueprintType) enum class EDropdownValueType : uint8
{
    None
    ,
    IntPoint
    ,
    WindowMode
    ,
    Integer
    ,
    Bool
};

//

USTRUCT(BlueprintType) struct FDropdownOption
{
    GENERATED_BODY()

    private:

    protected:

    public:

    UPROPERTY(EditAnywhere , BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere , BlueprintReadOnly , Meta = (HideInDetailPanel)) EDropdownValueType ValueType{EDropdownValueType::None};
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Dropdown Option" , Meta = (EditCondition = "ValueType == EDropdownValueType::IntPoint" , EditConditionHides)) FIntPoint IntPointValue{0};
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Dropdown Option" , Meta = (EditCondition = "ValueType == EDropdownValueType::WindowMode" , EditConditionHides))
    TEnumAsByte<EWindowMode::Type> WindowModeValue{EWindowMode::Type::Fullscreen};
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Dropdown Option" , Meta = (EditCondition = "ValueType == EDropdownValueType::Integer" , EditConditionHides)) int32 IntValue{0};
    UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Dropdown Option" , Meta = (EditCondition = "ValueType == EDropdownValueType::Bool" , EditConditionHides)) bool bValue{true};
    
    private:

    protected:

    public:

    FDropdownOption();

    static FDropdownOption MakeResolution(FText Name , FIntPoint Res);

    static FDropdownOption MakeWindowMode(FText Name , EWindowMode::Type Mode);

    static FDropdownOption MakeInteger(FText Name , int32 Val);
    
    static FDropdownOption MakeBool(FText Name , bool bValue);
};

//

UCLASS() class FTHISJOB_API UDropdownSettings : public UUIElementButton
{
    GENERATED_BODY()
        
    private:

    UPROPERTY() float LastCall;
    
    protected:

    //Text
    UPROPERTY(Meta = (BindWidget)) UCommonAnimatedSwitcher * Switcher;
    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UCommonTextBlock * CommonTextBlock;
    UPROPERTY() UCommonTextBlock * CommonTextBlockObject;
    UPROPERTY(EditAnywhere , BlueprintReadWrite, Category = "UIElement|Dropdown|Name") FText NameText;
    UPROPERTY(EditAnywhere , Category = "UIElement|Dropdown|Name") TSubclassOf<UCommonTextStyle> NormalTextStyle;
    UPROPERTY(EditAnywhere , Category = "UIElement|Dropdown|Name") TSubclassOf<UCommonTextStyle> HoveredTextStyle;
    UPROPERTY(EditAnywhere , Category = "UIElement|Dropdown") TSubclassOf<UCommonTextBlockDropdown> CommonTextBlocDropDownClass;
    UPROPERTY(Transient, meta = (BindWidgetAnim)) UWidgetAnimation* ToLeftAnimation;
    UPROPERTY(Transient, meta = (BindWidgetAnim)) UWidgetAnimation* ToRightAnimation;
    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UMainMenuButton * LeftArrowButton;
    UPROPERTY(BlueprintReadOnly , Meta = (BindWidget)) UMainMenuButton * RightArrowButton;
    
    UPROPERTY(EditAnywhere , Category = "UIElement|Dropdown") TArray<FDropdownOption> Entries;
    UPROPERTY() int32 SwitcherLenght;

    public:

    private:

    void OnLeftArrowClicked();
    void OnRightArrowClicked();
    
    protected:

    virtual FReply NativeOnPreviewKeyDown(FGeometry const& InGeometry , FKeyEvent const& InKeyEvent) override;
    virtual FReply NativeOnAnalogValueChanged(FGeometry const& InGeometry , FAnalogInputEvent const& InAnalogEvent) override;

    UFUNCTION() void CreateTextBlock(FText Text);

    UFUNCTION() void ToLeftOption();
    UFUNCTION() void ToRightOption();
    
    public:

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeOnHovered() override;
    virtual void NativeOnUnhovered() override;

    UFUNCTION(BlueprintImplementableEvent) void OnHoveredSound();

    UFUNCTION(BlueprintCallable) FDropdownOption GetSelectedOption() const;
    UFUNCTION(BlueprintCallable) UCommonAnimatedSwitcher * GetSwitcher() const;
    TArray<FDropdownOption> const& GetEntries();
};