// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectIdleGameMode.h"
#include "ProjectIdlePlayerController.h"
#include "ProjectIdleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectIdleGameMode::AProjectIdleGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjectIdlePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}