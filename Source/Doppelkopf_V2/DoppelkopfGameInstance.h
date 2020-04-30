// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "DoppelkopfGameInstance.generated.h"
/**
 *
 */
UCLASS()
class DOPPELKOPF_V2_API UDoppelkopfGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UDoppelkopfGameInstance();
	virtual void Init() override;
	virtual void Host(FText UserServerName) override;
	virtual void Join(uint32 Index) override;

	class UMainMenu* Menu;
	class ULobbyMenu_Server* LobbyMenu;

	void CreateSession();

	UFUNCTION(BlueprintCallable)
	virtual ULobbyMenu_Server* LoadLobbyMenu() override;

	UFUNCTION(BlueprintCallable)
		void LoadMenu();

	UFUNCTION(BlueprintCallable)
		void LoadInGameMenu();

	UFUNCTION(BlueprintCallable)
		virtual void LoadMainMenu() override;

	UFUNCTION(BlueprintCallable)
		virtual void QuitGame() override;

	UFUNCTION(BlueprintCallable)
		virtual void UpdateServerList() override;

	void StartSession();
	void RemoveLobbyMenu();

	UPROPERTY(BlueprintReadOnly)
	int ConnectedPlayers = 3;

private:

	FText ServerName;

	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;
	TSubclassOf<class UUserWidget> LobbyMenuServerClass;

	class TSharedPtr<FOnlineSessionSearch> SessionSearch;
	IOnlineSessionPtr SessionInterface;
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

};
