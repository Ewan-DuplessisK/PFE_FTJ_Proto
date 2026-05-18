#pragma once

//

#include"CoreMinimal.h"
#include"CommonButtonBase.h"
#include"UIElementButton.generated.h"

//

UCLASS() class FTHISJOB_API UUIElementButton : public UCommonButtonBase
{
    GENERATED_BODY()

    private:

    protected:

    UPROPERTY() bool bIsEditing{false};

    UPROPERTY(EditAnywhere , Category = "UIElement|Navigation") UUIElementButton * UpUIElement;
    UPROPERTY(EditAnywhere , Category = "UIElement|Navigation") UUIElementButton * DownUIElement;

    public:

    private:

    protected:

    virtual void NativeConstruct() override;

    virtual void NativeOnHovered() override;
    virtual void NativeOnUnhovered() override;

    public:
};