// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic.h"

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::ResetTrick() {
	TrickCardCount = 0;
	CurrentTrick.Empty();
}
void GameLogic::AddCardToTrick(uint8 MeshValue) {
	UE_LOG(LogTemp, Warning, TEXT("Card Played: %i, Nb in Trick: %i"), MeshValue, CurrentTrick.Num())
	CurrentTrick.Add(CardGameValue[MeshValue]);
	TrickCardCount++;
	if (TrickCardCount == 4) {

		uint8 trickwinner = CalculateTrickResult(CurrentTrick);
		UE_LOG(LogTemp, Warning, TEXT("Winner of the Trick: %i"), trickwinner)
		ResetTrick();
	}
	
}


uint8 GameLogic::CalculateTrickResult(TArray<uint8> Trick) {
	CheckTrickSpecial(Trick);

	uint8 highestCard = Trick[0];
	uint8 indexTrickWinner = 0;
	// Farbstich ohne Trumpf
	if (!Trick.ContainsByPredicate([](uint8 item) {return item > 30;})) {
		// Herzstich
		if (Trick[0] < 10){
			for (int i = 1; i < 4; i++) {
				if (Trick[i] > highestCard && Trick[i] < 10) {
					highestCard = Trick[i];
					indexTrickWinner = i;
				}
			}
			return indexTrickWinner;
		}
		
		//PikStick	
		if (Trick[0] < 20) {
			for (int i = 1; i < 4; i++) {
				if (Trick[i] > highestCard && Trick[i] < 20 && Trick[i] > 10) {
					highestCard = Trick[i];
					indexTrickWinner = i;
				}
			}
			return indexTrickWinner;
		}
		//Kreuzstick
		if (Trick[0] < 30) {
			for (int i = 1; i < 4; i++) {
				if (Trick[i] > highestCard && Trick[i] < 30 && Trick[i] > 20) {
					highestCard = Trick[i];
					indexTrickWinner = i;
				}
			}
			return indexTrickWinner;
		}
	}

	//Trumpfstick
	else {
		for (int i = 1; i < 4; i++) {
			if (Trick[i] > highestCard) {
				highestCard = Trick[i];
				indexTrickWinner = i;

			}
		}
		return indexTrickWinner;
	}
	
	return indexTrickWinner;
}

void GameLogic::CheckTrickSpecial(TArray<uint8> Trick) {
	// check if trick contains special points
}