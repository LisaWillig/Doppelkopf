// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfPlayerController.h"
#include "GameFramework/Pawn.h"
#include "DoppelkopfPlayerState.h"
#include "CardPlayer.h"

ADoppelkopfPlayerController::ADoppelkopfPlayerController() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	bEnableClickEvents = true;

	//FInputModeGameAndUI mode;
	//SetInputMode(mode);
}

void ADoppelkopfPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (myPlayerState == nullptr) {
		myPlayerState = Cast<ADoppelkopfPlayerState>(AController::PlayerState);
	}
	else {
		if (myPlayerState->myTurn == false) {
			FInputModeUIOnly mode;
			SetInputMode(mode);
		}
		else {
			FInputModeGameAndUI mode;
			SetInputMode(mode);
		}
	}
}

void ADoppelkopfPlayerController::SetupInputComponent() {

	Super::SetupInputComponent();
	InputComponent->BindAction("CardClicked", EInputEvent::IE_Released, this, &ADoppelkopfPlayerController::clickCard);
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
				UE_LOG(LogTemp, Warning, TEXT("I own it!"))
				Cast<ACardPlayer>(myPlayer)->PlayCard(MouseResult.GetActor());
			}
		}
	}
}