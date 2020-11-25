// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayingCard.h"
#include "CardPlayer.generated.h"

UCLASS()
class DOPPELKOPF_API ACardPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACardPlayer();

	/** Camera looking at the cards */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	/** Card Hand Mesh with attached Sockets for cards to spawn */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CardHand;

	/** Root Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, Category = Card)
	TSubclassOf<APlayingCard> PlayingCardClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PlaySettings")
	bool bInverteHand = true;

	//UFUNCTION(BlueprintCallable, Category = Card)
	//void PlayCard(int32 card);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetPlayerHand(UWorld* const World);

	bool bTurnCards;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void rotateOwnedCards();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, replicated, BlueprintReadWrite,Category = Card)
	TArray<APlayingCard*> PlayerCardArray;

	UPROPERTY(VisibleAnywhere, replicated)
	TArray<uint8> CardValues;
	FTimerHandle AllCardsSpawnedTimer;
	void rescaleToWindowSize(FViewport* ViewPort, uint32 val);
	void MoveOwnCards();
	int32 PlayCard(AActor* Card);
	bool bStartGame;
	void SortPlayerHand(TArray<uint8>& MyHand);
	void SpawnCardHand(UWorld* const World, TArray<uint8> MyHand);

};
