// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Doppelkopf_V2GameMode.h"

#include "DoppelkopfMode.generated.h"
 

UCLASS()
class DOPPELKOPF_V2_API ADoppelkopfMode : public ADoppelkopf_V2GameMode
{
	GENERATED_BODY()

	virtual void PostLogin(APlayerController* NewPlayerController) override;
	virtual void StartPlay() override;

public:

	void ShuffleCards();
	TArray<int32> NewDeck;
	TArray<int32> GiveCards();

private:

	int askedForCards = 0;
	TArray<int32> CardDeck = { 
		0, 8, 9, 10 , 11, 12, // Karo: A, 9, 10, J, Q K
		13, 21, 22, 23, 24, 25, // Kreuz
		26, 34, 35, 36, 37, 38, // Herz
		39, 47, 48, 49, 50, 51, // Pik
		0, 8, 9, 10 , 11, 12,
		13, 21, 22, 23, 24, 25,
		26, 34, 35, 36, 37, 38,
		39, 47, 48, 49, 50, 51,
	};

	int32 CurrentDeck[48] = {
		0, 8, 9, 10 , 11, 12, // Karo: A, 9, 10, J, Q K
		13, 21, 22, 23, 24, 25, // Kreuz
		26, 34, 35, 36, 37, 38, // Herz
		39, 47, 48, 49, 50, 51, // Pik
		0, 8, 9, 10 , 11, 12,
		13, 21, 22, 23, 24, 25,
		26, 34, 35, 36, 37, 38,
		39, 47, 48, 49, 50, 51,
	};
};
 