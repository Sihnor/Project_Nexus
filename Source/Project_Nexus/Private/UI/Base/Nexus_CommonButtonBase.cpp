// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Nexus_CommonButtonBase.h"
#include "CommonTextBlock.h"

void UNexus_CommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();
	this->Text->SetStyle(GetCurrentTextStyleClass());
	
}

void UNexus_CommonButtonBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	this->OnButtonBaseClicked.AddUniqueDynamic(this, &UNexus_CommonButtonBase::OnButtonClickedCallback);
}

void UNexus_CommonButtonBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	if (this->Text != nullptr)
	{
		this->Text->SetText(this->ButtonText);
	}
}

void UNexus_CommonButtonBase::OnButtonClickedCallback(UCommonButtonBase* ButtonBase) 
{
	UE_LOG(LogTemp, Warning, TEXT("DAS IST DDIE FUNKTION VOM BUTTON"))
	this->OnButtonClicked.Broadcast();
}
