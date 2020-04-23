// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Engine/Engine.h"


void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterace) {
	this->MenuInterface = MenuInterace;
}

void UMenuWidget::Setup() {
	this->AddToViewport();
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(this->TakeWidget());

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;

}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) {
	RemoveMenu();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

void UMenuWidget::RemoveMenu() {
	RemoveFromViewport();
	auto* world = GetWorld();
	if (!ensure(world != nullptr))
		return;

	auto* playerController = world->GetFirstPlayerController();
	if (!ensure(playerController != nullptr))
		return;
	FInputModeGameOnly inputMode;
	playerController->SetInputMode(inputMode);
	playerController->bShowMouseCursor = false;
}

void UMenuWidget::RemoveServerMenu() {
	UE_LOG(LogTemp, Warning, TEXT("Remove from Viewport ..."))
	RemoveFromViewport();
	RemoveFromParent();
	auto* world = GetWorld();
	if (!ensure(world != nullptr))
		return;
	auto playerController = GetMainController(world);
	if (!ensure(playerController != nullptr))
		return; 
	FInputModeGameOnly inputMode;
	playerController->SetInputMode(inputMode);
	playerController->bShowMouseCursor = true;
}

APlayerController* UMenuWidget::GetMainController(const UObject* WorldContextObject)
{
	// Get world context (containing player controllers)
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Loop on player controllers
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			// Get player controller from iterator
			APlayerController* PlayerController = Iterator->Get();

			// Get local player if exist
			ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

			// If it's local and id is 0, it's the main controller
			if (LocalPlayer != nullptr && LocalPlayer->GetControllerId() == 0)
			{
				return PlayerController;
			}
		}
	}

	// Not found
	return nullptr;
}