// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfMode.h"
#include <algorithm>
#include "Blueprint/WidgetLayoutLibrary.h"


void ADoppelkopfMode::StartPlay() {
	
	ShuffleCards();

	Super::StartPlay();
}

void ADoppelkopfMode::PostLogin(APlayerController* NewPlayerController) {

	UWorld* World = GetWorld();
	if (World != nullptr) {
		UWidgetLayoutLibrary::RemoveAllWidgets(World);
	}

	FInputModeGameAndUI inputMode;
	NewPlayerController->SetInputMode(inputMode);
	NewPlayerController->bShowMouseCursor = true;
	
	Super::PostLogin(NewPlayerController);
}

void ADoppelkopfMode::ShuffleCards() {

	NewDeck.Empty();
	std::random_shuffle(std::begin(CurrentDeck), std::end(CurrentDeck));
	
	for (int i = 0; i < 48; i++) {
		NewDeck.Add(CurrentDeck[i]);
	}
	askedForCards = 0;
}

TArray<int32> ADoppelkopfMode::GiveCards() {

	TArray<int32> hand; 
	for (int i = askedForCards * 12; i < askedForCards * 12 + 12; i++) {
		hand.Add(NewDeck[i]);
	}
	askedForCards++;
	return hand;		
}