// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameLogic.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameMode.h"
#include "DoppelkopfPlayerController.h"
#include "DoppelkopfMode.generated.h"
 

UCLASS()
class DOPPELKOPF_API ADoppelkopfMode : public AGameMode
{
	GENERATED_BODY()

	virtual void PostLogin(APlayerController* NewPlayerController) override;
	virtual void StartPlay() override;
	virtual void StartMatch() override;

public:

	ADoppelkopfMode();
	void ShuffleCards();
	TArray<uint8> NewDeck;
	TArray<uint8> GiveCards();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> PlayerArray;

	FString StartPlayerController; 
	bool matchOver;
	int playerIndex = 0;
	void Tick(float DeltaTime);
	void DetermineStartPlayer();
	//UFUNCTION()
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:

	int askedForCards = 0;
	TArray<uint8> CardDeck = {
		0, 1, 2, 3 , 4, 5, // Karo: A, 9, 10, J, Q K
		6, 7, 8, 9, 10, 11, // Kreuz
		12, 13, 14, 15, 16, 17, // Herz
		18, 19, 20, 21, 22, 23, // Pik
		0, 1, 2, 3 , 4, 5, // Karo: A, 9, 10, J, Q K
		6, 7, 8, 9, 10, 11, // Kreuz
		12, 13, 14, 15, 16, 17, // Herz
		18, 19, 20, 21, 22, 23,
	};

	uint8 CurrentDeck[48] = {
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
 