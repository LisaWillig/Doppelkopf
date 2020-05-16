// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayingCard.h"

// Sets default values
APlayingCard::APlayingCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	bAlwaysRelevant = true;
	SetReplicates(true);

}

// Called when the game starts or when spawned
void APlayingCard::BeginPlay()
{
	Super::BeginPlay();

	this->OnClicked.AddDynamic(this, &APlayingCard::OnCardClicked);
	
}

void APlayingCard::OnCardClicked(AActor* TouchedActor, FKey ButtonPressed) {
	UE_LOG(LogTemp, Warning, TEXT("I was clicked"))
}
void APlayingCard::SetCardValue(int32 meshValue) {
	SetCardFromtInt(meshValue);
	cardValue = meshValue;
}

/*
void APlayingCard::playThisCard() {
	
	//UE_LOG(LogTemp, Warning, TEXT("Card Played: %i"), cardValue)
	
}
*/
// Called every frame
void APlayingCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

