// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_SliderSetting.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_SliderSetting : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Variable")
	FText SettingText;
	
	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* SettingTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCommonTextBlock* CurrentValue;

	UPROPERTY(EditAnywhere, Category="Variable")
	float MinValue;
	UPROPERTY(EditAnywhere, Category="Variable")
	float MaxValue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USlider* ValueSlider;

	void LoadSliderValue(int32 LoadValue);
	
};
