// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIElementButton.h"
#include "DropdownSettings.generated.h"

UENUM(BlueprintType)
enum class EDropdownValueType : uint8
{
	None,
	IntPoint,
	WindowMode,
	Integer,
};

USTRUCT(BlueprintType)
struct FDropdownOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(HideInDetailPanel))
	EDropdownValueType ValueType = EDropdownValueType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dropdown Option",
		meta=(EditCondition="ValueType == EDropdownValueType::IntPoint", EditConditionHides))
	FIntPoint IntPointValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dropdown Option",
		meta=(EditCondition="ValueType == EDropdownValueType::WindowMode", EditConditionHides))
	TEnumAsByte<EWindowMode::Type> WindowModeValue = EWindowMode::Type::Fullscreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dropdown Option",
		meta=(EditCondition="ValueType == EDropdownValueType::Integer", EditConditionHides))
	int32 IntValue = 0;

	FDropdownOption()
	{
	}

	static FDropdownOption MakeResolution(FText Name, FIntPoint Res)
	{
		FDropdownOption Opt;
		Opt.DisplayName = Name;
		Opt.ValueType = EDropdownValueType::IntPoint;
		Opt.IntPointValue = Res;
		return Opt;
	}

	static FDropdownOption MakeWindowMode(FText Name, EWindowMode::Type Mode)
	{
		FDropdownOption Opt;
		Opt.DisplayName = Name;
		Opt.ValueType = EDropdownValueType::WindowMode;
		Opt.WindowModeValue = Mode;
		return Opt;
	}

	static FDropdownOption MakeInteger(FText Name, int32 Val)
	{
		FDropdownOption Opt;
		Opt.DisplayName = Name;
		Opt.ValueType = EDropdownValueType::Integer;
		Opt.IntValue = Val;
		return Opt;
	}
};

UCLASS()
class FTHISJOB_API UDropdownSettings : public UUIElementButton
{
	GENERATED_BODY()
		
public:
	virtual void NativeConstruct() override;

	class UCommonAnimatedSwitcher* GetSwitcher() const;

	UFUNCTION()
	FDropdownOption GetSelectedOption() const;

	virtual void NativeOnHovered() override;

	virtual void NativeOnUnhovered() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UCommonAnimatedSwitcher* Switcher;

	// Text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCommonTextBlock* CommonTextBlock;
	UPROPERTY()
	UCommonTextBlock* CommonTextBlockObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|Dropdown|Name")
	FText NameText;
	UPROPERTY(EditAnywhere, Category="UIElement|Dropdown|Name")
	TSubclassOf<UCommonTextStyle> NormalTextStyle;
	UPROPERTY(EditAnywhere, Category="UIElement|Dropdown|Name")
	TSubclassOf<UCommonTextStyle> HoveredTextStyle;
	UPROPERTY(EditAnywhere, Category="UIElement|Dropdown")
	TSubclassOf<class UCommonTextBlockDropdown> CommonTextBlocDropDownClass;

	UPROPERTY(EditAnywhere, Category="UIElement|Dropdown")
	TArray<FDropdownOption> Entries;

	UPROPERTY()
	int32 SwitcherLenght;

	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual FReply
	NativeOnAnalogValueChanged(const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent) override;

	UFUNCTION()
	void CreateTextBlock(FText Text);

	UFUNCTION()
	void ToRightOption();

	UFUNCTION()
	void ToLeftOption();

private:
	UPROPERTY()
	float LastCall = 0;
};
