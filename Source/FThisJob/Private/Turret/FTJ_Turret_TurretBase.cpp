#include"Turret/FTJ_Turret_TurretBase.h"

#include"Perception/AIPerceptionComponent.h"
#include"Perception/AISenseConfig_Sight.h"
#include"NiagaraComponent.h"
#include"Components/AudioComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Components/CapsuleComponent.h"

#include"Turret/FTJ_Turret_ProjectileBase.h"
#include"ScoringSystem/FTJ_ScoringSystem_Score.h"

void AFTJ_Turret_TurretBase::BeginPlay()
{
    //Delegate to APawn
    Super::BeginPlay();
    //Set the durability to remain
    Health = HealthLimit;
    //Cache the shape to render
    Mesh = GetComponentByClass<USkeletalMeshComponent>();
    Collision = GetComponentByClass<UCapsuleComponent>();
    //Cache the module to detect
    Perception = GetComponentByClass<UAIPerceptionComponent>();
    //Subscribe to detections
    Perception->OnTargetPerceptionUpdated.AddDynamic(this , &AFTJ_Turret_TurretBase::OnSensed);
    //Cache the model to sense
    Sight = Perception->GetSenseConfig<UAISenseConfig_Sight>();
    //Synchronize the sight radius to trigger with the perception
    SetRange(Range);
    ShowSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("ShowSound")));
    ShootSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("ShootSound")));
    HitSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("HitSound")));
    DeathSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("DeathSound")));
    HideSound = Cast<UAudioComponent>(GetDefaultSubobjectByName(TEXT("HideSound")));
    ShowEffect = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("ShowEffect")));
    ShootEffect = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("ShootEffect")));
    HitEffect = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("HitEffect")));
    DeathEffect = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("DeathEffect")));
    AdditionalDeathEffect = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("AdditionalDeathEffect")));
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
    Control.SetRotation(FQuat::FastLerp(Control.GetRotation() , FRotator{0.0 , 0.0 , -Space.Yaw}.Quaternion() * FRotator{Space.Pitch , 0.0 , 0.0}.Quaternion() , HeadRotationSpeed * InDelta));
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
        AdditionalDeathEffect->Activate();
        Perception->OnTargetPerceptionUpdated.RemoveDynamic(this , &AFTJ_Turret_TurretBase::OnSensed);
        SetActorTickEnabled(false);
        Mesh->SetVisibility(false);
        Collision->SetSimulatePhysics(false);
        Collision->SetCollisionProfileName("NoCollision");
        GetWorld()->GetTimerManager().SetTimer
        (
            Timer
            ,
            [&]
            {
	               UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UFTJ_ScoringSystem_Score>()->IncreaseWithText(ScoreForDestruction , 0 , FText::FromString("Turret"));
                Destroy();
            }
            ,
            1'000'000.0 , false , 3.0
        );
        return;
    }
    HitSound->Activate();
    HitEffect->Activate();
    bIsHit = true;
}

void AFTJ_Turret_TurretBase::EndPlay(EEndPlayReason::Type const InReason)
{
    GetWorld()->GetTimerManager().ClearTimer(Timer);
    Super::EndPlay(InReason);
}

void AFTJ_Turret_TurretBase::Shoot()
{
    //Set up a shooting timer
    GetWorld()->GetTimerManager().SetTimer
    (
        Timer
        ,
        [&]
        {
            //Spawn a projectile
            GetWorld()->SpawnActor<AFTJ_Turret_ProjectileBase>
            (
                ProjectileClass , FTransform
                {
                    FQuat::MakeFromEuler({0.0 , FMath::RandRange(-ShootingMarginalError , +ShootingMarginalError) , FMath::RandRange(-ShootingMarginalError , +ShootingMarginalError)})
                }
                * Mesh->GetSocketTransform("ProjectileSocket")
            )
            ->Spawn(this);
            Shoot();
            ShootSound->Activate();
            ShootEffect->Activate();
            bIsShooting = true;
        }
        ,
        1'000'000.0 , false , FMath::RandRange(MinimalCooldown , MaximalCooldown)
    );
}

void AFTJ_Turret_TurretBase::OnSensed(AActor * InActor , FAIStimulus InStimulus)
{
    //Check actor correctness, it can be not a player
    if(auto Pawn{Cast<APawn>(InActor)} ; !IsValid(Pawn) || !Pawn->IsPlayerControlled())
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
        ShowEffect->Activate();
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