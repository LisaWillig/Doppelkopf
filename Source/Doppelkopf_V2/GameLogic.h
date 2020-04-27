// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DOPPELKOPF_V2_API GameLogic
{
public:
	GameLogic();

	void AddCardToTrick(int32 MeshValue);
	~GameLogic();

private:

	TMap<int32, FString> Sonderpunkte; 

	void CalculateTrickResult(TArray<int32> CurrentTrick);
	void ResetTrick();
	int32 TrickCardCount = 0;
	TArray<int32> CurrentTrick;
	void CheckTrickSpecial(TArray<int32> Trick);

	// Mesh Value : Game value	
	TMap <int32, int32> CardGameValue = {

		// ~~~ Colors ~~~~

		// Heart Nine
		TPairInitializer<const int32&, const int32&>(13, 1),
		// Heart King
		TPairInitializer<const int32&, const int32&>(17, 2), 
		// Heart Ace
		TPairInitializer<const int32&, const int32&>(12, 4),

		// Spade Nine
		TPairInitializer<const int32&, const int32&>(19, 11),
		// Spade King
		TPairInitializer<const int32&, const int32&>(23, 12),
		// Spade 10
		TPairInitializer<const int32&, const int32&>(20, 13),
		// Spade Ace
		TPairInitializer<const int32&, const int32&>(18, 14),

		// Clubs Nine
		TPairInitializer<const int32&, const int32&>(7, 21),
		// Clubs King
		TPairInitializer<const int32&, const int32&>(11, 22),
		// Clubs Ten
		TPairInitializer<const int32&, const int32&>(8, 23),
		//Clubs Ace
		TPairInitializer<const int32&, const int32&>(6, 24),

		// ~~~ Trump ~~~~

		// Diamond Nine
		TPairInitializer<const int32&, const int32&>(1, 31),
		// Diamond King
		TPairInitializer<const int32&, const int32&>(5, 32),
		// Diamond Ten
		TPairInitializer<const int32&, const int32&>(2, 33),
		// Diamons Ace
		TPairInitializer<const int32&, const int32&>(0, 34),

		// Diamond Jack 
		TPairInitializer<const int32&, const int32&>(3, 41),
		// Heart Jack
		TPairInitializer<const int32&, const int32&>(15, 42),
		// Spades Jack
		TPairInitializer<const int32&, const int32&>(21, 43),
		// Clubs Jack
		TPairInitializer<const int32&, const int32&>(9, 43),

		// Diamond Queen
		TPairInitializer<const int32&, const int32&>(4, 51),
		// Heart Queen
		TPairInitializer<const int32&, const int32&>(16, 52),
		// Spades Queen
		TPairInitializer<const int32&, const int32&>(22, 53),
		// Clubs Queen
		TPairInitializer<const int32&, const int32&>(10, 54),

		// Heart Ten
		TPairInitializer<const int32&, const int32&>(14, 61),
	
	};
};
