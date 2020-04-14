// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"

#include "ScrollWidget.h"

UMainMenu::UMainMenu() {
	ConstructorHelpers::FClassFinder<UUserWidget> ServerScrollBP(TEXT("/Game/MenuSystem/WBP_ScrollBox"));
	if (!ensure(ServerScrollBP.Class != nullptr))return;
	ServerScrollClass = ServerScrollBP.Class;
}


bool UMainMenu::Initialize() {
	bool Success = Super::Initialize();

	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::Host);

	if (!ensure(JoinMenuButton != nullptr)) return false;
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(HostMenuButton != nullptr)) return false;
	HostMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);

	if (!ensure(CancelHostButton != nullptr)) return false;
	CancelHostButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::Join);

	if (!ensure(QuitGameButton != nullptr)) return false;
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);

	return true;
}

void UMainMenu::Quit() {
	if (MenuInterface == nullptr) return;
	MenuInterface->QuitGame();
}

void UMainMenu::Host() {
	if (!ensure(ServerNameLine != nullptr))return;
	if (MenuInterface == nullptr) return; 
	FText UserServerName = ServerNameLine->GetText();
	MenuInterface->Host(UserServerName);
}

void UMainMenu::SetServerList(TArray<FServerData> ServerNames) {
	if (!ensure(ServerScrollClass != nullptr))return;
	ServerList->ClearChildren();
	uint32 i = 0;
	for (const FServerData& ServerName : ServerNames) {
		UScrollWidget* Row = CreateWidget<UScrollWidget>(this, ServerScrollClass);
		if (!ensure(Row != nullptr))return;
		Row->ServerName->SetText(FText::FromString(ServerName.Name));
		Row->HostID->SetText(FText::FromString(ServerName.HostUsername));
		Row->CurrentPlayer->SetText(FText::AsNumber(ServerName.CurrentPlayers));
		Row->MaxPlayer->SetText(FText::AsNumber(ServerName.MaxPlayers));
		Row->Setup(this, i);
		++i;
		ServerList->AddChild(Row);
	}
}

void UMainMenu::SelectIndex(uint32 Index) {
	SelectedIndex = Index;
}

void UMainMenu::Join() {
	
	if (SelectedIndex.IsSet() && MenuInterface != nullptr) {
		MenuInterface->Join(SelectedIndex.GetValue());
		UE_LOG(LogTemp, Warning, TEXT("Selected Index %d"), SelectedIndex.GetValue())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Session Chosen"))
	}
}

void UMainMenu::OpenJoinMenu() {
	if (!ensure(MenuSwitch != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitch->SetActiveWidget(JoinMenu);
	if (MenuInterface != nullptr) {
		MenuInterface->UpdateServerList();
	}
}

void UMainMenu::OpenHostMenu() {
	if (!ensure(MenuSwitch != nullptr)) return;
	if (!ensure(HostMenu != nullptr)) return;
	MenuSwitch->SetActiveWidget(HostMenu);
}

void UMainMenu::OpenMainMenu() {
	if (!ensure(MenuSwitch != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitch->SetActiveWidget(MainMenu);
}