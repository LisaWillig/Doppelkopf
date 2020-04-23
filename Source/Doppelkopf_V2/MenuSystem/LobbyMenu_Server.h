// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "LobbyMenu_Server.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_V2_API ULobbyMenu_Server : public UMenuWidget
{
	GENERATED_BODY()
	
protected:

	virtual bool Initialize() override;
private:

	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameButton;

	UFUNCTION()
	void Start();
};
