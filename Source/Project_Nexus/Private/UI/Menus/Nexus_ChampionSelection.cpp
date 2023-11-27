// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Nexus_ChampionSelection.h"

#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Base/Nexus_WidgetContainerStack.h"

void UNexus_ChampionSelection::NativeConstruct()
{
	Super::NativeConstruct();

	this->COMPLETED->OnButtonClicked.AddUniqueDynamic(this, &UNexus_ChampionSelection::COMPLETEDEVENT);
	this->CANCELED->OnButtonClicked.AddUniqueDynamic(this, &UNexus_ChampionSelection::CANCELEDEVENT);
}

void UNexus_ChampionSelection::COMPLETEDEVENT()
{
	this->OnCompletedChampions.Broadcast();
}

void UNexus_ChampionSelection::CANCELEDEVENT()
{
	this->OnCanceledChampSelect.Broadcast();
}

