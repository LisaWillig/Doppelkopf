// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfPlayerState.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"

ADoppelkopfPlayerState::ADoppelkopfPlayerState() {
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
}	

void ADoppelkopfPlayerState::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

}

void ADoppelkopfPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    DOREPLIFETIME(ADoppelkopfPlayerState, myTurn);
}