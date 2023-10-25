// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Nexus_CommonButtonBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

UCLASS()
class PROJECT_NEXUS_API UNexus_CommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()
public:
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;

	UPROPERTY(meta = (BindWidget))
	class UCommonTextBlock* Text;

	UPROPERTY(EditAnywhere)
	FText ButtonText;

	FOnButtonClicked OnButtonClicked;
	UFUNCTION() void OnButtonClickedCallback(UCommonButtonBase* ButtonBase);
	
};
