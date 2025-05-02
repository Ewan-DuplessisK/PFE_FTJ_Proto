#include"Hitboxing/FTJHitboxingHit.h"

#include"Hitboxing/FTJHitboxingAttackboxes.h"

FFTJHitboxingHit::FFTJHitboxingHit()
{
    //Clear overlap data
    Reset();
}

void FFTJHitboxingHit::Record(FHitResult const& InSweep)
{
    //Store overlapped hitbox
    FName * Hitbox{nullptr};
    //Check hurtbox overlap
    if(Cast<UFTJHitboxingAttackboxes>(InSweep.Component))
    {
        //Select attackbox overlap
        Hitbox = &Attackbox;
    }
    //Check attackbox overlap
    else
    {
        //Select attackbox overlap
        Hitbox = &Hurtbox;
    }
    //Retrieve hitbox name
    *Hitbox = Cast<UFTJHitboxingHitboxes>(InSweep.Component)->FindConstraintBoneName(InSweep.Item - 1);
}

bool FFTJHitboxingHit::IsPopulated()
{
    //Check overlap completeness
    return(Attackbox != NAME_None && Hurtbox != NAME_None);
}

void FFTJHitboxingHit::Reset()
{
    //Clear damaging entity
    Attackboxer = nullptr;
    //Clear damaged entity
    Hurtboxer = nullptr;
    //Clear attackboxer hitbox
    Attackbox = NAME_None;
    //Clear hurtboxer hitbox
    Hurtbox = NAME_None;
}