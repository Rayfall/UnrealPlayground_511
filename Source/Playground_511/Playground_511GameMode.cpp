// Copyright Epic Games, Inc. All Rights Reserved.

#include "Playground_511GameMode.h"
#include "Playground_511Character.h"
#include "UObject/ConstructorHelpers.h"

APlayground_511GameMode::APlayground_511GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
