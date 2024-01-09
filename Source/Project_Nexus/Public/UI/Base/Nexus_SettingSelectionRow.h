// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus_CommonActivatableWidget.h"
#include "Nexus_SettingSelectionRow.generated.h"

class UNexus_SimpleButton;
class UNexus_CommonButtonBase;
class UNexus_GameSettings;
class UNexus_GraphicSettings;
class UNexus_SoundSettings;
/**
 * 
 */
UENUM()
enum class ESettings : uint8
{
	Game,
	Graphics,
	Sound,
	Controller,
	Copyright,
	Credits
};

UCLASS()
class PROJECT_NEXUS_API UNexus_SettingSelectionRow : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	UNexus_SettingSelectionRow();
	
	virtual void NativeConstruct() override;
	
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	UNexus_SimpleButton* DecrementSettingButton;
	int UNexus_CreditSettings;
	UFUNCTION()	void DecrementEnumSetting();
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	UNexus_SimpleButton* IncrementSettingButton;
	UFUNCTION() void IncrementEnumSetting();
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	UNexus_CommonButtonBase* GameSettingButton;
	UFUNCTION()	void GameSettingClick();
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	UNexus_CommonButtonBase* GraphicSettingButton;
	UFUNCTION()	void GraphicSettingClick();

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	UNexus_CommonButtonBase* SoundSettingButton;
	UFUNCTION()	void SoundSettingClick();

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	UNexus_CommonButtonBase* ControllerSettingButton;
	UFUNCTION()	void ControllerSettingClick();

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	UNexus_CommonButtonBase* CopyrightSettingButton;
	UFUNCTION()	void CopyrightSettingClick();

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	UNexus_CommonButtonBase* CreditSettingButton;
	UFUNCTION()	void CreditSettingClick();

	ESettings SelectedSetting;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNexus_GameSettings> GameSettingClass;
	TObjectPtr<UNexus_GameSettings> GameSettings;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNexus_GraphicSettings> GraphicSettingsClass;
	TObjectPtr<UNexus_GraphicSettings> GraphicSettings;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNexus_SoundSettings> SoundSettingsClass;
	TObjectPtr<UNexus_SoundSettings> SoundSettings;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNexus_ControllerSettings> ControllerSettingsClass;
	TObjectPtr<class UNexus_ControllerSettings> ControllerSettings;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNexus_CreditsSettings> CreditSettingsClass;
	TObjectPtr<class UNexus_CreditsSettings> CreditSettings;
	
	

	//// Online Multiplayer
	//UPROPERTY(meta = (BindWidget))
	//class UNexus_CommonButtonBase* ControllerSetupButton;

	//// Online Multiplayer
	//UPROPERTY(meta = (BindWidget))
	//class UNexus_CommonButtonBase* DisplaySettingsButton;

	//// Online Multiplayer
	//UPROPERTY(meta = (BindWidget))
	//class UNexus_CommonButtonBase* CopyrightButton;

	//// Online Multiplayer
	//UPROPERTY(meta = (BindWidget))
	//class UNexus_CommonButtonBase* CreditsButton;
	

	void InitSettingStack(UNexus_WidgetContainerStack* ActualSettingStack);

	UNexus_WidgetContainerStack* ActualSettingStackRef;
	
};

