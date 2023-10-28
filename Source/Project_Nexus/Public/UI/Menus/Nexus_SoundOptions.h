// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_SoundOptions.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_SoundOptions : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

	// Online Multiplayer
	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* OnlineButton;

	UPROPERTY(meta = (BindWidget))	
	class USlider* MasterVolumeSlider;

	UPROPERTY(meta = (BindWidget))	
	class USlider* BackgroundMusicSlider;

	UPROPERTY(meta = (BindWidget))	
	class USlider* SFXVolumeSlider;

	UPROPERTY(meta = (BindWidget))	
	class USlider* VoiceSlider;

	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* DefaultSoundButton;
};
