#include"Hitboxing/FTJ_ProtoHitboxingHit.h"

#include"Hitboxing/FTJ_ProtoHitboxingAttackboxes.h"

FFTJ_ProtoHitboxingHit::FFTJ_ProtoHitboxingHit()
{
    //Clears overlap data
    Reset();
}

void FFTJ_ProtoHitboxingHit::Record(FHitResult const& InSweep)
{
    //Stores overlapped hitbox
    FName * Hitbox{nullptr};
    //Checks hurtbox overlap
    if(Cast<UFTJ_ProtoHitboxingAttackboxes>(InSweep.Component))
    {
        //Selects attackbox overlap
        Hitbox = &Attackbox;
    }
    //Checks attackbox overlap
    else
    {
        //Selects attackbox overlap
        Hitbox = &Hurtbox;
    }
    //Retrieves hitbox name
    *Hitbox = Cast<UFTJ_ProtoHitboxingHitboxes>(InSweep.Component)->FindConstraintBoneName(InSweep.Item - 1);
}

bool FFTJ_ProtoHitboxingHit::IsPopulated()
{
    //Checks overlap completeness
    return(Attackbox != NAME_None && Hurtbox != NAME_None);
}

void FFTJ_ProtoHitboxingHit::Reset()
{
    //Clears damaging entity
    Attackboxer = nullptr;
    //Clears damaged entity
    Hurtboxer = nullptr;
    //Clears attackboxer hitbox
    Attackbox = NAME_None;
    //Clears hurtboxer hitbox
    Hurtbox = NAME_None;
}