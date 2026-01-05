#include"Turret/FTJ_Turret_ProjectileBase.h"

#include"Components/CapsuleComponent.h"

#include"HitInterface.h"
#include"Turret/FTJ_Turret_TurretBase.h"

void AFTJ_Turret_ProjectileBase::BeginPlay()
{
    //Delegate to AActor
    Super::BeginPlay();
    //Subscribe to collisions
    GetComponentByClass<UCapsuleComponent>()->OnComponentHit.AddDynamic(this , &AFTJ_Turret_ProjectileBase::OnHit);
}

void AFTJ_Turret_ProjectileBase::OnHit(UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult)
{
    //Use HitInterface and destroys itself
    if(InActor->Implements<UHitInterface>())
    {
        IHitInterface::Execute_GetHit(InActor , Damage , 0.0 , (InActor->GetActorLocation() - GetActorLocation()).GetSafeNormal() , 0.0 , Turret);
    }
    Destroy();
}

void AFTJ_Turret_ProjectileBase::Spawn(AFTJ_Turret_TurretBase * InTurret)
{
    //Just copy parameters into fields
    Turret = InTurret;
}