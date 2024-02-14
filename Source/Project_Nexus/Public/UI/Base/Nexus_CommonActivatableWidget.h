// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Nexus_CommonActivatableWidget.generated.h"

class UNexus_WidgetContainerStack;

/**
 * 
 */

UCLASS(Abstract)
class PROJECT_NEXUS_API UNexus_CommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UOverlay* MenuOverlay;

	UPROPERTY(meta = (BindWidget))
	class UCommonBorder* MenuBorder;

	virtual void PassStackVariable(UNexus_WidgetContainerStack* MenuStack);

	UNexus_WidgetContainerStack* MenuStackRef;

	virtual void RestoreDefaultSettings(){};
};
