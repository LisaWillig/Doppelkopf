// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DOPPELKOPF_API GameLogic
{
public:
	GameLogic();

	int8 AddCardToTrick(uint8 MeshValue);
	~GameLogic();

public:
	// Mesh Value : Game value	
	TMap <uint8, uint8> CardGameValue = {

		// ~~~ Colors ~~~~

		// Heart Nine
		TPairInitializer<const uint8&, const uint8&>(13, 1),
		// Heart King
		TPairInitializer<const uint8&, const uint8&>(17, 2),
		// Heart Ace
		TPairInitializer<const uint8&, const uint8&>(12, 4),

		// Spade Nine
		TPairInitializer<const uint8&, const uint8&>(19, 11),
		// Spade King
		TPairInitializer<const uint8&, const uint8&>(23, 12),
		// Spade 10
		TPairInitializer<const uint8&, const uint8&>(20, 13),
		// Spade Ace
		TPairInitializer<const uint8&, const uint8&>(18, 14),

		// Clubs Nine
		TPairInitializer<const uint8&, const uint8&>(7, 21),
		// Clubs King
		TPairInitializer<const uint8&, const uint8&>(11, 22),
		// Clubs Ten
		TPairInitializer<const uint8&, const uint8&>(8, 23),
		//Clubs Ace
		TPairInitializer<const uint8&, const uint8&>(6, 24),

		// ~~~ Trump ~~~~

		// Diamond Nine
		TPairInitializer<const uint8&, const uint8&>(1, 31),
		// Diamond King
		TPairInitializer<const uint8&, const uint8&>(5, 32),
		// Diamond Ten
		TPairInitializer<const uint8&, const uint8&>(2, 33),
		// Diamons Ace
		TPairInitializer<const uint8&, const uint8&>(0, 34),

		// Diamond Jack 
		TPairInitializer<const uint8&, const uint8&>(3, 41),
		// Heart Jack
		TPairInitializer<const uint8&, const uint8&>(15, 42),
		// Spades Jack
		TPairInitializer<const uint8&, const uint8&>(21, 43),
		// Clubs Jack
		TPairInitializer<const uint8&, const uint8&>(9, 43),

		// Diamond Queen
		TPairInitializer<const uint8&, const uint8&>(4, 51),
		// Heart Queen
		TPairInitializer<const uint8&, const uint8&>(16, 52),
		// Spades Queen
		TPairInitializer<const uint8&, const uint8&>(22, 53),
		// Clubs Queen
		TPairInitializer<const uint8&, const uint8&>(10, 54),

		// Heart Ten
		TPairInitializer<const uint8&, const uint8&>(14, 61),

	};

private:

	TMap<uint8, FString> Sonderpunkte; 

	int8 CalculateTrickResult(TArray<uint8> CurrentTrick);
	void ResetTrick();
	int8 TrickCardCount = -1;
	TArray<uint8> CurrentTrick;
	void CheckTrickSpecial(TArray<uint8> Trick);


};
