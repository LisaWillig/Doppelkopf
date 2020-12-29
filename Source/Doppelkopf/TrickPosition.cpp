// Fill out your copyright notice in the Description page of Project Settings.

#include "DoppelkopfGameState.h"
#include "TrickPosition.h"

// Sets default values
ATrickPosition::ATrickPosition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	Root->SetIsReplicated(true);
	this->SetRootComponent(Root);

	TrickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrickMesh"));
	TrickMesh->SetupAttachment(Root);
	TrickMesh->SetVisibility(false);
	TrickMesh->SetIsReplicated(true);

}

// Called when the game starts or when spawned
void ATrickPosition::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrickPosition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrickPosition::CollectTrick() {
	cardCount = 0;
	UE_LOG(LogTemp, Warning, TEXT("Collect Cards"))
	TArray<AActor*> Cards;
	this->GetAttachedActors(Cards);
	for (auto card : Cards) {
		card->Destroy();
	}
}


void ATrickPosition::SpawnCardAtTrick(int32 playerIndex, int32 cardValue) {
	auto pos = TrickMesh->GetSocketTransform(FName(FString::FromInt(playerIndex)));
	// Scale cards up
	FVector scale = pos.GetScale3D();
	pos.SetScale3D(scale * 1.5);

	if (PlayingCardClass != nullptr) {
		auto card = GetWorld()->SpawnActor<APlayingCard>(PlayingCardClass, pos);
		FAttachmentTransformRules AttachmentRules = { EAttachmentRule::KeepWorld, false };
		card->AttachToActor(this, AttachmentRules, FName(FString::FromInt(playerIndex)));
		card->cardValue = cardValue;
		card->OnRep_SetCardValue();
		cardCount++;
	}
	auto gamestate = Cast<ADoppelkopfGameState>(GetWorld()->GetGameState());
	if (gamestate != nullptr) {
		gamestate->SetActivePlayer();
	}
	if (cardCount == 4) {
		// collect Trick
		GetWorldTimerManager().SetTimer(CollectTrickWaitHandle, this, &ATrickPosition::CollectTrick, 1.0f, false);
	}
}