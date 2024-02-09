// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Setting/Nexus_SliderSetting.h"

#include "CommonTextBlock.h"
#include "Components/Slider.h"

void UNexus_SliderSetting::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNexus_SliderSetting::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (this->SettingTextBlock != nullptr)
	{
		this->SettingTextBlock->SetText(this->SettingText);
	}

	this->ValueSlider->SetMinValue(this->MinValue);
	this->ValueSlider->SetMaxValue(this->MaxValue);
}

void UNexus_SliderSetting::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	this->CurrentValue->SetText(FText::FromString(FString::FromInt(this->ValueSlider->GetValue())));
}

void UNexus_SliderSetting::LoadSliderValue(int32 LoadValue)
{
	this->ValueSlider->SetValue(LoadValue);
}
