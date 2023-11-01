// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_MainMenu.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_NEXUS_API UNexus_MainMenu : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	//UPROPERTY(meta = (BindWidget))
	//class UNexus_CommonButtonBase* StoryButton;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* PanelWidthSB;

	UPROPERTY(meta = (BindWidget))
	class UImage* SettingsImage;

	UPROPERTY(meta = (BindWidget))
	class UBorder* MenuBorder;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ButtonBox;

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* OnlineButton;

	// Local Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* OfflineButton;

	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* GalleryButton;
	
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* QuitButton;
	
};
