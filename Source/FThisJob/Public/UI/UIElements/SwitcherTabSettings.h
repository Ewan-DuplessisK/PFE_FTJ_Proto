// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SwitcherTabSettings.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USwitcherTabSettings : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	class UCommonAnimatedSwitcher* GetAnimatedSwitcher() const;

protected:
	UPROPERTY(meta = (BindWidget))
	class UCommonAnimatedSwitcher* AnimatedSwitcher;
};
