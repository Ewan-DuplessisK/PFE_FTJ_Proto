//Header

#include"UI/Menus/GameLayoutWidget.h"

#include"Widgets/CommonActivatableWidgetContainer.h"

//Private

//Protected

//Public

UCommonActivatableWidgetStack * UGameLayoutWidget::GetStack() const
{
    check(WidgetStack);
    return(WidgetStack);
}