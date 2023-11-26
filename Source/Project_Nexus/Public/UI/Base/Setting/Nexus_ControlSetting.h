// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_ControlSetting.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_ControlSetting : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;
	
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* SettingTextBlock;
	
	UPROPERTY(EditAnywhere, Category="Variable")
	FText SettingText;
};
