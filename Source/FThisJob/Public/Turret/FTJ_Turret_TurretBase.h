#pragma once

#include"CoreMinimal.h"
#include"GameFramework/Pawn.h"
#include"HitInterface.h"
#include"Interfaces/KickedInterface.h"
#include"FTJ_Turret_TurretBase.generated.h"

class UAIPerceptionComponent;
class AFTJ_Turret_ProjectileBase;
class UAISenseConfig_Sight;
class UNiagaraComponent;
class UFTJ_ScoringSystem_Score;
class UCapsuleComponent;

//An AFTJ_Turret_Turret base compatibility layer.
UCLASS() class FTHISJOB_API AFTJ_Turret_TurretBase : public APawn , public IHitInterface
{
    GENERATED_BODY()

    //Private variables
    private :
    //The remaining durability.
    float Health;
    //The sensed user.
    AActor * Player;
    //The shooting controller.
    FTimerHandle Timer;
    //The rendered shape.
    USkeletalMeshComponent * Mesh;
    UCapsuleComponent * Collision;
    //The detection module.
    UAIPerceptionComponent * Perception;
    //The sensing model.
    UAISenseConfig_Sight * Sight;
    UAudioComponent * ShowSound;
    UAudioComponent * ShootSound;
    UAudioComponent * HitSound;
    UAudioComponent * DeathSound;
    UAudioComponent * HideSound;
    UNiagaraComponent * ShowEffect;
    UNiagaraComponent * ShootEffect;
    UNiagaraComponent * HitEffect;
    UNiagaraComponent * DeathEffect;
    UNiagaraComponent * AdditionalDeathEffect;
    //The shot type to spawn.
    UPROPERTY(EditAnywhere , AdvancedDisplay) UClass * ProjectileClass;
    //The duration after popping out.
    UPROPERTY(EditAnywhere) float ShowingDelay;
    //The shooting delay lower bound.
    UPROPERTY(EditAnywhere) float MinimalCooldown;
    //The shooting delay higher bound.
    UPROPERTY(EditAnywhere) float MaximalCooldown;
    //The duration before popping in.
    UPROPERTY(EditAnywhere) float HidingDelay;
    //The damage taken to destroy.
    UPROPERTY(EditAnywhere) float HealthLimit;
    //The sight radius to trigger.
    UPROPERTY(EditAnywhere) float Range;
    UPROPERTY(EditAnywhere) int32 ScoreForDestruction;
    UPROPERTY(EditAnywhere) double HeadRotationSpeed;
    UPROPERTY(EditAnywhere) double ShootingMarginalError;

    //Protected variables
    protected :
    //The perception's player detection status.
    UPROPERTY(BlueprintReadOnly) bool bIsSensing;
    //The rig's head control point.
    UPROPERTY(BlueprintReadOnly) FTransform Control;
    UPROPERTY(BlueprintReadOnly) bool bIsHit;
    UPROPERTY(BlueprintReadOnly) bool bIsShooting;

    //Public variables
    public :

    //Private functions
    private :
    //Configures the health, perception, mesh.
    void BeginPlay() override;
    /*
        Updates the rotation.
        For parameters, go to AActor::Tick.
    */
    void Tick(float InDelta) override;
    /*
        Takes damage if shown and destroys on 0 health.
        For parameters, go to IHitInterface::GetHit.
    */
    void GetHit_Implementation(float InDamage , float InStun , FVector InKnockback , float InInvincibility , AActor * InSource) override;
    void EndPlay(EEndPlayReason::Type const InReason) override;
    //Spawns a projectile and sets up a shooting timer.
    void Shoot();
    /*
        Begins shooting after delaying if showing, ends to do it and waits before hiding otherwise.
        For parameters, go to FActorPerceptionUpdatedDelegate.
    */
    UFUNCTION() void OnSensed(AActor * InActor , FAIStimulus InStimulus);
    /*
        Implements the Range field getter.

        @return The sight radius to trigger.
    */
    UFUNCTION(BlueprintCallable) float GetRange();
    /*
        Implements the Range field setter.

        @param InRange The sight radius to trigger.
    */
    UFUNCTION(BlueprintCallable) void SetRange(float InRange);

    //Protected functions
    protected :

    //Public functions
    public :
};