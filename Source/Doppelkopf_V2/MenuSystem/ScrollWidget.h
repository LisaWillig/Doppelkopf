// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScrollWidget.generated.h"

/**
 * 
 */
UCLASS()
class DOPPELKOPF_V2_API UScrollWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual bool Initialize() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HostID;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentPlayer;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxPlayer;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ServerNameButton;

	void Setup(class UMainMenu* Parent, uint32 Index);

	UFUNCTION()
	void ReturnIndex();

	uint32 MyIndex; 

	UPROPERTY()
	class UMainMenu* ParentMenu; 
};
