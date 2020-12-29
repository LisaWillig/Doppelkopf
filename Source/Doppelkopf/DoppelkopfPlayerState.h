// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DoppelkopfPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_API ADoppelkopfPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	TArray<uint8> myWonTricks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	bool myTurn = false;
	ADoppelkopfPlayerState();

	void ActivatePlayerControllersTurn();
	void DeactivatePlayerControllersTurn();
	void AddWonTrick(TArray<uint8> newTrick);

};
