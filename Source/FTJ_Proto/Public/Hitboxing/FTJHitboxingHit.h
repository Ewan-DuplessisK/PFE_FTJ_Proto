#pragma once

#include"CoreMinimal.h"
#include"FTJHitboxingHit.generated.h"

//Hitbox overlap data
USTRUCT(BlueprintType) struct FFTJHitboxingHit
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
    FFTJHitboxingHit();
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