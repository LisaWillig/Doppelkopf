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

// Sets default values
ACardPlayer::ACardPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates =true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	Root->SetIsReplicated(true);
	this->SetRootComponent(Root);
	CardHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CardHand"));
	CardHand->SetupAttachment(Root);
	CardHand->SetVisibility(false);
	CardHand->SetIsReplicated(true);
	// Create a camera boom (pulls in towards the player if there is a collision)
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(CardHand);
	Camera->bUsePawnControlRotation = false; // Rotate the arm based on the controller
}

void ACardPlayer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(ACardPlayer, CardValues);
}

// Called when the game starts or when spawned
void ACardPlayer::BeginPlay()
{
	GiveCards = true;
	
	UWorld* const World = GetWorld();
	if (World != nullptr) {
		auto cardPositions = CardHand->GetAllSocketNames();
		for (FName socket : cardPositions) {
			auto pos = CardHand->GetSocketTransform(socket);
			if (PlayingCardClass != nullptr) {
				auto card = World->SpawnActor<APlayingCard>(PlayingCardClass, pos);
				FAttachmentTransformRules AttachmentRules = { EAttachmentRule::KeepWorld, false };
				card->AttachToActor(this, AttachmentRules, socket);
				PlayerCardArray.Add(card);
				card->SetReplicates(true);
			}
		}
	}
	
	if (GiveCards) {
		GivePlayerCards();
		SetCardMesh();
	}

	Super::BeginPlay();
}



// Called every frame
void ACardPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACardPlayer::GivePlayerCards() {
	TArray<int32> MyHand;

	UWorld* const World = GetWorld();
	if (World != nullptr) {
		ADoppelkopfMode* gamemode = Cast<ADoppelkopfMode>(UGameplayStatics::GetGameMode(World));
		if (gamemode != nullptr) {
			MyHand = gamemode->GiveCards();
			for (int card : MyHand) {
				CardValues.Add(card); //52: integer to change later, defines style of cards
			}
			GiveCards = false;
		}
	}
}


void ACardPlayer::SetCardMesh() {
	int i = 0;
	if (PlayerCardArray.Num() != 0) {
		for (auto card : PlayerCardArray) {
			//FRotator New = card->GetActorRotation();
			//New.Pitch += 180;
			//card->SetActorRotation(New);
			//UE_LOG(LogTemp, Warning, TEXT("Position of Card: %s"), *card->GetActorLocation().ToString())
			//card->SetCardFromtInt(CardValues[i]);
			card->SetCardValue(CardValues[i]);

			i++;
		}
	}
}
// Called to bind functionality to input
void ACardPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



