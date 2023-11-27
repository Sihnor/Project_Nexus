// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Setting/Nexus_DropDownSetting.h"

#include "CommonTextBlock.h"


void UNexus_DropDownSetting::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNexus_DropDownSetting::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (this->SettingTextBlock != nullptr)
	{
		this->SettingTextBlock->SetText(this->SettingText);
	}
}