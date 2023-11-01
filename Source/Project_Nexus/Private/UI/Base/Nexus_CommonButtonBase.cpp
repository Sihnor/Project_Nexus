// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Nexus_CommonButtonBase.h"
#include "CommonTextBlock.h"

void UNexus_CommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();
	this->ButtonTextBlock->SetStyle(GetCurrentTextStyleClass());
	
}

void UNexus_CommonButtonBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	this->OnButtonBaseClicked.AddUniqueDynamic(this, &UNexus_CommonButtonBase::OnButtonClickedCallback);
}

void UNexus_CommonButtonBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (this->ButtonTextBlock != nullptr)
	{
		this->ButtonTextBlock->SetText(this->ButtonText);
	}
}

void UNexus_CommonButtonBase::OnButtonClickedCallback(UCommonButtonBase* ButtonBase) 
{
	this->OnButtonClicked.Broadcast();
}
