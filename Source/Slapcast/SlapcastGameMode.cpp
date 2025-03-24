// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlapcastGameMode.h"
#include "SlapcastCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASlapcastGameMode::ASlapcastGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
