// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_CheckBoxSetting.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_CheckBoxSetting : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;
	
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* SettingTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CheckBox;

	UPROPERTY(EditAnywhere, Category="Variable")
	FText SettingText;

	void LoadCheckBoxValue(ECheckBoxState LoadValue);
};
