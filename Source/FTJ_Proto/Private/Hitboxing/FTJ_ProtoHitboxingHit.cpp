#include"Hitboxing/FTJ_ProtoHitboxingHit.h"

#include"Hitboxing/FTJ_ProtoHitboxingAttackboxes.h"

FFTJ_ProtoHitboxingHit::FFTJ_ProtoHitboxingHit()
{
    //Clear overlap data
    Reset();
}

void FFTJ_ProtoHitboxingHit::Record(FHitResult const& InSweep)
{
    //Store overlapped hitbox
    FName * Hitbox{nullptr};
    //Check hurtbox overlap
    if(Cast<UFTJ_ProtoHitboxingAttackboxes>(InSweep.Component))
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
    *Hitbox = Cast<UFTJ_ProtoHitboxingHitboxes>(InSweep.Component)->FindConstraintBoneName(InSweep.Item - 1);
}

bool FFTJ_ProtoHitboxingHit::IsPopulated()
{
    //Check overlap completeness
    return(Attackbox != NAME_None && Hurtbox != NAME_None);
}

void FFTJ_ProtoHitboxingHit::Reset()
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