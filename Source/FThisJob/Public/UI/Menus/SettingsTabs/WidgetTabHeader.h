// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "WidgetTabHeader.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UWidgetTabHeader : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	// Get/SetIndex()
	void SetIndex(int NewIndex);

	int GetIndex() const;

	void Toggle(bool bToggle);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCommonTextBlock* CommonTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* TabImage;
	UPROPERTY(EditAnywhere,Category="TabHeader")
	class UTexture2D* UnSelectedTabTexture;
	UPROPERTY(EditAnywhere,Category="TabHeader")
	class UTexture2D* SelectedTabTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget), Category="TabHeader")
	FText Text;
	UPROPERTY()
	int Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TabHeader|TextStyle")
	TSubclassOf<class UCommonTextStyle> NormalTextStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TabHeader|TextStyle")
	TSubclassOf<class UCommonTextStyle> HoveredTextStyle;
};
