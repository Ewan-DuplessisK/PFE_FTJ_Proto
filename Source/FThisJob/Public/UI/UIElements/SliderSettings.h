// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SliderSettings.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USliderSettings : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
protected:
	// Slider
	UPROPERTY(meta = (BindWidget))
	class USlider* Slider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slider|Values")
	float SliderMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slider|Values")
	float SliderMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slider|Values")
	float SliderStepSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slider|Values")
	float SliderTempDefaultValue;

	//Text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class URichTextBlock* RichTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slider|Name")
	FText Text;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class URichTextBlock* ValueRichTextBlock;
};
