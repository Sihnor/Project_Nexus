// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"
#include "Nexus_IncrementSetting.generated.h"

class UNexus_SimpleButton;
class UCommonTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API UNexus_IncrementSetting : public UNexus_CommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Variable")
	int Counter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variable")
	int MaxCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variable")
	int MinCounter;

	UPROPERTY(EditAnywhere, Category="Variable")
	FText SettingText;
	
	UPROPERTY(meta = (BindWidget))
	UCommonTextBlock* SettingTextBlock;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UNexus_SimpleButton* IncrementCounterButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UNexus_SimpleButton* DecrementCounterButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UCommonTextBlock* CounterTextBlock;


	UFUNCTION(BlueprintCallable)
	void IncrementCounter();

	UFUNCTION(BlueprintCallable)
	void DecrementCounter();

	void LoadCounterValue(int32 LoadValue);
	
	void ResetCounter();
};