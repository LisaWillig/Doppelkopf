// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfGameState.h"
#include "DoppelkopfPlayerState.h"


ADoppelkopfGameState::ADoppelkopfGameState() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ADoppelkopfGameState::BeginPlay() {
	Super::BeginPlay();
}


void ADoppelkopfGameState::Tick(float DeltaTime) {
	
    Super::Tick(DeltaTime);
	
	while (bPlay == false) {
		bPlay = HasBegunPlay();
	}
	if (PlayerArray.Num() == 4) {
		ActivePlayerIndex = 0;
		Cast<ADoppelkopfPlayerState>(PlayerArray[1])->myTurn = true;
	}
	    
}
