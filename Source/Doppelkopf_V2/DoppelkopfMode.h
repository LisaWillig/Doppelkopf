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
		0, 1, 2, 3 , 4, 5, // Karo: A, 9, 10, J, Q K
		6, 7, 8, 9, 10, 11, // Kreuz
		12, 13, 14, 15, 16, 17, // Herz
		18, 19, 20, 21, 22, 23, // Pik
		0, 1, 2, 3 , 4, 5, // Karo: A, 9, 10, J, Q K
		6, 7, 8, 9, 10, 11, // Kreuz
		12, 13, 14, 15, 16, 17, // Herz
		18, 19, 20, 21, 22, 23,
	};

	int32 CurrentDeck[48] = {
		0, 1, 2, 3 , 4, 5, // Karo: A, 9, 10, J, Q K
		6, 7, 8, 9, 10, 11, // Kreuz
		12, 13, 14, 15, 16, 17, // Herz
		18, 19, 20, 21, 22, 23, // Pik
		0, 1, 2, 3 , 4, 5, // Karo: A, 9, 10, J, Q K
		6, 7, 8, 9, 10, 11, // Kreuz
		12, 13, 14, 15, 16, 17, // Herz
		18, 19, 20, 21, 22, 23,
	};
};
 