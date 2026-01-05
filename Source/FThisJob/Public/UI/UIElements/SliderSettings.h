// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UIElementButton.h"
#include "SliderSettings.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USliderSettings : public UUIElementButton
{
	GENERATED_BODY()
	
public:
	class USlider* GetSlider() const;

	class UCommonTextBlock* GetValueCommonTextBlock() const;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnHovered() override;

	virtual void NativeOnUnhovered() override;

	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual FReply
	NativeOnAnalogValueChanged(const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent) override;


	// Slider
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class USlider* Slider;

	UPROPERTY()
	class USlider* CurrentSlider;

	bool bEnabled{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|Slider|Values")
	float SliderMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|Slider|Values")
	float SliderMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|Slider|Values")
	float SliderStepSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|Slider|Values")
	float SliderTempDefaultValue;

	//Text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCommonTextBlock* CommonTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|Slider|Text")
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|Slider|Text")
	TSubclassOf<UCommonTextStyle> NormalTextStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UIElement|Slider|Text")
	TSubclassOf<UCommonTextStyle> HoveredTextStyle;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCommonTextBlock* ValueCommonTextBlock;

	UPROPERTY()
	bool bIsHolding = false;

	UPROPERTY()
	float HoldTimer = 0.f;

	UPROPERTY()
	float HoldRepeatDelay = 0.2f;

	UPROPERTY()
	float HoldRepeatRate = 0.05f;

	UPROPERTY()
	int AxisDirection = 0;

	UPROPERTY()
	float RepeatAccumulator = 0.f;

	UPROPERTY()
	class ABaseHUD* HUD;

private:
	UPROPERTY()
	float LastCall = 0;

public:
	UFUNCTION()
	void SetNumberSlider(float Value) const;

	UFUNCTION()
	void Increment(float StepAmount);
};
