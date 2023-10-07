// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Nexus_CommonButtonBase.h"

#include "CommonTextBlock.h"

void UNexus_CommonButtonBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (this->Text != nullptr)
	{
		this->Text->SetText(this->ButtonText);
	}
}

void UNexus_CommonButtonBase::NativeConstruct()
{
	this->OnButtonClicked.AddUniqueDynamic(this, &UNexus_CommonButtonBase::OnButtonClickedCallback);
	Super::NativeConstruct();
}

void UNexus_CommonButtonBase::OnButtonClickedCallback()
{
	this->OnButtonClicked.Broadcast();
}
