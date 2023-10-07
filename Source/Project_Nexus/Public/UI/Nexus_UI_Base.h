// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UObject/Interface.h"
#include "UI/Base/Initializable.h"
#include "Nexus_UI_Base.generated.h"


UCLASS()
class PROJECT_NEXUS_API UNexus_UI_Base : public UCommonUserWidget, public IInitializable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void MyInitialize() override;

	UPROPERTY(meta=(BindWidget))
	class UNexus_CommonActiveWidgetStack* Stack;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNexus_MainMenuHUD> MainMenuHUDClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNexus_CharacterSelectionHUD> CharacterSelectionClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNexus_GameOverlayHUD> GameOverlayClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNexus_PauseMenuHUD> PauseOverlayClass;


private:
	UPROPERTY()
	UNexus_MainMenuHUD* MainMenuHUD;

	UPROPERTY()
	UNexus_CharacterSelectionHUD* CharacterSelection;

	UPROPERTY()
	UNexus_GameOverlayHUD* GameHUD;

	UFUNCTION()
	void OpenMainMenu();
	UFUNCTION()
	void CloseMainMenu();

	UFUNCTION()
	void OpenOnlineMenu();
	UFUNCTION()
	void CloseOnlineMenu();

	UFUNCTION()
	void OpenOfflineMenu();
	UFUNCTION()
	void CloseOfflineMenu();

	UFUNCTION()
	void OpenGalleryMenu();
	UFUNCTION()
	void CloseGalleryMenu();

	UFUNCTION()
	void OpenOptionsMenu();
	UFUNCTION()
	void CloseOptionsMenu();
	
	UFUNCTION()
	void OpenCharacterSelection();
	UFUNCTION()
	void CloseCharacterSelection();

	UFUNCTION()
	void OpenGameOverlay();
	UFUNCTION()
	void CloseGameOverlay();

	UFUNCTION()
	void QuitGame();
};


