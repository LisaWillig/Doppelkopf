// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfGameState.h"
#include "DoppelkopfPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "DoppelkopfMode.h"
#include "TrickPosition.h"
#include "GameLogic.h"
#include "Net/UnrealNetwork.h"


ADoppelkopfGameState::ADoppelkopfGameState() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ADoppelkopfGameState::BeginPlay() {
	Super::BeginPlay();
		
	if (HasAuthority()) {
		GameCalculation = GameLogic();
		TrickPos = Cast<ATrickPosition>(UGameplayStatics::GetActorOfClass(GetWorld(), ATrickPosition::StaticClass()));
	}
}

void ADoppelkopfGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADoppelkopfGameState, ActivePlayerIndex);
}

bool ADoppelkopfGameState::HasMatchStarted() const {

	return Super::HasMatchStarted();
}
void ADoppelkopfGameState::Tick(float DeltaTime) {
	
    Super::Tick(DeltaTime);
	
	if (HasMatchStarted() == true && bStart == false && PlayerArray.Num() ==4 && HasAuthority()) {
		StartGame();
	}
}

void ADoppelkopfGameState::StartGame() {
	auto test = Cast<ADoppelkopfMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (test) {
		cardsPlayed = 0;
		ActivePlayerIndex = test->playerIndex;
		SetActivePlayer();
		bStart = true;
	}
}
void ADoppelkopfGameState::Trick(int32 PlayedCard) {

	int8 result = GameCalculation.AddCardToTrick(PlayedCard); 
	cardsPlayed++;
	TrickPos->SpawnCardAtTrick(ActivePlayerIndex, PlayedCard);
	if (result != -1) {
		ActivePlayerIndex = (ActivePlayerIndex + result) % 4; 
		Cast<ADoppelkopfPlayerState>(PlayerArray[ActivePlayerIndex])->AddWonTrick(GameCalculation.LastTrick);
		UE_LOG(LogTemp, Warning, TEXT("Cards Played: %i"), cardsPlayed)
		if (cardsPlayed == 48) {
			UE_LOG(LogTemp, Warning, TEXT("Game is over"))
				for (auto player : PlayerArray) {
					GameLogic::CountResult(Cast<ADoppelkopfPlayerState>(player)->myWonTricks);
				}
		}
		else {
			SetActivePlayer();
		}
	}
}
                       
void ADoppelkopfGameState::SetActivePlayer() {
	for (int i = 0; i < PlayerArray.Num(); i++) {
		if (i == ActivePlayerIndex) {
			Cast<ADoppelkopfPlayerState>(PlayerArray[i])->ActivatePlayerControllersTurn();
		}
	}
	SetTurnHud();
	
	ActivePlayerIndex = (ActivePlayerIndex + 1) % 4;
}

