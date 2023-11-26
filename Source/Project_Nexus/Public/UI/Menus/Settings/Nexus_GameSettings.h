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
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_IncrementSetting* NumberOfRoundsSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_DropDownSetting* TimeLimitSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_CheckBoxSetting* ControllerVibrationsSetting;
	UFUNCTION() void ChangeControllerVibrations(bool bIsChecked);

	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* DefaultGameButton;

	UFUNCTION()
	virtual void RestoreDefaultSettings() override;
};
