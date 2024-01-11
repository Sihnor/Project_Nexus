// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Settings/Nexus_GameSettings.h"

#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "GameInstances/Nexus_GameInstance.h"
#include "Subsystems/Nexus_SettingsSubsystem.h"
#include "UENUMS/TimeLimits.h"
#include "UI/Base/Setting/Nexus_CheckBoxSetting.h"
#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Base/Setting/Nexus_DropDownSetting.h"
#include "UI/Base/Setting/Nexus_IncrementSetting.h"

void UNexus_GameSettings::NativeConstruct()
{
	Super::NativeConstruct();

	this->TimeLimitSetting->ComboBox->AddOption(FString(FString::FromInt((static_cast<int>(EAllTimeLimitsEnum::first)))));
	this->TimeLimitSetting->ComboBox->AddOption(FString(FString::FromInt((static_cast<int>(EAllTimeLimitsEnum::second)))));
	this->TimeLimitSetting->ComboBox->AddOption(FString(FString::FromInt((static_cast<int>(EAllTimeLimitsEnum::third)))));
	this->TimeLimitSetting->ComboBox->AddOption(FString(FString::FromInt((static_cast<int>(EAllTimeLimitsEnum::fourth)))));
	this->TimeLimitSetting->ComboBox->AddOption(FString(FString::FromInt((static_cast<int>(EAllTimeLimitsEnum::fifth)))));
		
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
			this->TimeLimitSetting->ComboBox->SetSelectedIndex((SettingsSubsystem->GetTimeLimitIndexSetting()));
			this->ControllerVibrationsSetting->LoadCheckBoxValue(SettingsSubsystem->GetControllerVibrationSetting());

			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("TimeLimitIndex: %d"), SettingsSubsystem->GetTimeLimitIndexSetting()));
			}
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
