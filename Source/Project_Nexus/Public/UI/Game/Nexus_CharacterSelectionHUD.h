// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_CharacterSelectionHUD.generated.h"

/**
 * 
 */

class UNexus_CommonButtonBase;

UCLASS()
class PROJECT_NEXUS_API UNexus_CharacterSelectionHUD : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta=(BindWidget))
	UNexus_CommonButtonBase* CharacterTwoButton;

	UPROPERTY(meta=(BindWidget))
	UNexus_CommonButtonBase* CharacterOneButton;
};
