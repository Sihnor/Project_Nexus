// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Nexus_MainMenu.h"


#include "Kismet/KismetSystemLibrary.h"
#include "UI/Menus/Settings/Nexus_GameSettings.h"
#include "UI/Menus/Nexus_SettingsMenu.h"
#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Base/Nexus_WidgetContainerStack.h"




void UNexus_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	//this->SetFocus();

	this->OnlineButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_MainMenu::OpenOnlineMode);
	this->OfflineButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_MainMenu::OpenOfflineMode);
	this->SettingsButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_MainMenu::OpenSettingsMenu);
	this->GalleryButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_MainMenu::OpenGalleryMenu);
	this->QuitButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_MainMenu::QuitGame);
}

void UNexus_MainMenu::OpenOnlineMode()
{
	this->OpenChampSelect();
}

void UNexus_MainMenu::OpenOfflineMode()
{
	this->OpenChampSelect();
}

void UNexus_MainMenu::OpenSettingsMenu()
{
	this->SettingsMenu = this->MenuStackRef->AddWidget<UNexus_SettingsMenu>(this->SettingMenuClass);
	this->SettingsMenu->PassStackVariable(this->MenuStackRef);
	
	//this->MenuStackRef->SetVisibility(ESlateVisibility::Hidden);
}

void UNexus_MainMenu::CloseSettingsMenu()
{
	this->MenuStackRef->SetVisibility(ESlateVisibility::Visible);
}

void UNexus_MainMenu::OpenGalleryMenu()
{
	// TODO: Erstelle eine Gallery
}

void UNexus_MainMenu::CloseGalleryMenu()
{
	// TODO: Schliesse die Galery
}

void UNexus_MainMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UNexus_MainMenu::OpenChampSelect()
{
	this->OnChangeToLobby.Broadcast();
}



