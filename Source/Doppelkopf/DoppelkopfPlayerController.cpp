// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfPlayerController.h"
#include "GameFramework/Pawn.h"
#include "DoppelkopfPlayerState.h"
#include "CardPlayer.h"
#include "DoppelkopfGameState.h"
#include "Engine.h"

ADoppelkopfPlayerController::ADoppelkopfPlayerController() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	bEnableClickEvents = true;

}

void ADoppelkopfPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (myPlayerState == nullptr) {
		myPlayerState = Cast<ADoppelkopfPlayerState>(AController::PlayerState);
	}
}

void ADoppelkopfPlayerController::SetInactive() {
	myPlayerState->myTurn = false;
	//FInputModeUIOnly mode;
	//SetInputMode(mode);
}

void ADoppelkopfPlayerController::SetActive() {
	myPlayerState->myTurn = true;
	//FInputModeGameAndUI mode;
	//SetInputMode(mode);
}

void ADoppelkopfPlayerController::SetupInputComponent() {

	Super::SetupInputComponent();
	InputComponent->BindAction("CardClicked", EInputEvent::IE_Released, this, &ADoppelkopfPlayerController::clickCard);
}

void ADoppelkopfPlayerController::Server_SetActivePlayer_Implementation() {
	SetInactive();
	auto gamestate = Cast<ADoppelkopfGameState>(GetWorld()->GetGameState());
	if (gamestate != nullptr) {
		gamestate->SetActivePlayer();
	}
}

void ADoppelkopfPlayerController::Server_AddCardToTrick_Implementation(int32 card) {
	auto gamestate = Cast<ADoppelkopfGameState>(GetWorld()->GetGameState());
	if (gamestate != nullptr) {
		gamestate->Trick(card);
	}
	UE_LOG(LogTemp, Warning, TEXT("Added Card"))
}

void ADoppelkopfPlayerController::clickCard() {
	APawn* myPlayer = GetPawn();
	if (myPlayer != nullptr) {
		TArray<AActor*> playersHand;
		myPlayer->GetAttachedActors(playersHand, true);
		FHitResult MouseResult;
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, MouseResult);
		if (MouseResult.bBlockingHit) {
			bool bFound = playersHand.Contains(MouseResult.GetActor());
			if (bFound) {
				int32 myCard = Cast<ACardPlayer>(myPlayer)->PlayCard(MouseResult.GetActor());
				if (myCard == -1) {
					return;
				}
				Server_AddCardToTrick(myCard);
				SetInactive();
				Server_SetActivePlayer();
			}
		}
	}
}