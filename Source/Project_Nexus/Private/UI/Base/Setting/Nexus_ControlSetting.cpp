// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Setting/Nexus_ControlSetting.h"

#include "CommonTextBlock.h"

void UNexus_ControlSetting::NativeConstruct()
{
	Super::NativeConstruct();

	//this->ActionWidgetOne = 
}

void UNexus_ControlSetting::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (this->SettingTextBlock != nullptr)
	{
		this->SettingTextBlock->SetText(this->SettingText);
	}
	else
	{
		this->SettingTextBlock->SetText(FText::FromString("{TEXT BLOCK}"));
	}
}