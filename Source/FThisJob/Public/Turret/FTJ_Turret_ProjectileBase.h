#pragma once

#include"CoreMinimal.h"
#include"GameFramework/Actor.h"
#include"FTJ_Turret_ProjectileBase.generated.h"

class UCapsuleComponent;
class UHitInterface;
class AFTJ_Turret_TurretBase;
class AFTJ_Turret_DecalBase;

//An AFTJ_Turret_Projectile base compatibility layer.
UCLASS() class FTHISJOB_API AFTJ_Turret_ProjectileBase : public AActor
{
    GENERATED_BODY()

    //Private variables
    private :
    //The owning actor.
    AFTJ_Turret_TurretBase * Turret;
    UPROPERTY(EditDefaultsOnly , AdvancedDisplay) TSubclassOf<AFTJ_Turret_DecalBase> DecalSpawnClass;
    //The health amount to reduce.
    UPROPERTY(EditDefaultsOnly) float Damage;

    //Protected variables
    protected :

    //Public variables
    public :

    //Private functions
    private :
    //Configures the collision.
    void BeginPlay() override;
    /*
        Uses HitInterface and destroys itself.
        For parameters, go to FComponentHitSignature.
    */
    UFUNCTION() void OnHit(UPrimitiveComponent * InThisComponent , AActor * InActor , UPrimitiveComponent * InThatComponent , FVector InImpulse , FHitResult const& InResult);

    //Protected functions
    protected :

    //Public functions
    public :
    /*
        Implements C++ constructor as a stub for Unreal Engine.

        @param InTurret The owning actor.
    */
    void Spawn(AFTJ_Turret_TurretBase * InTurret);
};