// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_MainMenuHUD.generated.h"

/**
 * 
 */
class UNexus_CommonButtonBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackAction);

UCLASS()
class PROJECT_NEXUS_API UNexus_MainMenuHUD : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	UNexus_MainMenuHUD();
	
	UPROPERTY(meta=(BindWidget))
	UNexus_CommonButtonBase* OnlineButton;
	
	UPROPERTY(meta=(BindWidget))
	UNexus_CommonButtonBase* OfflineButton;

	UPROPERTY(meta=(BindWidget))
	UNexus_CommonButtonBase* GalleryButton;

	UPROPERTY(meta=(BindWidget))
	UNexus_CommonButtonBase* OptionButton;  

	UPROPERTY(meta=(BindWidget))
	UNexus_CommonButtonBase* CloseButton;

public:
	FOnBackAction OnBackAction;
	virtual bool NativeOnHandleBackAction() override;
};
