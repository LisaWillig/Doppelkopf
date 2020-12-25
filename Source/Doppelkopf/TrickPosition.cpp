// Fill out your copyright notice in the Description page of Project Settings.

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

void ATrickPosition::SpawnCardAtTrick(int32 playerIndex, int32 cardValue) {
	//auto cardPositions = TrickMesh->GetAllSocketNames();
	auto pos = TrickMesh->GetSocketTransform(FName(FString::FromInt(playerIndex)));
	if (PlayingCardClass != nullptr) {
		auto card = GetWorld()->SpawnActor<APlayingCard>(PlayingCardClass, pos);
		FAttachmentTransformRules AttachmentRules = { EAttachmentRule::KeepWorld, false };
		card->AttachToActor(this, AttachmentRules, FName(FString::FromInt(playerIndex)));
		card->OnRep_SetCardValue();
	}
}