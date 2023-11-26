// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Nexus_SimpleButton.h"

void UNexus_SimpleButton::NativeConstruct()
{
	Super::NativeConstruct();

	this->OnButtonBaseClicked.AddUniqueDynamic(this, &UNexus_SimpleButton::OnSimpleButtonClickedCallback);
}

void UNexus_SimpleButton::OnSimpleButtonClickedCallback(UCommonButtonBase* ButtonBase)
{
	this->OnButtonClicked.Broadcast();
}
