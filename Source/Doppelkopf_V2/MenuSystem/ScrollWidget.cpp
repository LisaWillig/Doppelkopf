// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollWidget.h"
#include "MainMenu.h"
#include "Components/Button.h"

bool UScrollWidget::Initialize() {

	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(ServerNameButton != nullptr)) return false;
	ServerNameButton->OnClicked.AddDynamic(this, &UScrollWidget::ReturnIndex);

	return true;
}


void UScrollWidget::Setup(UMainMenu* Parent, uint32 Index) {
	ParentMenu = Parent;
	MyIndex = Index;
}

void UScrollWidget::ReturnIndex() {
	ParentMenu->SelectIndex(MyIndex);
}
