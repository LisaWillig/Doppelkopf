// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Doppelkopf_V2GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_V2_API ALobbyGameMode : public ADoppelkopf_V2GameMode
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
