// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Nexus_CommonActiveWidgetStack.generated.h"

/**
 * 
 */
class UCommonActivatableWidget;

UCLASS()
class PROJECT_NEXUS_API UNexus_CommonActiveWidgetStack : public UCommonActivatableWidgetContainerBase
{
	GENERATED_BODY()

public:
	TObjectPtr<UCommonActivatableWidget> GetRootContent() const;

protected:
	virtual void SynchronizeProperties() override;
	virtual void OnWidgetAddedToList(UCommonActivatableWidget& AddedWidget) override;
	
private:
	/** Optional widget to auto-generate as the permanent root element of the stack */
	UPROPERTY(EditAnywhere, Category = Content)
	TSubclassOf<UCommonActivatableWidget> RootContentWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<UCommonActivatableWidget> RootContentWidget;
public:
	void SetRootContentWidgetClass(TSubclassOf<class UNexus_CommonActivatableWidget> InRootContentWidgetClass);
};
