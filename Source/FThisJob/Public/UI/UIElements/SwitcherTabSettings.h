// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SwitcherTabSettings.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API USwitcherTabSettings : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	class UCommonAnimatedSwitcher* GetAnimatedSwitcher() const;

	class UHorizontalBox* GetTabHeaderBox() const;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION()
	void SetIndex(int Index, float WaitingTime) const;

	UFUNCTION()
	void SetFocusOnElement(float WaitingTime) const;

protected:
	UPROPERTY(meta = (BindWidget))
	class USettingsTabBase* GameplayTab;
	UPROPERTY(meta = (BindWidget))
	class USettingsTabBase* AudioTab;
	UPROPERTY(meta = (BindWidget))
	class USettingsTabBase* GraphicsTab;
	//UPROPERTY(meta = (BindWidget))
	//class USettingsTabBase* AccessibilityTab;
	UPROPERTY(meta = (BindWidget))
	class USettingsTabBase* ControlTab;

	//Tab Header
	UPROPERTY(meta = (BindWidget))
	class UWidgetTabHeader* GameplayTabHeader;
	UPROPERTY(meta = (BindWidget))
	class UWidgetTabHeader* AudioTabHeader;
	UPROPERTY(meta = (BindWidget))
	class UWidgetTabHeader* GraphicsTabHeader;
	//UPROPERTY(meta = (BindWidget))
	//class UWidgetTabHeader* AccessibilityTabHeader;
	UPROPERTY(meta = (BindWidget))
	class UWidgetTabHeader* ControlTabHeader;
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* TabHeaderBox;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCommonActivatableWidgetSwitcher* AnimatedSwitcher;

	UFUNCTION()
	void ToRightTab() const;
	UFUNCTION()
	void ToLeftTab() const;

public:
	UFUNCTION()
	USettingsTabBase* GetGameplayTab() const;
	UFUNCTION()
	USettingsTabBase* GetAudioTab() const;
	UFUNCTION()
	USettingsTabBase* GetGraphicsTab() const;
	//UFUNCTION()
	//USettingsTabBase* GetAccessibilityTab() const;
	UFUNCTION()
	USettingsTabBase* GetControlTab() const;

	UFUNCTION()
	class UWidgetTabHeader* GetGameplayTabHeader() const;
	UFUNCTION()
	UWidgetTabHeader* GetAudioTabHeader() const;
	UFUNCTION()
	UWidgetTabHeader* GetGraphicsTabHeader() const;
	//UFUNCTION()
	//UWidgetTabHeader* GetAccessibilityTabHeader() const;
	UFUNCTION()
	UWidgetTabHeader* GetControlTabHeader() const;
};
