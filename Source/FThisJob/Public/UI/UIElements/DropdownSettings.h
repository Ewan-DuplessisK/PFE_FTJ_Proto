// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DropdownSettings.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UDropdownSettings : public UCommonUserWidget
{
	GENERATED_BODY()
		
public:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ComboBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dropdown|Value")
	TArray<FString> DropdownValues;

	// Text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class URichTextBlock* RichTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dropdown|Name")
	FText Text;
};
