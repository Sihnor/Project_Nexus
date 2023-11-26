// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Nexus_SettingsMenu.h"

#include "UI/Base/Nexus_SettingSelectionRow.h"

void UNexus_SettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	this->SelectionRow->PassStackVariable(this->MenuStackRef);
	this->SelectionRow->InitSettingStack(this->ActualSetting);
}
