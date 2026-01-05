// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonTextBlockDropdown.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UCommonTextBlockDropdown : public UCommonUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	class UCommonTextBlock* GetCommonTextBlock() const;

protected:
	UPROPERTY(meta=(BindWidget))
	class UCommonTextBlock* CommonTextBlock;
};
