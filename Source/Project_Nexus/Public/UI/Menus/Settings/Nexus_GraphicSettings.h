// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_GraphicSettings.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_NEXUS_API UNexus_GraphicSettings : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_DropDownSetting* ScreenModeSetting;
	UFUNCTION()	void ChangeScreenModeEvent(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()	void ChangeScreenMode(FString SelectedItem);

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_DropDownSetting* ResolutionSetting;
	UFUNCTION()	void ChangeResolutionEvent(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()	void ChangeResolution(int width, int height);

	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CheckBoxSetting* VSyncSetting;
	UFUNCTION()	void ChangeVSyncEvent(bool bIsChecked);


	UPROPERTY(meta = (BindWidget), Blueprintable, BlueprintReadWrite)
	class UNexus_CheckBoxSetting* DisplayFPSSetting;
	UFUNCTION()	void DisplayFPSEvent(bool bIsChecked);

	UPROPERTY(meta = (BindWidget))
	class UNexus_CommonButtonBase* DefaultGraphicButton;

	UFUNCTION()
	virtual void RestoreDefaultSettings() override;


	// TODO: HIER SOLLEN NOCH VIELLEICH DIE HUD SETTINGS REIN 
};
