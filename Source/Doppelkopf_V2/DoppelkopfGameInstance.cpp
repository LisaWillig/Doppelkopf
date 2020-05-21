// Fill out your copyright notice in the Description page of Project Settings.


#include "DoppelkopfGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/MenuWidget.h"
#include "MenuSystem/LobbyMenu_Server.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

#include "Delegates/DelegateSignatureImpl.inl"
#include "Delegates/DelegateInstanceInterface.h"

const static FName SESSION_NAME = NAME_GameSession;
const static FName SERVERNAME_SETTING_KEY = TEXT("ServerName");

UDoppelkopfGameInstance::UDoppelkopfGameInstance() {

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr))return;
	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr))return;
	InGameMenuClass = InGameMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> LobbyMenuServerBPClass(TEXT("/Game/MenuSystem/WBP_LobbyServer"));
	if (!ensure(LobbyMenuServerBPClass.Class != nullptr))return;
	LobbyMenuServerClass = LobbyMenuServerBPClass.Class;
}

void UDoppelkopfGameInstance::Init() {
	Super::Init();

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Subsystem: %s"), *Subsystem->GetSubsystemName().ToString())
			SessionInterface = Subsystem->GetSessionInterface();
		
		if (SessionInterface.IsValid()) {
			
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UDoppelkopfGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UDoppelkopfGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UDoppelkopfGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UDoppelkopfGameInstance::OnJoinSessionComplete);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
	}
}

/*
ONLINE SESSION

Create Online Session & Join

*/
void UDoppelkopfGameInstance::OnCreateSessionComplete(FName SessionName, bool Success) {

	if (!Success) {
		UE_LOG(LogTemp, Warning, TEXT("No Session was created!"))
			return;
	}
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Level/TableLobby?listen");
}

void UDoppelkopfGameInstance::OnFindSessionsComplete(bool Success) {
	if (Success && SessionSearch.IsValid() && Menu != nullptr) {
		TArray<FServerData> ServerNames;
		for (const FOnlineSessionSearchResult result : SessionSearch->SearchResults) {

			FServerData Data;
			Data.NameId = result.GetSessionIdStr();
			Data.MaxPlayers = result.Session.SessionSettings.NumPublicConnections;
			Data.CurrentPlayers = result.Session.SessionSettings.NumPublicConnections - result.Session.NumOpenPublicConnections;
			Data.HostUsername = result.Session.OwningUserName;
			FString ServerUserName;
			if (result.Session.SessionSettings.Get(SERVERNAME_SETTING_KEY, ServerUserName)) {
				Data.Name = ServerUserName;
				UE_LOG(LogTemp, Warning, TEXT("Session: %s"), *ServerUserName)
			}
			else {
				Data.Name = Data.NameId;
				UE_LOG(LogTemp, Warning, TEXT("No Settings found"))
			}
			ServerNames.Add(Data);
		}
		Menu->SetServerList(ServerNames);
	}
}

void UDoppelkopfGameInstance::OnDestroySessionComplete(FName SessionName, bool Success) {
	if (!Success) {
		CreateSession();
	}
}

void UDoppelkopfGameInstance::Host(FText UserServerName) {
	ServerName = UserServerName;
	if (SessionInterface.IsValid()) {
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr) {
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else {
			CreateSession();
		}
	}
}

void UDoppelkopfGameInstance::UpdateServerList() {
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	if (SessionSearch.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Looking for session"))

			if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL") {
				SessionSearch->bIsLanQuery = true;
			}
			else {
				SessionSearch->bIsLanQuery = false;
			}
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UDoppelkopfGameInstance::CreateSession() {
	if (SessionInterface.IsValid()) {

		FOnlineSessionSettings Settings;

		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL") {
			Settings.bIsLANMatch = true;
		}
		else {
			Settings.bIsLANMatch = false;
		}
		Settings.NumPublicConnections = 5;
		Settings.bShouldAdvertise = true;
		Settings.bUsesPresence = true;
		if (ServerName.ToString() != "") {
			Settings.Set(SERVERNAME_SETTING_KEY, ServerName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		}

		SessionInterface->CreateSession(0, SESSION_NAME, Settings);
	}
}

void UDoppelkopfGameInstance::Join(uint32 Index) {

	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;
	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

void UDoppelkopfGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) {

	if (!SessionInterface.IsValid()) return;

	FString Info;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Info)) {
		UE_LOG(LogTemp, Warning, TEXT("Could Not Get Connect String."))
			return;
	};

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(Info, ETravelType::TRAVEL_Absolute);
}

void UDoppelkopfGameInstance::StartSession() {
	if (!SessionInterface.IsValid()) return;
	SessionInterface->StartSession(SESSION_NAME);
}


/*
MENU SYSTEM

Create & Load Menus in the game

*/

void UDoppelkopfGameInstance::LoadMainMenu() {
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/Level/MainMenu", ETravelType::TRAVEL_Absolute);
}

ULobbyMenu_Server* UDoppelkopfGameInstance::LoadLobbyMenu() {
	if (!ensure(LobbyMenuServerClass != nullptr))return nullptr;
	LobbyMenu = CreateWidget<ULobbyMenu_Server>(this, LobbyMenuServerClass);
	if (!ensure(LobbyMenu != nullptr))return nullptr;
	LobbyMenu->Setup();
	LobbyMenu->SetMenuInterface(this);
	return LobbyMenu;
}

// called from Blueprint for loading the widgets
void UDoppelkopfGameInstance::LoadMenu() {
	if (!ensure(MenuClass != nullptr))return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr))return;
	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UDoppelkopfGameInstance::RemoveLobbyMenu() {
	if (!ensure(LobbyMenu != nullptr))return;
	LobbyMenu->RemoveMenu();
}

void UDoppelkopfGameInstance::LoadInGameMenu() {
	if (!ensure(InGameMenuClass != nullptr))return;
	UInGameMenu* InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
	if (!ensure(InGameMenu != nullptr))return;
	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

/*
EXIT GAME

*/
void UDoppelkopfGameInstance::QuitGame() {
	auto* playerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(playerController != nullptr)) return;
	playerController->ConsoleCommand("quit");
}