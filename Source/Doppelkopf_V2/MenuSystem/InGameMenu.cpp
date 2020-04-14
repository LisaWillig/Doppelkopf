// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "MainMenu.h"
#include "../DoppelkopfGameInstance.h"

bool UInGameMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(CancelMenuButton != nullptr)) return false;
	CancelMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelInGame);

	if (!ensure(CallMenuInGameButton != nullptr)) return false;
	CallMenuInGameButton->OnClicked.AddDynamic(this, &UInGameMenu::OpenMainMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::Quit);

	return true;
}

void UInGameMenu::OpenMainMenu() {
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->LoadMainMenu();
}

void UInGameMenu::Quit() {
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->QuitGame();
}

void UInGameMenu::CancelInGame() {
	auto* playerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(playerController != nullptr)) return;
	this->RemoveFromViewport();
	FInputModeGameOnly inputMode;
	playerController->SetInputMode(inputMode);
	playerController->bShowMouseCursor = false;
}