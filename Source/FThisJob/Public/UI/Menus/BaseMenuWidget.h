// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FTHISJOB_API UBaseMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	virtual class UMainMenuButton* GetFocusedButton() const;

	virtual void NativeConstruct() override;

	virtual class UVerticalBox* GetMenuVerticalBox() const;

protected:

	// Buttons Functions
	UFUNCTION()
	virtual void OnChangeLevelClicked();

	UFUNCTION()
	virtual void OnSettingsClicked() ;

	UFUNCTION()
	virtual void OnQuitClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void Quit();

	UFUNCTION(BlueprintCallable)
	virtual void UnQuit();

	UFUNCTION(BlueprintCallable)
	void OpenSettings();

	UFUNCTION(BlueprintCallable)
	void OpenQuitPanel();

	
	// Widgets Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMainMenuButton* ChangeLevelButton;

	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* SettingsButton;
	
	UPROPERTY(meta = (BindWidget))
	UMainMenuButton* QuitButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMainMenuButton* YesQuitButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMainMenuButton* NoQuitButton;


	// Variables for GD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Menus", meta = (AllowedClasses="World"))
	TSoftObjectPtr<UWorld> NewLevel;

	UPROPERTY(BlueprintReadWrite ,meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;



};
