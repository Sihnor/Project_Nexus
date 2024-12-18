// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Setting/Nexus_DropDownSetting.h"

#include "CommonTextBlock.h"
#include "Components/ComboBoxString.h"


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

int UNexus_DropDownSetting::GetSelectedOption() const
{
	switch (this->ComboBox->GetSelectedIndex())
	{
	case 0:
		return 50;
	case 1:
		return 60;
	case 2:
		return 90;
	case 3:
		return 120;
	case 4:
		return 150;
	default: ;
	}

	return 0;
}
