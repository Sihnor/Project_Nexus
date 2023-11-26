// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Setting/Nexus_CheckBoxSetting.h"

#include "CommonTextBlock.h"
#include "Components/CheckBox.h"

void UNexus_CheckBoxSetting::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNexus_CheckBoxSetting::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (this->SettingTextBlock != nullptr)
	{
		this->SettingTextBlock->SetText(this->SettingText);
	}
}

void UNexus_CheckBoxSetting::LoadCheckBoxValue(ECheckBoxState LoadValue)
{
	this->CheckBox->SetCheckedState(LoadValue);
}
