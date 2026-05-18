#pragma once

//

#include"CoreMinimal.h"
#include"CommonUserWidget.h"
#include"GameLayoutWidget.generated.h"

//

class UCommonActivatableWidgetStack;

//

UCLASS() class FTHISJOB_API UGameLayoutWidget : public UCommonUserWidget
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY(Meta = (BindWidget)) TObjectPtr<UCommonActivatableWidgetStack> WidgetStack;

    public:

    private:

    protected:
    
    public:

    UCommonActivatableWidgetStack * GetStack() const;
};