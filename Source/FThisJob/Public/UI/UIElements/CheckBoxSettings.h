// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CheckBoxSettings.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UCheckBoxSettings : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CheckBox;

	// Text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class URichTextBlock* RichTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CheckBox|Name")
	FText Text;
	
};
