// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_SettingsMenu.generated.h"

class UNexus_GameSettings;
class UNexus_GraphicSettings;
class UNexus_SoundSettings;
class UNexus_SettingSelectionRow;
/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_SettingsMenu : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess))
	UNexus_SettingSelectionRow* SelectionRow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	UNexus_WidgetContainerStack* ActualSetting;

	
	
};
