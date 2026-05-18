//Header

#include"UI/Menus/QuitPanelWidget.h"

//Private

FReply UQuitPanelWidget::NativeOnKeyDown(FGeometry const& InGeometry , FKeyEvent const& InKeyEvent)
{
    auto Reply{Super::NativeOnKeyDown(InGeometry , InKeyEvent)};
    if(InKeyEvent.GetKey() == EKeys::Gamepad_FaceButton_Right || InKeyEvent.GetKey() == EKeys::Escape)
    {
        OnQuitAborted();
        return(FReply::Handled());
    }
    return(Reply);
}

//Protected

//Public