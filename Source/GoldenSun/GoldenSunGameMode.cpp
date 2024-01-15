// Copyright Epic Games, Inc. All Rights Reserved.

#include "GoldenSunGameMode.h"
#include "GoldenSunCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGoldenSunGameMode::AGoldenSunGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
