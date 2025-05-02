#include"Hitboxing/FTJHitboxingHitboxes.h"

UFTJHitboxingHitboxes::UFTJHitboxingHitboxes()
{
    //Enable touch registration
    SetGenerateOverlapEvents(true);
    //Enable precise collision
    bMultiBodyOverlap = true;
    //Disable mesh visibility
    SetHiddenInGame(true);
}