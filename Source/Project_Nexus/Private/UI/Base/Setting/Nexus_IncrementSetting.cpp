// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Setting/Nexus_IncrementSetting.h"


#include "CommonTextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "UI/Base/Nexus_SimpleButton.h"


void UNexus_IncrementSetting::NativeConstruct()
{
	Super::NativeConstruct();
	
	this->MinCounter = 3;
	this->MaxCounter = 9;

	this->Counter = this->MinCounter;
	

	this->IncrementCounterButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_IncrementSetting::IncrementCounter);
	this->DecrementCounterButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_IncrementSetting::DecrementCounter);
}

void UNexus_IncrementSetting::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (this->SettingTextBlock != nullptr)
	{
		this->SettingTextBlock->SetText(this->SettingText);
	}
}

void UNexus_IncrementSetting::IncrementCounter()
{
	if (this->Counter >= this->MaxCounter)
	{
		return;
	}
	this->Counter += 2;
	this->CounterTextBlock->SetText(FText::FromString(FString::FromInt(this->Counter)));
}

void UNexus_IncrementSetting::DecrementCounter()
{
	if (this->Counter <= this->MinCounter)
	{
		return;
	}
	this->Counter -= 2;
	this->CounterTextBlock->SetText(FText::FromString(FString::FromInt(this->Counter)));
}

void UNexus_IncrementSetting::LoadCounterValue(int32 LoadValue)
{
	this->Counter = LoadValue;
	
	this->CounterTextBlock->SetText(FText::FromString(FString::FromInt(this->Counter)));
}

void UNexus_IncrementSetting::ResetCounter()
{
	this->Counter = this->MinCounter;
	this->CounterTextBlock->SetText(FText::FromString(FString::FromInt(this->Counter)));
}
