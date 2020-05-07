// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DoppelkopfGameState.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_V2_API ADoppelkopfGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	ADoppelkopfGameState();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool bPlay = false;
	int ActivePlayerIndex;
};