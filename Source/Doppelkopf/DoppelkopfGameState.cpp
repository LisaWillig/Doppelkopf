// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfGameState.h"
#include "DoppelkopfPlayerState.h"
#include "Net/UnrealNetwork.h"


ADoppelkopfGameState::ADoppelkopfGameState() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ADoppelkopfGameState::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
		GameCalculation = GameLogic();
	}
}

void ADoppelkopfGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADoppelkopfGameState, ActivePlayerIndex);
}

void ADoppelkopfGameState::Tick(float DeltaTime) {
	
    Super::Tick(DeltaTime);
	
	while (bPlay == false) {
		bPlay = HasBegunPlay();
	}
	if (PlayerArray.Num() == 4) {
		Cast<ADoppelkopfPlayerState>(PlayerArray[ActivePlayerIndex])->ActivatePlayerControllersTurn();
	}
}

void ADoppelkopfGameState::Trick(int32 PlayedCard) {
	GameCalculation.AddCardToTrick(PlayedCard); 	
}

void ADoppelkopfGameState::SetActivePlayer() {
	ActivePlayerIndex = (ActivePlayerIndex + 1) % 4;
}

