#include"Hitboxing/FTJ_ProtoHitboxingAttackboxes.h"

void UFTJ_ProtoHitboxingAttackboxes::BeginPlay()
{
    //Delegates to SkeletalMeshComponent
    Super::BeginPlay();
    //Subscribes to overlaps
    OnComponentBeginOverlap.AddDynamic(this , &UFTJ_ProtoHitboxingAttackboxes::OnHit);
}

UFTJ_ProtoHitboxingAttackboxes::UFTJ_ProtoHitboxingAttackboxes()
{
    //Configures valid preset
    SetCollisionProfileName("Attackbox");
}

void UFTJ_ProtoHitboxingAttackboxes::Enable()
{
    //Enables overlap registration
    SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UFTJ_ProtoHitboxingAttackboxes::Disable()
{
    //Disables overlap registration
    SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UFTJ_ProtoHitboxingAttackboxes::OnHit(UPrimitiveComponent * InOverlapped , AActor * InActor , UPrimitiveComponent * InOther , int32 InBody , bool bInSweep , FHitResult const& InSweep)
{
    //Checks overlap correctness
    if(InSweep.Item <= 0)
    {
        //Returns if incorrect
        return;
    }
    //Writes overlap data
    HitResult.Record(InSweep);
    //Checks overlap completeness
    if(HitResult.IsPopulated())
    {
        //Notifies about overlap
        HitEvent.Broadcast(HitResult);
        //Clears overlap data
        HitResult.Reset();
        //Disables furher overlaps
        Disable();
    }
}