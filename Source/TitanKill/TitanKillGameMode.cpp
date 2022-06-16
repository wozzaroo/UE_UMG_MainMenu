// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TitanKillGameMode.h"
#include "TitanKillHUD.h"
#include "TitanKillCharacter.h"
#include "TKPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ATitanKillGameMode::ATitanKillGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATitanKillHUD::StaticClass();

	// Set our custom player controller class
	PlayerControllerClass = ATKPlayerController::StaticClass();
}
