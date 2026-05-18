//Header

#include"UI/UIElements/CommonTextBlockDropdown.h"

//Private

void UCommonTextBlockDropdown::NativeConstruct()
{
    Super::NativeConstruct();
}

//Protected

//Public

UCommonTextBlock * UCommonTextBlockDropdown::GetCommonTextBlock() const
{
    return(CommonTextBlock);
}