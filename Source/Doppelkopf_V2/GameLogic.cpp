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
void GameLogic::AddCardToTrick(int32 MeshValue) {
	CurrentTrick.Add(CardGameValue[MeshValue]);
	TrickCardCount++;
	if (TrickCardCount == 4) {

		int32 trickwinner = CalculateTrickResult(CurrentTrick);
		UE_LOG(LogTemp, Warning, TEXT("Winner of the Trick: %i"), trickwinner)
		ResetTrick();
	}
	
}


int32 GameLogic::CalculateTrickResult(TArray<int32> Trick) {
	CheckTrickSpecial(Trick);

	int32 highestCard = Trick[0];
	int32 indexTrickWinner = 0;
	// Farbstich ohne Trumpf
	if (!Trick.ContainsByPredicate([](int32 item) {return item > 30;})) {
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

void GameLogic::CheckTrickSpecial(TArray<int32> Trick) {
	// check if trick contains special points
}