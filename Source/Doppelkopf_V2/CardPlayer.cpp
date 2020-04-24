// Fill out your copyright notice in the Description page of Project Settings.


#include "CardPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "DoppelkopfMode.h"
#include "Net/UnrealNetwork.h"
#include "GameFrameWork/GameState.h"

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
	DOREPLIFETIME(ACardPlayer, PlayerCardArray);
	DOREPLIFETIME(ACardPlayer, CardValues);
}

// Called when the game starts or when spawned
void ACardPlayer::BeginPlay()
{
	GiveCards = true;
	
	if (GiveCards) {
		UWorld* const World = GetWorld();
		if (World != nullptr) {
			ADoppelkopfMode* gamemode = Cast<ADoppelkopfMode>(UGameplayStatics::GetGameMode(World));
			if (gamemode != nullptr) {
				TArray<int32> MyHand = gamemode->GiveCards();
				auto cardPositions = CardHand->GetAllSocketNames();
				int i = 0;
				for (FName socket : cardPositions) {
					auto pos = CardHand->GetSocketTransform(socket);
					if (PlayingCardClass != nullptr) {
						auto card = World->SpawnActor<APlayingCard>(PlayingCardClass, pos);
						
						card->SetCardFromtInt(MyHand[i] + 52);
						CardValues.Add(MyHand[i] + 52);
						card->SetReplicates(true);
						PlayerCardArray.Add(card);
					}
					i++;
				}
			}
			GiveCards = false;
		}
	}
	
	Super::BeginPlay();

}

void ACardPlayer::OnRep_ServerState() {
	PlayerCardArray;
}

// Called every frame
void ACardPlayer::Tick(float DeltaTime)
{
	if (IsLocallyControlled()) {
		int i = 0;
		if (PlayerCardArray.Num() != 0) {
			for (auto card : PlayerCardArray) {
				card->SetCardFromtInt(CardValues[i]);
				i++;
			}
		}
	}
	Super::Tick(DeltaTime);
	



}

// Called to bind functionality to input
void ACardPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

