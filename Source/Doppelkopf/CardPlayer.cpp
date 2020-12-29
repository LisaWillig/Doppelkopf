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
#include "GameLogic.h"
#include "UnrealClient.h"
#include "GameFramework/PlayerController.h"
#include "DoppelkopfPlayerState.h"
#include "DoppelkopfGameState.h"

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

	GEngine->GameViewport->Viewport->ViewportResizedEvent.AddUObject(this, &ACardPlayer::rescaleToWindowSize);
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

	
	UWorld* const World = GetWorld();

	if (HasAuthority()) {

		//clear Arrays for each Player
		PlayerCardArray.Empty();
		CardValues.Empty();

		if (World != nullptr) {
			GetPlayerHand(World);
			SpawnCardHand(World, CardValues);
		}
	}
	//after begin play (eg. all cards are dealed)
	if (IsLocallyControlled()) {
		GetWorld()->GetTimerManager().SetTimer(AllCardsSpawnedTimer, this, &ACardPlayer::MoveOwnCards, 1.0f, false);
	}

}

void ACardPlayer::rescaleToWindowSize(FViewport* ViewPort, uint32 val) {
	if (!bStartGame) { return; }
	if (!OriginalCardPositions.IsValidIndex(0)) { return; }
	TArray<AActor*> playersHand;
	GetAttachedActors(playersHand, true);
	uint8 NbCurrentCards = playersHand.Num();
	int32 ResolutionX;
	int32 ResolutionY;
	APlayerController* playerController = Cast<APlayerController>(GetController());
	playerController->GetViewportSize(ResolutionX, ResolutionY);
	this->GetActorLocation();

	int32 ScreenThird = ResolutionX / 3;
	int32 totalLengthCard = ScreenThird * 2;
	int32 stepEachCard = totalLengthCard / 12;

	TArray<FVector> CardOffsetPositions;
	CardOffsetPositions.Init(FVector(0, 0, 0), 12);

	FVector2D ScreenPositionLeft(ScreenThird, 0);
	FVector WorldPositionLeft;
	FVector WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld
	(
		playerController,
		ScreenPositionLeft,
		WorldPositionLeft,
		WorldDirection
	);

	FVector2D ScreenPositionRight(ScreenThird * 2, 0);
	FVector WorldPositionRight;
	UGameplayStatics::DeprojectScreenToWorld
	(
		playerController,
		ScreenPositionRight,
		WorldPositionRight,
		WorldDirection
	);

	for (int i = 0; i < 6; i++) {
		CardOffsetPositions[i] = FVector(-WorldPositionLeft.X + i * stepEachCard, 0, i * 0.02);
		CardOffsetPositions[11 - i] = FVector(WorldPositionRight.X - (11 - i) * stepEachCard, 0, i * 0.02);
	}
	int i = 0;
	for (int j = 0; j < playersHand.Num(); j++) {
		FVector currentPos = Cast<APlayingCard>(playersHand[j])->GetActorLocation();
		//card->SetActorLocation(currentPos + );
		//card->SetPivotOffset(CardOffsetPositions[i]);
		//card->AddActorLocalOffset(CardOffsetPositions[i]);
		playersHand[j]->SetActorLocation(OriginalCardPositions[j] + CardOffsetPositions[i]);
		i++;
	}
}
void ACardPlayer::GetPlayerHand(UWorld* const World)
{
	// get Player Hand randomized from GameMode
	ADoppelkopfMode* gamemode = Cast<ADoppelkopfMode>(UGameplayStatics::GetGameMode(World));
	GameLogic MyGame = GameLogic();
	TArray<uint8> MyHand;
	if (gamemode != nullptr) {
		MyHand = gamemode->GiveCards();
	}
	for (auto card : MyHand){
		CardValues.Add(MyGame.CardGameValue[card]);
	}
	SortPlayerHand(CardValues);
}

void ACardPlayer::SortPlayerHand(TArray<uint8>& Hand) {
	Hand.Sort();
}

void ACardPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACardPlayer::rotateOwnedCards()
{
		TArray<AActor*> playersHand;
		GetAttachedActors(playersHand, true);

		for (auto card : playersHand) {
			Cast<APlayingCard>(card)->SwapBackFront();
			Cast<APlayingCard>(card)->SetActorScale3D(FVector(2, 2, 2));
		}
}

void ACardPlayer::MoveOwnCards()
{
	if (!bStartGame) {
		rotateOwnedCards();
		bStartGame = true;
	}
	APlayerController* playerController = Cast<APlayerController>(GetController());
	FViewport* port = GEngine->GameViewport->Viewport;
	rescaleToWindowSize(port, 0);	


}


