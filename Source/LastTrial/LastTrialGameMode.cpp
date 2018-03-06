// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LastTrialGameMode.h"
#include "LastTrialHUD.h"
#include "LastTrialCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALastTrialGameMode::ALastTrialGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALastTrialHUD::StaticClass();
}
