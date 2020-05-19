// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayingCard.h"
#include "CardPlayer.generated.h"

UCLASS()
class DOPPELKOPF_V2_API ACardPlayer : public APawn
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

	//UFUNCTION(BlueprintCallable, Category = Card)
	//void PlayCard(int32 card);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetPlayerHand(UWorld* const World, TArray<int32>& MyHand);

	bool bCardsDealed = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void rotateOwnedCards();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, replicated, BlueprintReadWrite,Category = Card)
	TArray<APlayingCard*> PlayerCardArray;

	UPROPERTY(VisibleAnywhere, replicated)
	TArray<int32> CardValues;

	void PlayCard(AActor* Card);
	bool bStartGame;
	void SpawnCardHand(UWorld* const World, TArray<int> MyHand);
};
