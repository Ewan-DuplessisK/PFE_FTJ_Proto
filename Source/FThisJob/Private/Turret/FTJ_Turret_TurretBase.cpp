#include"Turret/FTJ_Turret_TurretBase.h"

#include"Perception/AIPerceptionComponent.h"
#include"Perception/AISenseConfig_Sight.h"
#include"NiagaraComponent.h"
#include"Components/AudioComponent.h"
#include"Kismet/GameplayStatics.h"

#include"Turret/FTJ_Turret_ProjectileBase.h"
#include"ScoringSystem/FTJ_ScoringSystem_Score.h"

void AFTJ_Turret_TurretBase::BeginPlay()
{
    //Delegate to APawn
    Super::BeginPlay();
    //Set the durability to remain
    Health = HealthLimit;
    //Cache the module to detect
    Perception = GetComponentByClass<UAIPerceptionComponent>();
    //Subscribe to detections
    Perception->OnTargetPerceptionUpdated.AddDynamic(this , &AFTJ_Turret_TurretBase::OnSensed);
    //Cache the model to sense
    Sight = Perception->GetSenseConfig<UAISenseConfig_Sight>();
    //Cache the shape to render
    Mesh = GetComponentByClass<USkeletalMeshComponent>();
    //Synchronize the sight radius to trigger with the perception
    SetRange(Range);
    ShowSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("ShowSound")));
    ShootSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("ShootSound")));
    HitSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("HitSound")));
    DeathSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("DeathSound")));
    HideSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("HideSound")));
    ShootEffect = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("ShootEffect")));
    HitEffect = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("HitEffect")));
    DeathEffect = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("DeathEffect")));
    SetActorTickEnabled(false);
}

void AFTJ_Turret_TurretBase::Tick(float InDelta)
{
    //Delegate to AActor
    Super::Tick(InDelta);
    //Check the perception's player detection status and actor correctness because it can be already destroyed
    if(!IsValid(Player))
    {
        return;
    }
    //Convert to the control basis
    auto Space{GetActorTransform().InverseTransformVectorNoScale(Player->GetActorLocation() - Mesh->GetSocketLocation("ProjectileSocket")).Rotation()};
    //Apply rotations separately
    Control.SetRotation(FQuat::FastLerp(Control.GetRotation() , FRotator{0.0 , 0.0 , -Space.Yaw}.Quaternion() * FRotator{Space.Pitch , 0.0 , 0.0}.Quaternion() , 5.0 * InDelta));
    bIsHit = false;
    bIsShooting = false;
}

void AFTJ_Turret_TurretBase::GetHit_Implementation(float InDamage , float InStun , FVector InKnockback , float InInvincibility , AActor * InSource)
{
    //Check the player detection status
    if(!bIsSensing || Health <= 0.0)
    {
        return;
    }
    //Take damage, destroy on 0
    Health -= InDamage;
    if(Health <= 0.0)
    {
        DeathSound->Activate();
        DeathEffect->Activate();
        Perception->OnTargetPerceptionUpdated.RemoveDynamic(this , &AFTJ_Turret_TurretBase::OnSensed);
        SetActorTickEnabled(false);
        GetWorld()->GetTimerManager().SetTimer
        (
            Timer
            ,
            [&]
            {
                Mesh->SetVisibility(false);
                GetWorld()->GetTimerManager().SetTimer
               (
                   Timer
                   ,
                   [&]
                   {
                       if (IsValid(UGameplayStatics::GetPlayerPawn(GetWorld() , 0)))
                       {
                           UGameplayStatics::GetPlayerPawn(GetWorld() , 0)->GetComponentByClass<UFTJ_ScoringSystem_Score>()->IncreaseWithText(ScoreForDestruction , 0 , FText::FromString("Turret"));
                       }
                       
                       Destroy();
                   }
                   ,
                   1'000'000.0 , false , 1.0
               );
            }
            ,
            1'000'000.0 , false , 1.0
        );
        return;
    }
    HitSound->Activate();
    HitEffect->Activate();
    bIsHit = true;
}

void AFTJ_Turret_TurretBase::Shoot()
{
    //Spawn a projectile
    GetWorld()->SpawnActor<AFTJ_Turret_ProjectileBase>(ProjectileClass , Mesh->GetSocketTransform("ProjectileSocket"))->Spawn(this);
    //Set up a shooting timer
    GetWorld()->GetTimerManager().SetTimer(Timer , this , &AFTJ_Turret_TurretBase::Shoot , 1'000'000.0 , false , FMath::RandRange(MinimalCooldown , MaximalCooldown));
    ShootSound->Activate();
    ShootEffect->Activate();
    bIsShooting = true;
}

void AFTJ_Turret_TurretBase::OnSensed(AActor * InActor , FAIStimulus InStimulus)
{
    //Check actor correctness, it can be not a player
    if(auto Actor{Cast<APawn>(InActor)} ; !IsValid(Actor) || !Actor->IsPlayerControlled())
    {
        return;
    }
    //Remember as the sensed user
    Player = InActor;
    //Check the player detection status
    if(InStimulus.WasSuccessfullySensed())
    {
        //Shoots after delaying
        bIsSensing = true;
        GetWorld()->GetTimerManager().SetTimer
        (
            Timer
            ,
            [&]
            {
                Shoot();
                SetActorTickEnabled(true);
            }
            ,
            1'000'000.0 , false , ShowingDelay
        );
        ShowSound->Activate();
    }
    else
    {
        SetActorTickEnabled(false);
        //End shooting, wait before hiding
        GetWorld()->GetTimerManager().SetTimer
        (
            Timer
            ,
            [&]
            {
                bIsSensing = false;
                HideSound->Activate();
            }
            ,
            1'000'000.0 , false , HidingDelay
        );
    }
}

float AFTJ_Turret_TurretBase::GetRange()
{
    //Just return a copy directly
    return(Range);
}

void AFTJ_Turret_TurretBase::SetRange(float InRange)
{
    //Ask to apply distance changes
    Range = InRange;
    Sight->SightRadius = Range;
    Sight->LoseSightRadius = Range;
    Perception->RequestStimuliListenerUpdate();
}