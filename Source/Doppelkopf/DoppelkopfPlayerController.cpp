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

void ADoppelkopfPlayerController::BeginPlay() {

	Super::BeginPlay();
}

void ADoppelkopfPlayerController::SetupInputComponent() {

	Super::SetupInputComponent();
	InputComponent->BindAction("CardClicked", EInputEvent::IE_Released, this, &ADoppelkopfPlayerController::clickCard);
}

void ADoppelkopfPlayerController::Server_AddCardToTrick_Implementation(int32 card) {
	auto gamestate = Cast<ADoppelkopfGameState>(GetWorld()->GetGameState());
	if (gamestate != nullptr) {
		gamestate->Trick(card);
	}
}

void ADoppelkopfPlayerController::clickCard() {
	if (myPlayerState->myTurn == false) {
		return;
	}
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

				Cast<ADoppelkopfPlayerState>(PlayerState)->myTurn = false;
			}
		}
	}
}