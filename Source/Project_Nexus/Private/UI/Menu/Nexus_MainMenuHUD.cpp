// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/Nexus_MainMenuHUD.h"

UNexus_MainMenuHUD::UNexus_MainMenuHUD()
{
	this->bIsBackHandler = true;
}

bool UNexus_MainMenuHUD::NativeOnHandleBackAction()
{
	this->OnBackAction.Broadcast();
	return false;
}
