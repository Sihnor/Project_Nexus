// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_GameSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_GameSettings : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	FText NumberOfRoundText;

	UPROPERTY(meta = (BindWidget))
	FText TimeLimitText;

	UPROPERTY(meta = (BindWidget))
	FText ControllerVibrationsText;

	UPROPERTY(meta = (BindWidget))
	FText RestoreDefaultGameSettingText;
};
