// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "UIElementButton.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UUIElementButton : public UCommonButtonBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnHovered() override;

	UPROPERTY()
	bool bIsEditing = false;

	UPROPERTY(EditAnywhere, Category="UIElement|Navigation")
	UUIElementButton* UpUIElement;

	UPROPERTY(EditAnywhere, Category="UIElement|Navigation")
	UUIElementButton* DownUIElement;
};
