﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_GraphicSettingsMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_GraphicSettingsMenu : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	FText SceenModeText;

	UPROPERTY(meta = (BindWidget))
	FText ResolutionText;

	UPROPERTY(meta = (BindWidget))
	FText VSyncText;

	UPROPERTY(meta = (BindWidget))
	FText DisplayFPSText;


	// HIER SOLLEN NOCH VIELLEICH DIE HUD SETTINGS REIN
	
};
