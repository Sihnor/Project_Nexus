// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_ChampionSelection.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompletedChampions);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCanceledChampSelect);

UCLASS()
class PROJECT_NEXUS_API UNexus_ChampionSelection : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CommonButtonBase* ChampionOne;

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CommonButtonBase* ChampionTwo;

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CommonButtonBase* ChampionRandom;

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CommonButtonBase* EscapeButton;

	UFUNCTION(BlueprintCallable)
	void OnEscapeButton();
	
	UFUNCTION(BlueprintCallable)
	void QuitChampSelection();

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CommonButtonBase* SelectButton;
	
	
	UFUNCTION(BlueprintCallable) void StartGame();

	FOnCompletedChampions OnCompletedChampSelect;
	FOnCanceledChampSelect OnCanceledChampSelect;

	/*
	 * hier kann noch ne moegliche Hilfe angegeben werden die man navigiert und wie man den character selected bzw. Wie man zurück geht
	 */
	
	
};
