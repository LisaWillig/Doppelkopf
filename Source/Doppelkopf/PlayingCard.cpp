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
	RootComponent = CardMesh;


}

// Called when the game starts or when spawned
void APlayingCard::BeginPlay()
{
	Super::BeginPlay();

	this->OnClicked.AddDynamic(this, &APlayingCard::OnCardClicked);	
	this->OnBeginCursorOver.AddDynamic(this, &APlayingCard::OnCardHovered);
	this->OnEndCursorOver.AddDynamic(this, &APlayingCard::OnCardUnHovered);
}

void APlayingCard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APlayingCard, cardValue);
}

void APlayingCard::OnCardHovered(AActor* TouchedActor) {
	if (bElevateHighlightedCards) {
		spawnZHeight = GetActorLocation().Z;
		SetActorScale3D(FVector(GetActorScale().X * HoverScale, GetActorScale().Y * HoverScale, 1));
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 10));
		CardDisable(true);
	}
	else {
		SetActorScale3D(FVector(GetActorScale().X * HoverScale* 1.1, GetActorScale().Y * HoverScale * 1.1, 1));
	}
}

void APlayingCard::OnCardUnHovered(AActor* TouchedActor){

	if (bElevateHighlightedCards) {
		SetActorScale3D(FVector(GetActorScale().X / HoverScale, GetActorScale().Y / HoverScale, 1));
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, spawnZHeight));
		CardDisable(false);
	}
	else {
		SetActorScale3D(FVector(GetActorScale().X / (1.1*HoverScale), GetActorScale().Y/(1.1 * HoverScale), 1));
	}
}

void APlayingCard::OnCardClicked(AActor* TouchedActor, FKey ButtonPressed) {
	GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("mesh %i"), cardValue));
}


void APlayingCard::OnRep_SetCardValue() {
	SetCardFromtInt(cardValue);
}


// Called every frame
void APlayingCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

