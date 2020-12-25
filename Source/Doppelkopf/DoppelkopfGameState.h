// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameLogic.h"
#include "TrickPosition.h"
#include "DoppelkopfGameState.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_API ADoppelkopfGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallAble)
	void Trick(int PlayedCard);

	ADoppelkopfGameState();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool bPlay = false;

	UPROPERTY(replicated)
	int32 ActivePlayerIndex = 0;

	UFUNCTION()
	void SetActivePlayer();

	GameLogic GameCalculation;

	/** Card Hand Mesh with attached Sockets for cards to spawn */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	ATrickPosition* TrickPos;
};
