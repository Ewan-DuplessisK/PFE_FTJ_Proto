// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SettingsMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USettingsMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	class USwitcherTabSettings* GetSwitcherTabSettings() const;
	
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SwitchCameraDefault();
	
protected:
	UPROPERTY(meta = (BindWidget))
	class USwitcherTabSettings* SwitcherTabSettings;
	
	UFUNCTION(BlueprintCallable)
	void Return();
};
