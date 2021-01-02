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
int8 GameLogic::AddCardToTrick(uint8 MeshValue) {
	CurrentTrick.Add(CardGameValue[MeshValue]);
	TrickCardCount++;
	if (TrickCardCount == 4) {

		int8 trickwinner = CalculateTrickResult(CurrentTrick);
		LastTrick = CurrentTrick;
		UE_LOG(LogTemp, Warning, TEXT("Winner of the Trick: %i"), trickwinner)
		ResetTrick();
		return trickwinner;
	}
	return -1;
	
}


int8 GameLogic::CalculateTrickResult(TArray<uint8> Trick) {
	CheckTrickSpecial(Trick);

	uint8 highestCard = Trick[0];
	int8 indexTrickWinner = 0;
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
		
		//PikStich	
		if (Trick[0] < 20) {
			for (int i = 1; i < 4; i++) {
				if (Trick[i] > highestCard && Trick[i] < 20 && Trick[i] > 10) {
					highestCard = Trick[i];
					indexTrickWinner = i;
				}
			}
			return indexTrickWinner;
		}
		//Kreuzstich
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

	//Trumpfstich
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

int32 GameLogic::CountResult(TArray<uint8> cardArray) {
	int32 result = 0;
	uint8 value;
	for (auto card : cardArray) {
		if (card == 2 || card == 12 || card == 22 || card == 32) {
			value = 4;
		}
		else if (card == 4 || card == 14 || card == 24 || card == 34) {
			value = 11;
		}
		else if (card == 13 || card == 23 || card == 33 || card == 61) {
			value = 10;
		}
		else if (card >= 41 && card <= 44) {
			value = 2;
		}
		else if (card >= 51 && card <= 54) {
			value = 3;
		}
		else { value = 0; }

		result = result + value;
	}
	UE_LOG(LogTemp, Warning, TEXT("Result: %i"), result)
	return result;
}