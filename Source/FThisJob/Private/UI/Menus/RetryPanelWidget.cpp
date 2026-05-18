// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/RetryPanelWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UI/GameHUD.h"

FReply URetryPanelWidget::NativeOnKeyDown(FGeometry const& InGeometry, FKeyEvent const& InKeyEvent)
{
	auto Reply{Super::NativeOnKeyDown(InGeometry , InKeyEvent)};    
	if(InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right || InKeyEvent.GetKey() == EKeys::Escape)
	{
		auto const PC{UGameplayStatics::GetPlayerController(GetWorld() , 0)};
		auto HUD{Cast<AGameHUD>(PC->GetHUD())};
		if(ensure(HUD))
		{
			HUD->RetryPanelToPause();
		}
		return(FReply::Handled());
	}
	return Reply;
}

