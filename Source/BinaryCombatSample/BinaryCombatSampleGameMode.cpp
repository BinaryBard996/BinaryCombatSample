// Copyright Epic Games, Inc. All Rights Reserved.

#include "BinaryCombatSampleGameMode.h"
#include "BinaryCombatSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABinaryCombatSampleGameMode::ABinaryCombatSampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
