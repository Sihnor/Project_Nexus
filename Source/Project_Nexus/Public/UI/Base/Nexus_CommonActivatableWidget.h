// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Nexus_CommonActivatableWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_CommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UCommonBorder* Border;
};
