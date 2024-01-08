// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Nexus_LobbyBase.h"

#include "Kismet/GameplayStatics.h"
#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Base/Nexus_WidgetContainerStack.h"
#include "UI/Menus/Nexus_ChampionSelection.h"

void UNexus_LobbyBase::NativeConstruct()
{
	Super::NativeConstruct();

	this->OpenChampSelection();
}

void UNexus_LobbyBase::OpenChampSelection()
{
	this->ChampionMenu = this->SelectionStack->AddWidget<UNexus_ChampionSelection>(this->ChampionMenuClass);
	this->ChampionMenu->COMPLETED->OnButtonClicked.AddUniqueDynamic(this, &UNexus_LobbyBase::StartGame);
	this->ChampionMenu->CANCELED->OnButtonClicked.AddUniqueDynamic(this, &UNexus_LobbyBase::CloseChampSelection);
	this->ChampionMenu->SetIsFocusable(true);
}

void UNexus_LobbyBase::CloseChampSelection()
{
	this->SelectionStack->ClearWidgets();

	FString MapName = "UserInterfaceLevel";

	UGameplayStatics::OpenLevel(this, *MapName, true);
}

void UNexus_LobbyBase::StartGame()
{
	this->SelectionStack->ClearWidgets();

	FString MapName = "GameplayLevelTest";

	UGameplayStatics::OpenLevel(this, *MapName, true);
}