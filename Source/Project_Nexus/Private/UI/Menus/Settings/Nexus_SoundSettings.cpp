// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Settings/Nexus_SoundSettings.h"

#include "Components/Slider.h"
#include "GameInstances/Nexus_GameInstance.h"
#include "Subsystems/Nexus_SettingsSubsystem.h"
#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Base/Setting/Nexus_SliderSetting.h"

void UNexus_SoundSettings::NativeConstruct()
{
	Super::NativeConstruct();

	this->DefaultSoundButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_SoundSettings::RestoreDefaultSettings);
}

void UNexus_SoundSettings::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
	{
		if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
		{
			this->MasterVolumeSetting->ValueSlider->SetValue(SettingsSubsystem->GetMasterVolumeSetting());
			this->BackgroundMusicSetting->ValueSlider->SetValue(SettingsSubsystem->GetBackgroundMusicSetting());
			this->SFXVolumeSetting->ValueSlider->SetValue(SettingsSubsystem->GetSFXVolumeSetting());
			this->VoiceVolumeSetting->ValueSlider->SetValue(SettingsSubsystem->GetVoiceVolumeSetting());
		}
	}
}

void UNexus_SoundSettings::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	
	if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
	{
		if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
		{
			SettingsSubsystem->SetMasterVolumeSetting(static_cast<int32>(this->MasterVolumeSetting->ValueSlider->GetValue()));
			SettingsSubsystem->SetBackgroundMusicSetting(static_cast<int32>(this->BackgroundMusicSetting->ValueSlider->GetValue()));
			SettingsSubsystem->SetSFXVolumeSetting(static_cast<int32>(this->SFXVolumeSetting->ValueSlider->GetValue()));
			SettingsSubsystem->SetVoiceVolumeSetting(static_cast<int32>(this->VoiceVolumeSetting->ValueSlider->GetValue()));
		}
	}
}

void UNexus_SoundSettings::RestoreDefaultSettings()
{
	Super::RestoreDefaultSettings();

	this->MasterVolumeSetting->ValueSlider->SetValue(this->MasterVolumeSetting->ValueSlider->GetMaxValue());
	this->BackgroundMusicSetting->ValueSlider->SetValue(this->BackgroundMusicSetting->ValueSlider->GetMaxValue());
	this->SFXVolumeSetting->ValueSlider->SetValue(this->SFXVolumeSetting->ValueSlider->GetMaxValue());
	this->VoiceVolumeSetting->ValueSlider->SetValue(this->VoiceVolumeSetting->ValueSlider->GetMaxValue());
}
