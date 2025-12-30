// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChaosDestroyResearchGameMode.h"
#include "ChaosDestroyResearchCharacter.h"
#include "UObject/ConstructorHelpers.h"

AChaosDestroyResearchGameMode::AChaosDestroyResearchGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
