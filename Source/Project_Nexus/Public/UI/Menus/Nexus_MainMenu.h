// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_MainMenu.generated.h"


class UNexus_SettingsMenu;
class UNexus_ChampionSelection;

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLobbySelect);

UCLASS()
class PROJECT_NEXUS_API UNexus_MainMenu : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	// TODO: Ein Story Modus
		
	UPROPERTY(meta = (BindWidget))
	class USizeBox* PanelWidthSB;

	UPROPERTY(meta = (BindWidget))
	class UImage* SettingsImage;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ButtonBox;

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CommonButtonBase* OnlineButton;

	// Local Multiplayer
	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CommonButtonBase* OfflineButton;

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CommonButtonBase* SettingsButton;

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CommonButtonBase* GalleryButton;
	
	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_CommonButtonBase* QuitButton;
	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNexus_SettingsMenu> SettingMenuClass;
	TObjectPtr<UNexus_SettingsMenu> SettingsMenu;

	FOnLobbySelect OnChangeToLobby;
	
	UFUNCTION()
	void OpenOnlineMode();

	UFUNCTION()
	void OpenOfflineMode();

	UFUNCTION()
	void OpenSettingsMenu();

	UFUNCTION()
	void CloseSettingsMenu();

	UFUNCTION()
	void OpenGalleryMenu();

	UFUNCTION()
	void CloseGalleryMenu();

	UFUNCTION()
	void QuitGame();

	void OpenChampSelect();
	
};
