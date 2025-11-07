#include"Hitboxing/FTJHitboxingAttackboxes.h"

void UFTJHitboxingAttackboxes::BeginPlay()
{
    //Delegate to SkeletalMeshComponent
    Super::BeginPlay();
    //Subscribe to overlaps
    OnComponentBeginOverlap.AddDynamic(this , &UFTJHitboxingAttackboxes::OnHit);
}

UFTJHitboxingAttackboxes::UFTJHitboxingAttackboxes()
{
    //Configure valid preset
    SetCollisionProfileName("Attackbox");
}

void UFTJHitboxingAttackboxes::Enable()
{
    //Enable overlap registration
    SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UFTJHitboxingAttackboxes::Disable()
{
    //Disable overlap registration
    SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UFTJHitboxingAttackboxes::OnHit(UPrimitiveComponent * InOverlapped , AActor * InActor , UPrimitiveComponent * InOther , int32 InBody , bool bInSweep , FHitResult const& InSweep)
{
    //Check overlap correctness
    if(InSweep.Item < 0)
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