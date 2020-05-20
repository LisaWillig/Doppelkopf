// Fill out your copyright notice in the Description page of Project Settings.


#include "CardPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "DoppelkopfMode.h"
#include "Net/UnrealNetwork.h"
#include "GameFrameWork/GameState.h"
#include "Engine/EngineTypes.h"
#include "Engine.h"


ACardPlayer::ACardPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates =true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	Root->SetIsReplicated(true);
	this->SetRootComponent(Root);

	CardHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CardHand"));
	CardHand->SetupAttachment(Root);
	CardHand->SetVisibility(false);
	CardHand->SetIsReplicated(true);

	// Create a camera boom 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(CardHand);
	Camera->bUsePawnControlRotation = false; 
}

void ACardPlayer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ACardPlayer, PlayerCardArray,  COND_InitialOnly);
	DOREPLIFETIME(ACardPlayer, CardValues);
}


void ACardPlayer::BeginPlay()
{
	Super::BeginPlay();

	TArray<int32> MyHand;
	UWorld* const World = GetWorld();

	if (HasAuthority()) {

		//clear Arrays for each Player
		PlayerCardArray.Empty();
		CardValues.Empty();

		if (World != nullptr) {
			GetPlayerHand(World, MyHand);
			SpawnCardHand(World, MyHand);
		}
	}

}

void ACardPlayer::GetPlayerHand(UWorld* const World, TArray<int32>& MyHand)
{
	// get Player Hand randomized from GameMode
	ADoppelkopfMode* gamemode = Cast<ADoppelkopfMode>(UGameplayStatics::GetGameMode(World));
	if (gamemode != nullptr) {
		MyHand = gamemode->GiveCards();
	}
}


void ACardPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//rotateOwnedCards();
	if (IsLocallyControlled()) {
		TArray<AActor*> playersHand;
		GetAttachedActors(playersHand, true);
		for (auto card : playersHand) {
			Cast<APlayingCard>(card)->SwapBackFront();
		}
	}
	/*if (GEngine->GetNetMode(GetWorld()) == ENetMode::NM_Client) //code to only run on clients, will not run in single player / standalone
	{
		rotateOwnedCards();
	}*/

}

void ACardPlayer::rotateOwnedCards()
{
	TArray<AActor*> playersHand;
	GetAttachedActors(playersHand, true);
	for (auto card : playersHand) {
		FRotator rot = card->GetActorRotation();
		rot.Roll = 0;
		card->SetActorRotation(rot);
	}
}

void ACardPlayer::SpawnCardHand(UWorld* const World, TArray<int> MyHand) {
	int i = 0;
	auto cardPositions = CardHand->GetAllSocketNames();
	for (FName socket : cardPositions) {
		auto pos = CardHand->GetSocketTransform(socket);
		FQuat rot = pos.GetRotation();
		FRotator newRot = rot.Rotator();
		newRot.Roll = 180;
		pos.SetRotation(newRot.Quaternion());
		if (PlayingCardClass != nullptr) {
			auto card = World->SpawnActor<APlayingCard>(PlayingCardClass, pos);
			FAttachmentTransformRules AttachmentRules = { EAttachmentRule::KeepWorld, false };
			card->AttachToActor(this, AttachmentRules, socket);
			PlayerCardArray.Add(card);
			CardValues.Add(MyHand[i]);
			card->cardValue = MyHand[i];
			card->OnRep_SetCardValue();
		}
		i++;
	}
}
// Called to bind functionality to input
void ACardPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACardPlayer::PlayCard(AActor* Card) {
	if (HasAuthority()) {
		int intValue = Cast<APlayingCard>(Card)->cardValue;
		UWorld* World = GetWorld();
		if (World != nullptr) {
			auto gameMode = Cast<ADoppelkopfMode>(UGameplayStatics::GetGameMode(World));
			gameMode->Trick(intValue);
		}
		UE_LOG(LogTemp, Warning, TEXT("Card: %i"), intValue)
	}
	
}