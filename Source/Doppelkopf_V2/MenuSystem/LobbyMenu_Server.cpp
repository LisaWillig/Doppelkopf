// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMenu_Server.h"
#include "../LobbyGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool ULobbyMenu_Server::Initialize() {
	bool Success = Super::Initialize();

	if (!ensure(StartGameButton != nullptr)) return false;
	StartGameButton->OnClicked.AddDynamic(this, &ULobbyMenu_Server::Start);

	return true;
}

void ULobbyMenu_Server::Start() {
	
	auto GameMode = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode != nullptr) {
		GameMode->StartSession();
		
	}
}

