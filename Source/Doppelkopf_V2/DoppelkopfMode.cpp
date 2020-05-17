// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfMode.h"
#include <algorithm>
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "DoppelkopfGameInstance.h"
#include "Engine/World.h"
#include "DoppelkopfGameState.h"

ADoppelkopfMode::ADoppelkopfMode() {
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BaseClasses/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void ADoppelkopfMode::StartPlay() {
	
	ShuffleCards();
	GameCalculation = GameLogic();

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

AActor* ADoppelkopfMode::ChoosePlayerStart_Implementation(AController* Player) {
	
	// create array with all PlayerStart Actors
	TArray<AActor*> PlayerStarts;
	TSubclassOf< APlayerStart > PlayerStart = APlayerStart::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerStart, PlayerStarts);
	
	//Loop through Array, spawn only if the spawn is not already taken
	for (auto Spawn : PlayerStarts) {
		if (Cast< APlayerStart>(Spawn)->PlayerStartTag != "Taken") {
			Cast< APlayerStart>(Spawn)->PlayerStartTag = "Taken";
			return Spawn;
		}
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}

void ADoppelkopfMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	int player = Cast<ADoppelkopfGameState>(GetWorld()->GetGameState())->ActivePlayerIndex;
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
	if (askedForCards >= 4) {
		hand.Init(0, 12);
		return hand;
	}

	for (int i = askedForCards * 12; i < askedForCards * 12 + 12; i++) {
		hand.Add(NewDeck[i]);
	}
	askedForCards++;
	return hand;		
}


void ADoppelkopfMode::Trick(int32 PlayedCard) {
	GameCalculation.AddCardToTrick(PlayedCard);
}