#pragma once

//

#include"CoreMinimal.h"
#include"CommonActivatableWidget.h"
#include"QuitPanelWidget.generated.h"

//

UCLASS() class FTHISJOB_API UQuitPanelWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()

    private:

    protected:

    public:

    private:

    FReply NativeOnKeyDown(FGeometry const& InGeometry , FKeyEvent const& InKeyEvent) override;

    protected:

    UFUNCTION(BlueprintImplementableEvent , BlueprintCallable) void OnQuitAborted();

    public:
};