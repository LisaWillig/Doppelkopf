// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Doppelkopf_V2GameMode.h"
#include "UObject/ConstructorHelpers.h"

ADoppelkopf_V2GameMode::ADoppelkopf_V2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BaseClasses/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}
