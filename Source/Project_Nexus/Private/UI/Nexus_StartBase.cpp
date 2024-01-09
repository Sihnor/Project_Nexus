// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Nexus_StartBase.h"

#include "Kismet/GameplayStatics.h"
#include "UI/Base/Nexus_WidgetContainerStack.h"
#include "UI/Menus/Nexus_MainMenu.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UNexus_StartBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	this->OpenMainMenu();
}

void UNexus_StartBase::OpenMainMenu()
{
	this->MainMenu = this->MenuStack->AddWidget<UNexus_MainMenu>(this->MainMenuClass);
	this->MainMenu->PassStackVariable(this->MenuStack);
	this->MainMenu->OnChangeToLobby.AddUniqueDynamic(this, &UNexus_StartBase::OpenLobby);
	this->MainMenu->SetIsFocusable(true);
}

void UNexus_StartBase::OpenLobby()
{
	//this->MenuStack->SetVisibility(ESlateVisibility::Hidden);

	FString MapName = "ChampSelectLevel";

	UGameplayStatics::OpenLevel(this, *MapName, true);
}

void UNexus_StartBase::PushMenu(TSubclassOf<UNexus_CommonActivatableWidget> ActivatableWidgetClass)
{
	this->MenuStack->AddWidget<UNexus_CommonActivatableWidget>(ActivatableWidgetClass);
}

//if (GEngine) {
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), OutWidth));
//}

