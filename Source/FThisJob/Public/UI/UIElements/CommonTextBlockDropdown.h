#pragma once

//

#include"CoreMinimal.h"
#include"CommonUserWidget.h"
#include"CommonTextBlockDropdown.generated.h"

//

UCLASS() class FTHISJOB_API UCommonTextBlockDropdown : public UCommonUserWidget
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY(Meta = (BindWidget)) UCommonTextBlock * CommonTextBlock;

    public:

    private:

    virtual void NativeConstruct() override;

    protected:

    public:

    UFUNCTION() UCommonTextBlock * GetCommonTextBlock() const;
};