//Header

#include"UI/Menus/InGameMenuWidget.h"

//Private

TOptional<FUIInputConfig> UInGameMenuWidget::GetDesiredInputConfig() const
{
    return(FUIInputConfig{ECommonInputMode::Game , EMouseCaptureMode::CapturePermanently});
}

//Protected

//Public