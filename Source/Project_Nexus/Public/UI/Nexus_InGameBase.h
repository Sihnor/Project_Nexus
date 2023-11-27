// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Nexus_CommonUserWidget.h"
#include "Nexus_InGameBase.generated.h"

class UNexus_GameOverlay;
class UNexus_InGameMenu;

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_InGameBase : public UNexus_CommonUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	class UNexus_WidgetContainerStack* GameOverlayStack;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	class UNexus_WidgetContainerStack* InGameMenuStack;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNexus_GameOverlay> GameOverlayClass;
	TObjectPtr<UNexus_GameOverlay> GameOverlayMenu;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNexus_InGameMenu> SettingMenuClass;
	TObjectPtr<UNexus_InGameMenu> SettingsMenu;

	UFUNCTION()
	void OpenGameOverlay();
};
