// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_MainOptionsMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_MainOptionsMenu : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* GameOptionsButton;

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* SoundOptionsButton;

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* ControllerSetupButton;

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* DisplaySettingsButton;

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* GraphicsSettingButton;

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* CopyrightButton;

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* CreditsButton;
};
