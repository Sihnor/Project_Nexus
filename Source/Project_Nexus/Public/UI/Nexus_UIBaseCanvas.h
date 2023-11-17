// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Nexus_CommonUserWidget.h"
#include "Nexus_UIBaseCanvas.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_UIBaseCanvas : public UNexus_CommonUserWidget
{
public:
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNexus_MainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNexus_ChampionSelection> ChampionSelectionClass;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	class UCommonActivatableWidgetContainerBase* Stack;

	TObjectPtr<UNexus_MainMenu> MainMenu;
	TObjectPtr<UNexus_ChampionSelection> ChampionSelectionMenu;

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void CloseMainMenu();

	UFUNCTION()
	void OpenOfflineMenu();

	UFUNCTION()
	void CloseOfflineMenu();
	
	UFUNCTION()
	void QuitGame();
	
};
