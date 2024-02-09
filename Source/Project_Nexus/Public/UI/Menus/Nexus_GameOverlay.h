// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_GameOverlay.generated.h"

class UProgressBar;
class UCommonTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_GameOverlay : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* PlayerOneHealth;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* PlayerTwoHealth;

	UPROPERTY(meta=(BindWidget))
	UCommonTextBlock* ActualTime;

	UFUNCTION()
	void OnTickEvent(int32 RemainingTimer);
};
