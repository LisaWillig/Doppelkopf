// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/LocalPlayer.h"
#include "PlayingCard.generated.h"

UCLASS()
class DOPPELKOPF_API APlayingCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayingCard();

	UFUNCTION(BlueprintImplementableEvent, Category = "Card")
	void SetCardFromtInt(int32 value);

	UFUNCTION(BlueprintImplementableEvent, Category = "Card")
	void SwapBackFront();

	UFUNCTION(BlueprintImplementableEvent, Category = "Card")
	void CardDisable(bool bdisable);

	//UFUNCTION(BlueprintCallable, Category = "Card")
	//void playThisCard();

	UFUNCTION()
	void OnRep_SetCardValue();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* CardMesh; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshSocket* socket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_SetCardValue)
	uint8 cardValue;

	UPROPERTY(replicated)
	AActor* myPlayer;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	UFUNCTION()
	void OnCardHovered(AActor* TouchedActor);

	UFUNCTION()
	void OnCardUnHovered(AActor* TouchedActor);

	float HoverScale = 1.1; 
	float spawnZHeight = 0;
	bool bElevateHighlightedCards = true;
 
};
