// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Nexus_SettingsSubsystem.h"

void UNexus_SettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	this->NumberOfRounds = 5;
	this->TimeLimit = 90;
	this->ControllerVibration = ECheckBoxState::Checked;

	this->ScreenModeIndex = 0;
	this->ResolutionIndex = 8;
	this->VSync = ECheckBoxState::Unchecked;
	this->DisplayFPS = ECheckBoxState::Unchecked;

	this->MasterVolume = 70;
	this->BackgroundMusic = 70;
	this->SFXVolume = 70;
	this->VoiceVolume = 70;
}

void UNexus_SettingsSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UNexus_SettingsSubsystem::SetNumberOfRoundsSetting(int32 NewRounds)
{
	this->NumberOfRounds = NewRounds;
}

int32 UNexus_SettingsSubsystem::GetNumberOfRoundsSetting()
{
	return this->NumberOfRounds;
}

void UNexus_SettingsSubsystem::SetTimeLimitSetting(int32 NewLimit)
{
	this->TimeLimit = NewLimit;
}

int32 UNexus_SettingsSubsystem::GetTimeLimitSetting()
{
	return this->TimeLimit;
}

void UNexus_SettingsSubsystem::SetControllerVibrationSetting(ECheckBoxState NewState)
{
	this->ControllerVibration = NewState;
}

ECheckBoxState UNexus_SettingsSubsystem::GetControllerVibrationSetting()
{
	return this->ControllerVibration;
}

void UNexus_SettingsSubsystem::SetScreenModeSetting(int32 NewIndex)
{
	this->ScreenModeIndex = NewIndex;
}

int32 UNexus_SettingsSubsystem::GetScreenModeSetting()
{
	return this->ScreenModeIndex;
}

void UNexus_SettingsSubsystem::SetResolutionSetting(int32 NewIndex)
{
	this->ResolutionIndex = NewIndex;
}

int32 UNexus_SettingsSubsystem::GetResolutionSetting()
{
	return this->ResolutionIndex;
}

void UNexus_SettingsSubsystem::SetVSyncSetting(ECheckBoxState NewState)
{
	this->VSync = NewState;
}

ECheckBoxState UNexus_SettingsSubsystem::GetVSyncSetting()
{
	return this->VSync;
}

void UNexus_SettingsSubsystem::SetDisplayFPSSetting(ECheckBoxState NewState)
{
	this->DisplayFPS = NewState;
}

ECheckBoxState UNexus_SettingsSubsystem::GetDisplayFPSSetting()
{
	return this->DisplayFPS;
}

void UNexus_SettingsSubsystem::SetMasterVolumeSetting(int32 NewVolume)
{
	this->MasterVolume = NewVolume;
}

int32 UNexus_SettingsSubsystem::GetMasterVolumeSetting()
{
	return this->MasterVolume;
}

void UNexus_SettingsSubsystem::SetBackgroundMusicSetting(int32 NewVolume)
{
	this->BackgroundMusic = NewVolume;
}

int32 UNexus_SettingsSubsystem::GetBackgroundMusicSetting()
{
	return this->BackgroundMusic;
}

void UNexus_SettingsSubsystem::SetSFXVolumeSetting(int32 NewVolume)
{
	this->SFXVolume = NewVolume;
}

int32 UNexus_SettingsSubsystem::GetSFXVolumeSetting()
{
	return this->SFXVolume;
}

void UNexus_SettingsSubsystem::SetVoiceVolumeSetting(int32 NewVolume)
{
	this->VoiceVolume = NewVolume;
}

int32 UNexus_SettingsSubsystem::GetVoiceVolumeSetting()
{
	return this->VoiceVolume;
}
