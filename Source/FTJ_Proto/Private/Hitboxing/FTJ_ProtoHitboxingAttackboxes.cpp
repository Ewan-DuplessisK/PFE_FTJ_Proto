#include"Hitboxing/FTJ_ProtoHitboxingAttackboxes.h"

void UFTJ_ProtoHitboxingAttackboxes::BeginPlay()
{
    //Delegate to SkeletalMeshComponent
    Super::BeginPlay();
    //Subscribe to overlaps
    OnComponentBeginOverlap.AddDynamic(this , &UFTJ_ProtoHitboxingAttackboxes::OnHit);
}

UFTJ_ProtoHitboxingAttackboxes::UFTJ_ProtoHitboxingAttackboxes()
{
    //Configure valid preset
    SetCollisionProfileName("Attackbox");
}

void UFTJ_ProtoHitboxingAttackboxes::Enable()
{
    //Enable overlap registration
    SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UFTJ_ProtoHitboxingAttackboxes::Disable()
{
    //Disable overlap registration
    SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UFTJ_ProtoHitboxingAttackboxes::OnHit(UPrimitiveComponent * InOverlapped , AActor * InActor , UPrimitiveComponent * InOther , int32 InBody , bool bInSweep , FHitResult const& InSweep)
{
    //Check overlap correctness
    if(InSweep.Item <= 0)
    {
        //Return if incorrect
        return;
    }
    //Write overlap data
    HitResult.Record(InSweep);
    //Check overlap completeness
    if(HitResult.IsPopulated())
    {
        //Notifie about overlap
        HitEvent.Broadcast(HitResult);
        //Clear overlap data
        HitResult.Reset();
        //Disable furher overlaps
        Disable();
    }
}