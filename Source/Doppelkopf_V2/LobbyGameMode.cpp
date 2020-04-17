// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "TimerManager.h"
#include "DoppelkopfGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NbOfPlayers++;
	if (NbOfPlayers > 0) {
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ALobbyGameMode::StartSession, 5.0f, false);
	}
}

void ALobbyGameMode::StartSession() {
	UWorld* World = GetWorld();
	auto GameInstance = Cast<UDoppelkopfGameInstance>(GetGameInstance());
	if (GameInstance != nullptr) {
		GameInstance->StartSession();
		GameInstance->ConnectedPlayers = NbOfPlayers;
	}
	if (!ensure(World != nullptr))return;
	bUseSeamlessTravel = true;

	World->ServerTravel("/Game/Level/Table?listen");
}
void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	NbOfPlayers--;
}
