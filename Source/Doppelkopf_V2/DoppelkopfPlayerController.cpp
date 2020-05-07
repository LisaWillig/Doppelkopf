// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfPlayerController.h"
#include "DoppelkopfPlayerState.h"

ADoppelkopfPlayerController::ADoppelkopfPlayerController() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
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