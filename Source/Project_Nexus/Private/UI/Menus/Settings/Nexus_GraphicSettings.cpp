// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Settings/Nexus_GraphicSettings.h"

#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "GameInstances/Nexus_GameInstance.h"
#include "Kismet/KismetStringLibrary.h"
#include "Subsystems/Nexus_SettingsSubsystem.h"
#include "UI/Base/Setting/Nexus_CheckBoxSetting.h"
#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Base/Setting/Nexus_DropDownSetting.h"

void UNexus_GraphicSettings::NativeConstruct()
{
	Super::NativeConstruct();

	this->ResolutionSetting->ComboBox->AddOption(FString("720 x 480"));
	this->ResolutionSetting->ComboBox->AddOption(FString("720 x 576"));
	this->ResolutionSetting->ComboBox->AddOption(FString("1280 x 720"));
	this->ResolutionSetting->ComboBox->AddOption(FString("1280 x 1024"));
	this->ResolutionSetting->ComboBox->AddOption(FString("1366 x 768"));
	this->ResolutionSetting->ComboBox->AddOption(FString("1440 x 900"));
	this->ResolutionSetting->ComboBox->AddOption(FString("1536 x 864"));
	this->ResolutionSetting->ComboBox->AddOption(FString("1600 x 900"));
	this->ResolutionSetting->ComboBox->AddOption(FString("1920 x 1080"));
	this->ResolutionSetting->ComboBox->AddOption(FString("2560 x 1440"));
	this->ResolutionSetting->ComboBox->AddOption(FString("3840 x 2160"));
	this->ResolutionSetting->ComboBox->AddOption(FString("7680 x 4320"));

	this->ResolutionSetting->ComboBox->SetSelectedIndex(8);
	this->ChangeResolution(1920, 1080);
	this->ResolutionSetting->ComboBox->OnSelectionChanged.AddUniqueDynamic(this, &UNexus_GraphicSettings::ChangeResolutionEvent);
	
	this->ScreenModeSetting->ComboBox->AddOption(FString("Fullscreen"));
	this->ScreenModeSetting->ComboBox->AddOption(FString("WindowedFullscreen"));
	this->ScreenModeSetting->ComboBox->AddOption(FString("Windowed"));

	this->ScreenModeSetting->ComboBox->SetSelectedIndex(0);
	
	this->ScreenModeSetting->ComboBox->OnSelectionChanged.AddUniqueDynamic(this, &UNexus_GraphicSettings::ChangeScreenModeEvent);

	
	this->ChangeScreenMode("Windowed");
	
	this->VSyncSetting->CheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UNexus_GraphicSettings::ChangeVSyncEvent);


	this->DefaultGraphicButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_GraphicSettings::RestoreDefaultSettings);
}

void UNexus_GraphicSettings::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
	{
		if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
		{
			this->ScreenModeSetting->ComboBox->SetSelectedIndex(SettingsSubsystem->GetScreenModeSetting());
			this->ResolutionSetting->ComboBox->SetSelectedIndex(SettingsSubsystem->GetResolutionSetting());
			this->VSyncSetting->CheckBox->SetCheckedState(SettingsSubsystem->GetVSyncSetting());
			this->DisplayFPSSetting->CheckBox->SetCheckedState(SettingsSubsystem->GetDisplayFPSSetting());
		}
	}
}

void UNexus_GraphicSettings::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
	{
		if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
		{
			SettingsSubsystem->SetScreenModeSetting(this->ScreenModeSetting->ComboBox->GetSelectedIndex());
			SettingsSubsystem->SetResolutionSetting(this->ResolutionSetting->ComboBox->GetSelectedIndex());
			SettingsSubsystem->SetVSyncSetting(this->VSyncSetting->CheckBox->GetCheckedState());
			SettingsSubsystem->SetDisplayFPSSetting(this->DisplayFPSSetting->CheckBox->GetCheckedState());
		}
	}
}

void UNexus_GraphicSettings::ChangeScreenModeEvent(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	this->ChangeScreenMode(SelectedItem);
}

void UNexus_GraphicSettings::ChangeScreenMode(FString SelectedItem)
{
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();

	if (!UserSettings)
	{
		return;
	}
	
	if (SelectedItem == "Fullscreen")
	{
		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
	}

	if (SelectedItem == "WindowedFullscreen")
	{
		UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	}

	if (SelectedItem == "Windowed")
	{
		UserSettings->SetFullscreenMode(EWindowMode::Windowed);
	}

	UserSettings->ApplySettings(false);
}

void UNexus_GraphicSettings::ChangeResolutionEvent(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	TArray<FString> ResolutionArray = UKismetStringLibrary::ParseIntoArray(SelectedItem, TEXT("x"));

	int32 OutWidth = 0;
	int32 OutHeight = 0;
	
	if (ResolutionArray.Num() == 2)
	{
		// Konvertiere die beiden Teile in Zahlen (Breite und Höhe)
		OutWidth = FCString::Atoi(*ResolutionArray[0]);
		OutHeight = FCString::Atoi(*ResolutionArray[1]);
	}

	this->ChangeResolution(OutWidth, OutHeight);

}

void UNexus_GraphicSettings::ChangeResolution(int width, int height)
{
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	
	if (UserSettings)
	{
		UserSettings->SetScreenResolution(FIntPoint(width, height));
		UserSettings->ApplySettings(false);
	}
}

void UNexus_GraphicSettings::ChangeVSyncEvent(bool bIsChecked)
{
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();

	if (UserSettings)
	{
		UserSettings->SetVSyncEnabled(bIsChecked);
		UserSettings->ApplySettings(false);
	}
}

void UNexus_GraphicSettings::DisplayFPSEvent(bool bIsChecked)
{
	// TODO: Muss noch gemacht werden wenn das Overlay steht
}

void UNexus_GraphicSettings::RestoreDefaultSettings()
{
	Super::RestoreDefaultSettings();
	
	this->ResolutionSetting->ComboBox->SetSelectedIndex(8);
	this->ChangeResolution(1920, 1080);

	this->ScreenModeSetting->ComboBox->SetSelectedIndex(0);
	this->ChangeScreenMode("Fullscreen");

	this->VSyncSetting->CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	this->ChangeVSyncEvent(false);

	this->DisplayFPSSetting->CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	this->DisplayFPSEvent(false);
}

