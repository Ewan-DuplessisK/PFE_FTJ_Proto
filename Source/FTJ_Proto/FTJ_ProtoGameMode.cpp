// Copyright Epic Games, Inc. All Rights Reserved.

#include "FTJ_ProtoGameMode.h"
#include "FTJ_ProtoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFTJ_ProtoGameMode::AFTJ_ProtoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
