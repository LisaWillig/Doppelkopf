// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayingCard.h"
#include "DoppelkopfGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ADoppelkopfGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADoppelkopfGameMode();

	virtual void BeginPlay() override;

	TArray<int> DoppelKopfPool = { 0,0,8,8,9,9,10,10,11,11,12,12, 
		13,13,21,21,22,22,23,23,24,24,25,25,
		26,26,34,34,35,35,36,36,37,37,38,38,
		39,39,47,47,48,48,49,49,50,50,51,51};

	TArray<int> CardDeck;

	void GiveCards();

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = PlayingCard)
	TSubclassOf<APlayingCard> PlayingCard;
};



