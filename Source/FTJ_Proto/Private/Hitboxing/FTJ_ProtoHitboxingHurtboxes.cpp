#include"Hitboxing/FTJ_ProtoHitboxingHurtboxes.h"

void UFTJ_ProtoHitboxingHurtboxes::BeginPlay()
{
    //Delegates to SkeletalMeshComponent
    Super::BeginPlay();
    //Subscribes to overlaps
    Super::OnComponentBeginOverlap.AddDynamic(this , &UFTJ_ProtoHitboxingHurtboxes::OnOverlapped);
    //Resets overlapped hurtbox
    Hurtbox = NAME_None;
    //Resets overlapped attackbox
    Attackbox = NAME_None;
}

void UFTJ_ProtoHitboxingHurtboxes::OnOverlapped(UPrimitiveComponent * InOverlapped , AActor * InActor , UPrimitiveComponent * InOther , int32 InBody , bool bInSweep , FHitResult const& InSweep)
{
    //Checks overlap correctness
    if(InSweep.Item <= 0)
    {
        //Returns if incorrect
        return;
    }
    //Stores overlapped hitbox
    FName * Hitbox{nullptr};
    //Checks hurtbox overlap
    if(Cast<UFTJ_ProtoHitboxingHurtboxes>(InSweep.Component))
    {
        //Selects attackbox overlap
        Hitbox = &Hurtbox;
    }
    //Checks attackbox overlap
    else
    {
        //Selects attackbox overlap
        Hitbox = &Attackbox;
    }
    //Retrieves hitbox name
    *Hitbox = FindConstraintBoneName(InSweep.Item - 1);
    //Checks overlap completeness
    if(Hurtbox != NAME_None && Attackbox != NAME_None)
    {
        //TEMPORARY
        UE_LOG(LogTemp , Log , TEXT("%s") , *Attackbox.ToString().Append(" > ").Append(Hurtbox.ToString()));
        //Resets overlapped hurtbox
        Hurtbox = NAME_None;
        //Resets overlapped attackbox
        Attackbox = NAME_None;
        //Disables furher overlaps
        SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}