void ACardPlayer::SpawnCardHand(UWorld* const World, TArray<uint8> MyHand) {
	int i = 0;
	GameLogic MyGame = GameLogic();
	auto cardPositions = CardHand->GetAllSocketNames();
	if (bInverteHand) {
		cardPositions.Sort([](const FName& A, const FName& B) {
			return A > B;
			});
	}
	else {
		cardPositions.Sort();
	}
	
	//spawn card hand
	for (FName socket : cardPositions) {

		// get socket transform 
		auto pos = CardHand->GetSocketTransform(socket);

		// rotate cards to show their back side
		FQuat rot = pos.GetRotation();
		FRotator newRot = rot.Rotator();
		newRot.Roll = 180;
		pos.SetRotation(newRot.Quaternion());

		// Scale cards from other players down 
		FVector scale = pos.GetScale3D();
		pos.SetScale3D(scale * 0.5);


		if (PlayingCardClass != nullptr) {
			auto card = World->SpawnActor<APlayingCard>(PlayingCardClass, pos);
			FAttachmentTransformRules AttachmentRules = { EAttachmentRule::KeepWorld, false }; 
			card->AttachToActor(this, AttachmentRules, socket);
			PlayerCardArray.Add(card);
			OriginalCardPositions.Add(card->GetActorLocation());
			card->cardValue = *MyGame.CardGameValue.FindKey(MyHand[i]);
			card->OnRep_SetCardValue();
			card->myPlayer = this;
		}
		i++;
	}
}
// Called to bind functionality to input
void ACardPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int32 ACardPlayer::PlayCard(AActor* Card) {
	auto test = Cast<ADoppelkopfPlayerState>(GetPlayerState());
	/*if (test->myTurn == false) {
		return -1;
	}*/

	APlayingCard* playingCard = Cast<APlayingCard>(Card);
	GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("mesh %i, player: %s"), playingCard->cardValue));
	UE_LOG(LogTemp, Warning, TEXT("Socket Name of Played Card: %s"), *playingCard->GetAttachParentSocketName().ToString());
	int32 emptySocket = FCString::Atoi(*Card->GetAttachParentSocketName().ToString());
	auto cardPositions = CardHand->GetAllSocketNames();
	Card->Destroy(true);
	
	PlayerCardArray.Remove(Cast<APlayingCard>(Card));
	for (auto card : PlayerCardArray) {
		if (emptySocket < 7) {
			if (FCString::Atoi(*card->GetAttachParentSocketName().ToString()) < emptySocket) {
				FName newSocket = FName("0" + FString::FromInt(FCString::Atoi(*card->GetAttachParentSocketName().ToString()) + 1));
				FAttachmentTransformRules AttachmentRules = { EAttachmentRule::KeepWorld, false };
				card->AttachToActor(this, AttachmentRules, newSocket);
				auto pos = CardHand->GetSocketTransform(newSocket);
				card->SetActorLocation(pos.GetLocation());
				card->SetActorRotation(pos.GetRotation());
			}
		}
		else {
			int32 currentSocket = FCString::Atoi(*card->GetAttachParentSocketName().ToString());
			if (currentSocket > emptySocket) {
				if (currentSocket > 10) {
					FName newSocket = FName(FString::FromInt(FCString::Atoi(*card->GetAttachParentSocketName().ToString()) - 1));
					FAttachmentTransformRules AttachmentRules = { EAttachmentRule::KeepWorld, false };
					card->AttachToActor(this, AttachmentRules, newSocket);
					auto pos = CardHand->GetSocketTransform(newSocket);
					card->SetActorLocation(pos.GetLocation());
					card->SetActorRotation(pos.GetRotation());
				}
				else {
					FName newSocket = FName("0" + FString::FromInt(FCString::Atoi(*card->GetAttachParentSocketName().ToString()) - 1));
					FAttachmentTransformRules AttachmentRules = { EAttachmentRule::KeepWorld, false };
					card->AttachToActor(this, AttachmentRules, newSocket);
					auto pos = CardHand->GetSocketTransform(newSocket);
					card->SetActorLocation(pos.GetLocation());
					card->SetActorRotation(pos.GetRotation());
				}
			}
		}
	}

	return Cast<APlayingCard>(Card)->cardValue;
	/*auto gamestate = Cast<ADoppelkopfGameState>(GetWorld()->GetGameState());
	if (gamestate != nullptr) {
		gamestate->Trick(cardToPlay);
	}*/
}
