// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DoppelkopfGameMode.h"
#include "DoppelkopfPlayerController.h"
#include "Math/UnrealMathUtility.h"
#include "Math/TransformNonVectorized.h"
#include "Engine/World.h"
#include "DoppelkopfPawn.h"

ADoppelkopfGameMode::ADoppelkopfGameMode()
{
	// no pawn by default
	DefaultPawnClass = ADoppelkopfPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ADoppelkopfPlayerController::StaticClass();


}

void ADoppelkopfGameMode::BeginPlay() {
	CardDeck = DoppelKopfPool;

	GiveCards();

}

void ADoppelkopfGameMode::GiveCards() {
	FTransform SpawnPoint = {
		FRotator{0,0,0},
	 FVector(0,0,0.02),
	FVector(1,1,1)};

	while (CardDeck.Num() > 0) {
		int randomCardIndex = FMath::RandRange(0, CardDeck.Num() - 1);
		int chosenCard = CardDeck[randomCardIndex];
		FActorSpawnParameters SpawnParameters;
		auto card = GetWorld()->SpawnActor<APlayingCard>(PlayingCard,
			SpawnPoint, 
			SpawnParameters);


		//card->SetActorLocation(SpawnPoint, false);
		//auto loc = card->GetActorLocation();
		
		FVector New = SpawnPoint.GetLocation();
		New.Y += 25;

		SpawnPoint.SetLocation(New);
		//UE_LOG(LogTemp, Warning, TEXT("Spawn: %s"), *loc.ToString())
		card->SetCard(chosenCard);
		CardDeck.RemoveSingle(chosenCard);

	}

}