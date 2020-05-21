// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DoppelkopfPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_V2_API ADoppelkopfPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Replicated)
	bool myTurn = false;
	ADoppelkopfPlayerState();

};
