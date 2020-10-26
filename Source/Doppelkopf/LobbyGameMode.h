// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoppelkopfGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_API ALobbyGameMode : public ADoppelkopfGameMode
{
	GENERATED_BODY()
	
public:

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	void StartSession();

private:

	FTimerHandle TimerHandle;
	uint32 NbOfPlayers = 0;

	class ULobbyMenu_Server* menu;
};
