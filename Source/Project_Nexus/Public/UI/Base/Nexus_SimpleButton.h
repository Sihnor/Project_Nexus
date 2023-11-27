// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Nexus_SimpleButton.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSimpleButtonClicked);

UCLASS()
class PROJECT_NEXUS_API UNexus_SimpleButton : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:
virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UOverlay* ButtonOverlay;

	UPROPERTY(meta = (BindWidget))
	class UCommonLazyImage* ButtonImage;

	FOnSimpleButtonClicked OnButtonClicked;
	UFUNCTION() void OnSimpleButtonClickedCallback(UCommonButtonBase* ButtonBase);
};
