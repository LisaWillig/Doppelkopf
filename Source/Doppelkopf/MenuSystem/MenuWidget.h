// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
	void RemoveMenu();
	void SetMenuInterface(IMenuInterface* MenuInerface);
	void Setup();
	void RemoveServerMenu();
	APlayerController* GetMainController(const UObject* WorldContextObject);

protected:

	IMenuInterface* MenuInterface;
};
