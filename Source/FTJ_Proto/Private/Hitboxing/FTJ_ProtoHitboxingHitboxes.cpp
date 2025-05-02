#include"Hitboxing/FTJ_ProtoHitboxingHitboxes.h"

UFTJ_ProtoHitboxingHitboxes::UFTJ_ProtoHitboxingHitboxes()
{
    //Enable touch registration
    SetGenerateOverlapEvents(true);
    //Enable precise collision
    bMultiBodyOverlap = true;
}