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

		CalculateTrickResult(CurrentTrick);
		ResetTrick();
	}
	
}


void GameLogic::CalculateTrickResult(TArray<int32> Trick) {
	CheckTrickSpecial(Trick);

	// Farbstich ohne Trumpf
	if (!Trick.ContainsByPredicate([](int32 item) {return item > 30;})) {
		int32 highestCard = Trick[0];
		UE_LOG(LogTemp, Warning, TEXT("Farbstich!"))
		// Herzstich
		if (Trick[0] < 10){
			for (int i = 1; i < 4; i++) {
				if (Trick[i] > highestCard && Trick[i] < 10) {
					highestCard = Trick[i];
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("Herzstich: %i"), highestCard)
			}
		
		//PikStick	
		else if (Trick[0] < 20) {
			for (int i = 1; i < 4; i++) {
				if (Trick[i] > highestCard && Trick[i] < 20 && Trick[i] > 10) {
					highestCard = Trick[i];
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("Pikstich: %i"), highestCard)
		}
		//Kreuzstick
		else if (Trick[0] < 30) {
			for (int i = 1; i < 4; i++) {
				if (Trick[i] > highestCard && Trick[i] < 30 && Trick[i] > 20) {
					highestCard = Trick[i];
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("Kreuzstich: %i"), highestCard)
		}
	}

	//Trumpfstick
	else {
		int32 highestCard = Trick[0];
		for (int i = 1; i < 4; i++) {
			if (Trick[i] > highestCard) {
				highestCard = Trick[i];

			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Trumpfstich: %i"), highestCard)
	}
	
	
	UE_LOG(LogTemp, Warning, TEXT("%i, %i, %i, %i"), Trick[0], Trick[1], Trick[2], Trick[3])
}

void GameLogic::CheckTrickSpecial(TArray<int32> Trick) {
	// check if trick contains special points
}