// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Nexus_SettingsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_SettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Game")
	void SetNumberOfRoundsSetting(int32 NewRounds);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Game")
	int32 GetNumberOfRoundsSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Game")
	void SetTimeLimitSetting(int32 NewLimit);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Game")
	int32 GetTimeLimitIndexSetting();

	int GetTimeLimitSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Game")
	void SetControllerVibrationSetting(ECheckBoxState NewState);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Game")
	ECheckBoxState GetControllerVibrationSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Graphic")
	void SetScreenModeSetting(int32 NewIndex);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Graphic")
	int32 GetScreenModeSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Graphic")
	void SetResolutionSetting(int32 NewIndex);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Graphic")
	int32 GetResolutionSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Graphic")
	void SetVSyncSetting(ECheckBoxState NewState);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Graphic")
	ECheckBoxState GetVSyncSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Graphic")
	void SetDisplayFPSSetting(ECheckBoxState NewState);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Graphic")
	ECheckBoxState GetDisplayFPSSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Sound")
	void SetMasterVolumeSetting(int32 NewVolume);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Sound")
	int32 GetMasterVolumeSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Sound")
	void SetBackgroundMusicSetting(int32 NewVolume);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Sound")
	int32 GetBackgroundMusicSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Sound")
	void SetSFXVolumeSetting(int32 NewVolume);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Sound")
	int32 GetSFXVolumeSetting();

	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Sound")
	void SetVoiceVolumeSetting(int32 NewVolume);
	
	UFUNCTION(BlueprintCallable, Category="SettingSubsystem|Sound")
	int32 GetVoiceVolumeSetting();

private:
	int32 NumberOfRounds;
	int32 TimeLimitIndex;
	ECheckBoxState ControllerVibration;
	int32 ScreenModeIndex;
	int32 ResolutionIndex;
	ECheckBoxState VSync;
	ECheckBoxState DisplayFPS;
	int32 MasterVolume;
	int32 BackgroundMusic;
	int32 SFXVolume;
	int32 VoiceVolume;
};
