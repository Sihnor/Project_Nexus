// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Nexus_CommonUserWidget.h"
#include "Nexus_LobbyBase.generated.h"

class UNexus_ChampionSelection;

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_LobbyBase : public UNexus_CommonUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	class UNexus_WidgetContainerStack* SelectionStack;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNexus_ChampionSelection> ChampionMenuClass;
	TObjectPtr<UNexus_ChampionSelection> ChampionMenu;

	UFUNCTION()
	void OpenChampSelection();
	
	UFUNCTION(BlueprintCallable)
	void CloseChampSelection();

	UFUNCTION()
	void StartGame();
};
