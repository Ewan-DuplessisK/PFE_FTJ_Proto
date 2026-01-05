// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "EngineUtils.h"
#include "MainMenuButton.generated.h"

UCLASS()
class FTHISJOB_API UMainMenuButton : public UCommonButtonBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeOnHovered() override;

	virtual void NativeOnUnhovered() override;

	virtual void NativeOnPressed() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCommonTextBlock* TextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	FText Text;

	// Animation
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ButtonHoveredAnim;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* ButtonClickedAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button|TextStyle")
	TSubclassOf<UCommonTextStyle> NormalTextStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button|TextStyle")
	TSubclassOf<UCommonTextStyle> HoveredTextStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button|TextStyle")
	TSubclassOf<UCommonTextStyle> PressedTextStyle;
	


};
