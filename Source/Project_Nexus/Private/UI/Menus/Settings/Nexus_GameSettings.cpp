// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Settings/Nexus_GameSettings.h"

#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "GameInstances/Nexus_GameInstance.h"
#include "Subsystems/Nexus_SettingsSubsystem.h"
#include "UI/Base/Setting/Nexus_CheckBoxSetting.h"
#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Base/Setting/Nexus_DropDownSetting.h"
#include "UI/Base/Setting/Nexus_IncrementSetting.h"
#include "UI/Base/Setting/Nexus_SliderSetting.h"

void UNexus_GameSettings::NativeConstruct()
{
	Super::NativeConstruct();

	this->TimeLimitSetting->ComboBox->AddOption(FString("50"));
	this->TimeLimitSetting->ComboBox->AddOption(FString("60"));
	this->TimeLimitSetting->ComboBox->AddOption(FString("90"));
	this->TimeLimitSetting->ComboBox->AddOption(FString("120"));
	this->TimeLimitSetting->ComboBox->AddOption(FString("150"));

	this->TimeLimitSetting->ComboBox->SetSelectedIndex(3);

	this->ControllerVibrationsSetting->CheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UNexus_GameSettings::ChangeControllerVibrations);

	this->DefaultGameButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_GameSettings::RestoreDefaultSettings);

	this->SetFocus();
}

void UNexus_GameSettings::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
	{
		if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
		{
			this->NumberOfRoundsSetting->LoadCounterValue(SettingsSubsystem->GetNumberOfRoundsSetting());
			this->TimeLimitSetting->ComboBox->SetSelectedIndex((SettingsSubsystem->GetTimeLimitSetting()));
			this->ControllerVibrationsSetting->LoadCheckBoxValue(SettingsSubsystem->GetControllerVibrationSetting());
		}
	}
}

void UNexus_GameSettings::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
	{
		if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
		{
			SettingsSubsystem->SetNumberOfRoundsSetting(this->NumberOfRoundsSetting->Counter);
			SettingsSubsystem->SetTimeLimitSetting(this->TimeLimitSetting->ComboBox->GetSelectedIndex());
			SettingsSubsystem->SetControllerVibrationSetting(this->ControllerVibrationsSetting->CheckBox->GetCheckedState());
		}
	}
}

void UNexus_GameSettings::ChangeControllerVibrations(bool bIsChecked)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
 
     if (PlayerController)
     {
        PlayerController->SetDisableHaptics(bIsChecked);
     }
}

void UNexus_GameSettings::RestoreDefaultSettings()
{
	Super::RestoreDefaultSettings();

	this->NumberOfRoundsSetting->ResetCounter();
	this->TimeLimitSetting->ComboBox->SetSelectedIndex(0);
	this->ControllerVibrationsSetting->CheckBox->SetCheckedState(ECheckBoxState::Checked);
	this->ChangeControllerVibrations(true);
}
