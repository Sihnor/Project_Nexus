// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Nexus_InGameBase.h"

#include "UI/Base/Nexus_WidgetContainerStack.h"
#include "UI/Menus/Nexus_GameOverlay.h"

void UNexus_InGameBase::NativeConstruct()
{
	Super::NativeConstruct();

	this->OpenGameOverlay();
}

void UNexus_InGameBase::OpenGameOverlay()
{
	this->GameOverlayMenu = this->GameOverlayStack->AddWidget<UNexus_GameOverlay>(this->GameOverlayClass);
}
