// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_ChampionSelection.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_ChampionSelection : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* ChampionOne;

	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* ChampionTwo;

	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* ChampionRandom;

	/*
	 * hier kann noch ne moegliche Hilfe angegeben werden die man navigiert und wie man den character selected bzw. Wie man zurück geht
	 */
	
	
};
