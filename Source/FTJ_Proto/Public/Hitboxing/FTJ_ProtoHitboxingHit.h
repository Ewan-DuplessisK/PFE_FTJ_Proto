#pragma once

#include"CoreMinimal.h"
#include"FTJ_ProtoHitboxingHit.generated.h"

//Hitbox overlap data
USTRUCT(BlueprintType) struct FFTJ_ProtoHitboxingHit
{
    GENERATED_BODY()
    
    //Overlapped damaging entity
    UPROPERTY(BlueprintReadWrite) AActor * Attackboxer;
    //Overlapped damaged entity
    UPROPERTY(BlueprintReadWrite) AActor * Hurtboxer;
    //Overlapped attackboxer hitbox
    UPROPERTY(BlueprintReadWrite) FName Attackbox;
    //Overlapped hurtboxer hitbox
    UPROPERTY(BlueprintReadWrite) FName Hurtbox;

    //Clears overlap data
    FFTJ_ProtoHitboxingHit();
    /*
        Writes overlap data
        @param InSweep OnComponentBeginOverlap SweepResult parameter
    */
    void Record(FHitResult const& InSweep);
    //Checks overlap completeness
    bool IsPopulated();
    //Clears overlap data
    void Reset();
};