// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/LocalPlayer.h"
#include "PlayingCard.generated.h"

UCLASS()
class DOPPELKOPF_API APlayingCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayingCard();

	UFUNCTION(BlueprintImplementableEvent, Category = "Card")
	void SetCardFromtInt(int32 value);

	UFUNCTION(BlueprintImplementableEvent, Category = "Card")
	void SwapBackFront();

	//UFUNCTION(BlueprintCallable, Category = "Card")
	//void playThisCard();

	UFUNCTION()
	void OnRep_SetCardValue();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* CardMesh; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_SetCardValue)
	int32 cardValue;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCardClicked(AActor* TouchedActor, FKey ButtonPressed);

 
};
