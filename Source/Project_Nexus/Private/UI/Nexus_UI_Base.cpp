// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Nexus_UI_Base.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UI/Base/Nexus_CommonActiveWidgetStack.h"
#include "UI/Base/Nexus_CommonButtonBase.h"
#include "UI/Game/Nexus_CharacterSelectionHUD.h"
#include "UI/Game/Nexus_GameOverlayHUD.h"
#include "UI/Menu/Nexus_MainMenuHUD.h"
#include "UI/Menu/Nexus_PauseMenuHUD.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UNexus_UI_Base::MyInitialize()
 {
	ensureMsgf(this->MainMenuHUDClass != nullptr, TEXT("Please set a correct class as EditorHUDClass in UUI_Base"));
	ensureMsgf(this->CharacterSelectionClass != nullptr, TEXT("Please set a correct class as EditorMainMenuClass in UUI_Base"));
	ensureMsgf(this->GameOverlayClass != nullptr, TEXT("Please set a correct class as SaveMenuClass in UUI_Base"));
	ensureMsgf(this->PauseOverlayClass != nullptr, TEXT("Please set a correct class as NewSaveGameWidgetClass in UUI_Base"));

	this->Stack->SetRootContentWidgetClass(this->MainMenuHUDClass);
	this->MainMenuHUD = Cast<UNexus_MainMenuHUD>(this->Stack->GetRootContent());
	this->MainMenuHUD->MyInitialize();
	this->MainMenuHUD->OnBackAction.AddUniqueDynamic(this, &UNexus_UI_Base::QuitGame);
	
	this->MainMenuHUD->ActivateWidget();
 }

void UNexus_UI_Base::OpenMainMenu()
{
	this->MainMenuHUD = Stack->AddWidget<UNexus_MainMenuHUD>(this->MainMenuHUDClass);
	this->MainMenuHUD->OnlineButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_UI_Base::OpenOnlineMenu);
	this->MainMenuHUD->OfflineButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_UI_Base::OpenOfflineMenu);
	this->MainMenuHUD->GalleryButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_UI_Base::OpenGalleryMenu);
	this->MainMenuHUD->OptionButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_UI_Base::OpenOptionsMenu);
	this->MainMenuHUD->CloseButton->OnButtonClicked.AddUniqueDynamic(this, &UNexus_UI_Base::QuitGame);
	
	this->MainMenuHUD->SetFocus();
}

void UNexus_UI_Base::CloseMainMenu()
{
	this->MainMenuHUD->DeactivateWidget();
	
}

void UNexus_UI_Base::OpenOnlineMenu()
{
}

void UNexus_UI_Base::CloseOnlineMenu()
{
}

void UNexus_UI_Base::OpenOfflineMenu()
{
}

void UNexus_UI_Base::CloseOfflineMenu()
{
}

void UNexus_UI_Base::OpenGalleryMenu()
{
}

void UNexus_UI_Base::CloseGalleryMenu()
{
}

void UNexus_UI_Base::OpenOptionsMenu()
{
}

void UNexus_UI_Base::CloseOptionsMenu()
{
}

void UNexus_UI_Base::CloseGameOverlay()
{
}

void UNexus_UI_Base::OpenCharacterSelection()
{
}

void UNexus_UI_Base::CloseCharacterSelection()
{
}

void UNexus_UI_Base::OpenGameOverlay()
{
}

void UNexus_UI_Base::QuitGame()
{
	// TODO: Check if that work in production build
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
	// This also shuts down the editor in PIE
	//FGenericPlatformMisc::RequestExit(false);
}
