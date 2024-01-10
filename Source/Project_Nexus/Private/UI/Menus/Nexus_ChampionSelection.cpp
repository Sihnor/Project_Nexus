// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Nexus_ChampionSelection.h"

#include "UI/Base/Nexus_CommonButtonBase.h"

void UNexus_ChampionSelection::NativeConstruct()
{
	Super::NativeConstruct();

	this->EscapeButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_ChampionSelection::OnEscapeButton);
}

void UNexus_ChampionSelection::OnEscapeButton()
{
	this->DeactivateWidget();
}

void UNexus_ChampionSelection::QuitChampSelection()
{
	this->OnCanceledChampSelect.Broadcast();
}

void UNexus_ChampionSelection::StartGame()
{
	this->OnCompletedChampSelect.Broadcast();
}
