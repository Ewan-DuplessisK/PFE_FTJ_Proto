#include"Hitboxing/FTJ_ProtoHitboxingHitboxes.h"

UFTJ_ProtoHitboxingHitboxes::UFTJ_ProtoHitboxingHitboxes()
{
    //Enables touch registration
    SetGenerateOverlapEvents(true);
    //Enables precise collision
    bMultiBodyOverlap = true;
}