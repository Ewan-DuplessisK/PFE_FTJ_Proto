// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "RetryPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API URetryPanelWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

	virtual FReply NativeOnKeyDown(FGeometry const& InGeometry , FKeyEvent const& InKeyEvent) override;

};
