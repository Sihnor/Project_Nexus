// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_ControllerSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_ControllerSettings : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* JumpSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* CrouchSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* MoveRightSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* MoveLeftSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* LightAttackSetting;
	
	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* HeavyAttackSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* BlockingSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* SideStepLeftSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* SideStepRightSetting;

	UPROPERTY(meta = (BindWidget), Blueprintable,BlueprintReadWrite)
	class UNexus_ControlSetting* PauseSetting;
};
