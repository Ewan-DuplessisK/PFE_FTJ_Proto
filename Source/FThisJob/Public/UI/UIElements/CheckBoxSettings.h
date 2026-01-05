// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIElementButton.h"
#include "CheckBoxSettings.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UCheckBoxSettings : public UUIElementButton
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	class UCheckBox* GetCheckBox() const;
	
	virtual void NativeOnHovered() override;

	virtual void NativeOnUnhovered() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CheckBox;

	// Text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCommonTextBlock* CommonTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|CheckBox|Name")
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|CheckBox|Text")
	TSubclassOf<class UCommonTextStyle> NormalTextStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|CheckBox|Text")
	TSubclassOf<UCommonTextStyle> HoveredTextStyle;
	
};
