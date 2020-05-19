// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayingCard.h"
#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"

// Sets default values
APlayingCard::APlayingCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	
	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayingCardMesh"));
	CardMesh->SetIsReplicated(true);
	RootComponent = CardMesh;
}

// Called when the game starts or when spawned
void APlayingCard::BeginPlay()
{
	Super::BeginPlay();

	this->OnClicked.AddDynamic(this, &APlayingCard::OnCardClicked);

	
	
}

void APlayingCard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APlayingCard, cardValue);
	DOREPLIFETIME(APlayingCard, CardMesh);
}


void APlayingCard::OnCardClicked(AActor* TouchedActor, FKey ButtonPressed) {
	//GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("mesh %i"), cardValue));
}

void APlayingCard::OnRep_SetCardValue() {
	SetCardFromtInt(cardValue);
}


// Called every frame
void APlayingCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

