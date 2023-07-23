// Copyright Epic Games, Inc. All Rights Reserved.

#include "SupermanUnlimitedGameMode.h"
#include "SupermanUnlimitedCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASupermanUnlimitedGameMode::ASupermanUnlimitedGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
