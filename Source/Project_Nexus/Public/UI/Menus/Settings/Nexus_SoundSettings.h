// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_SoundSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_SoundSettings : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	
	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_SliderSetting* MasterVolumeSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_SliderSetting* BackgroundMusicSetting;
	
	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_SliderSetting* SFXVolumeSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_SliderSetting* VoiceVolumeSetting;

	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* DefaultSoundButton;

	UFUNCTION()
	virtual void RestoreDefaultSettings() override;
};
