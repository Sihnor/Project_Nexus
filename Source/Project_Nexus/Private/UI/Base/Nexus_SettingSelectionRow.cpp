// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Nexus_SettingSelectionRow.h"

#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Base/Setting/Nexus_IncrementSetting.h"
#include "UI/Base/Nexus_SimpleButton.h"
#include "UI/Base/Nexus_WidgetContainerStack.h"

#include "UI/Menus/Settings/Nexus_GameSettings.h"
#include "UI/Menus/Settings/Nexus_GraphicSettings.h"
#include "UI/Menus/Settings/Nexus_SoundSettings.h"
#include "UI/Menus/Settings/Nexus_ControllerSettings.h"
#include "UI/Menus/Settings/Nexus_CreditsSettings.h"

UNexus_SettingSelectionRow::UNexus_SettingSelectionRow()
{
	this->SelectedSetting = ESettings::Game;
}

void UNexus_SettingSelectionRow::NativeConstruct()
{
	Super::NativeConstruct();

	this->DecrementSettingButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_SettingSelectionRow::DecrementEnumSetting);
	this->IncrementSettingButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_SettingSelectionRow::IncrementEnumSetting);
	this->GameSettingButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_SettingSelectionRow::GameSettingClick);
	this->GraphicSettingButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_SettingSelectionRow::GraphicSettingClick);
	this->SoundSettingButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_SettingSelectionRow::SoundSettingClick);
	this->ControllerSettingButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_SettingSelectionRow::ControllerSettingClick);
	this->CopyrightSettingButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_SettingSelectionRow::CopyrightSettingClick);
	this->CreditSettingButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_SettingSelectionRow::CreditSettingClick);
}

void UNexus_SettingSelectionRow::DecrementEnumSetting()
{
	switch (this->SelectedSetting)
	{
	case ESettings::Game:
		this->CreditSettingClick();
		break;
	case ESettings::Graphics:
		this->GameSettingClick();
		break;
	case ESettings::Sound:
		this->GraphicSettingClick();
		break;
	case ESettings::Controller:
		this->SoundSettingClick();
		break;
	case ESettings::Copyright:
		this->ControllerSettingClick();
		break;
	case ESettings::Credits:
		this->CopyrightSettingClick();
		break;
	default: ;
	}
}

void UNexus_SettingSelectionRow::IncrementEnumSetting()
{
	switch (this->SelectedSetting)
	{
	case ESettings::Game:
		this->GraphicSettingClick();
		break;
	case ESettings::Graphics:
		this->SoundSettingClick();
		break;
	case ESettings::Sound:
		this->ControllerSettingClick();
		break;
	case ESettings::Controller:
		this->CopyrightSettingClick();
		break;
	case ESettings::Copyright:
		this->CreditSettingClick();
		break;
	case ESettings::Credits:
		this->GameSettingClick();
		break;
	default: ;
	}
}

void UNexus_SettingSelectionRow::GameSettingClick()
{
	this->SelectedSetting = ESettings::Game;

	this->GameSettings = this->ActualSettingStackRef->AddWidget<UNexus_GameSettings>(this->GameSettingClass);

	
}

void UNexus_SettingSelectionRow::GraphicSettingClick()
{
	this->SelectedSetting = ESettings::Graphics;
	
	this->GraphicSettings = this->ActualSettingStackRef->AddWidget<UNexus_GraphicSettings>(this->GraphicSettingsClass);
}

void UNexus_SettingSelectionRow::SoundSettingClick()
{
	this->SelectedSetting = ESettings::Sound;
	
	this->SoundSettings = this->ActualSettingStackRef->AddWidget<UNexus_SoundSettings>(this->SoundSettingsClass);
}

void UNexus_SettingSelectionRow::ControllerSettingClick()
{
	this->SelectedSetting = ESettings::Controller;
	
	this->ControllerSettings = this->ActualSettingStackRef->AddWidget<UNexus_ControllerSettings>(this->ControllerSettingsClass);
}

void UNexus_SettingSelectionRow::CopyrightSettingClick()
{
	this->SelectedSetting = ESettings::Copyright;
	
	//this->CopyrightSettings = this->ActualSettingStackRef->AddWidget<UNexus_CopyrightSettings>(this->CopyrightSettingsClass);
}

void UNexus_SettingSelectionRow::CreditSettingClick()
{
	this->SelectedSetting = ESettings::Credits;
	
	this->CreditSettings = this->ActualSettingStackRef->AddWidget<UNexus_CreditsSettings>(this->CreditSettingsClass);
}

void UNexus_SettingSelectionRow::InitSettingStack(UNexus_WidgetContainerStack* SettingStack)
{
	this->ActualSettingStackRef = SettingStack;

	// Start the first Setting
	this->GameSettings = this->ActualSettingStackRef->AddWidget<UNexus_GameSettings>(this->GameSettingClass);
}
