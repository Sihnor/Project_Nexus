// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Nexus_UIBaseCanvas.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Menus/Nexus_ChampionSelection.h"
#include "UI/Menus/Nexus_MainMenu.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UNexus_UIBaseCanvas::NativeConstruct()
{
	Super::NativeConstruct();

	ensureMsgf(this->MainMenuClass != nullptr, TEXT("Please set a correct class as MainMenuClass"));
	ensureMsgf(this->ChampionSelectionMenu != nullptr, TEXT("Please set a correct class as ChampionSelection"));
	
	this->OpenMainMenu();
	
}

void UNexus_UIBaseCanvas::OpenMainMenu()
{
	//this->Stack->AddWidget(this->MainMenuClass);
	this->MainMenu = this->Stack->AddWidget<UNexus_MainMenu>(this->MainMenuClass);
	this->MainMenu->OfflineButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_UIBaseCanvas::OpenOfflineMenu);
	this->MainMenu->QuitButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_UIBaseCanvas::QuitGame);


}

void UNexus_UIBaseCanvas::CloseMainMenu()
{
	this->MainMenu->DeactivateWidget();
}

void UNexus_UIBaseCanvas::OpenOfflineMenu()
{
	this->ChampionSelectionMenu = this->Stack->AddWidget<UNexus_ChampionSelection>(this->ChampionSelectionClass);
}

void UNexus_UIBaseCanvas::CloseOfflineMenu()
{
}

void UNexus_UIBaseCanvas::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}



