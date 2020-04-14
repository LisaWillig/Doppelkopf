// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "Components/Button.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_V2_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:

	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CallMenuInGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UFUNCTION()
	void CancelInGame();
	UFUNCTION()
	void OpenMainMenu();
	UFUNCTION()
	void Quit();

};
