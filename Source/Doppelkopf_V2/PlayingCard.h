// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayingCard.generated.h"

UCLASS()
class DOPPELKOPF_V2_API APlayingCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayingCard();

	UFUNCTION(BlueprintImplementableEvent, Category = "Card")
	void SetCardFromtInt(int32 cardValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};