// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DoppelkopfPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_V2_API ADoppelkopfPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ADoppelkopfPlayerController();
    virtual void Tick(float DeltaTime) override;

    class ADoppelkopfPlayerState* myPlayerState = nullptr;
    virtual void SetupInputComponent() override;
    void clickCard();

    UFUNCTION(Server, reliable)
	void Server_SetActivePlayer();

	UFUNCTION(Server, reliable)
	void Server_AddCardToTrick(int32 card);

    void SetInactive();
    void SetActive();

       
};
