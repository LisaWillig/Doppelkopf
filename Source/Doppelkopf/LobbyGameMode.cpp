// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "TimerManager.h"
#include "MenuSystem/LobbyMenu_Server.h"
#include "DoppelkopfGameInstance.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NbOfPlayers++;
	if (HasAuthority()) {
		auto GameInstance = Cast<UDoppelkopfGameInstance>(GetGameInstance());
		if (GameInstance != nullptr) {
			GameInstance->LoadLobbyMenu();
		}
	}
	
	//if (NbOfPlayers > 0) {
	//	GetWorldTimerManager().SetTimer(TimerHandle, this, &ALobbyGameMode::StartSession, 5.0f, false);
	//}
}

void ALobbyGameMode::StartSession() {

	UWorld* World = GetWorld();
	int32 HumanPlayers = GetNumPlayers();
	auto GameInstance = Cast<UDoppelkopfGameInstance>(GetGameInstance());
	if (GameInstance != nullptr) {
		GameInstance->RemoveLobbyMenu();
		GameInstance->StartSession();
		GameInstance->ConnectedPlayers = HumanPlayers;
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
