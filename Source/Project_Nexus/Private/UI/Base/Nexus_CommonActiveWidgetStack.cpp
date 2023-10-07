// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Nexus_CommonActiveWidgetStack.h"

#include "Slate/SCommonAnimatedSwitcher.h"
#include "UI/Base/Nexus_CommonActivatableWidget.h"

TObjectPtr<UCommonActivatableWidget> UNexus_CommonActiveWidgetStack::GetRootContent() const
{
	return this->RootContentWidget;
}

void UNexus_CommonActiveWidgetStack::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	Super::SynchronizeProperties();
	
#if WITH_EDITOR
	if (IsDesignTime() && this->RootContentWidget && this->RootContentWidget->GetClass() != this->RootContentWidgetClass)
	{
		// At design time, account for the possibility of the preview class changing
		if (this->RootContentWidget->GetCachedWidget())
		{
			MySwitcher->GetChildSlot(0)->DetachWidget();
		}

		RootContentWidget = nullptr;
	}
#endif

	if (!this->RootContentWidget && this->RootContentWidgetClass)
	{
		// Establish the root content as the blank 0th slot content
		this->RootContentWidget = CreateWidget<UCommonActivatableWidget>(this, this->RootContentWidgetClass);
		MySwitcher->GetChildSlot(0)->AttachWidget(this->RootContentWidget->TakeWidget());
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UNexus_CommonActiveWidgetStack::OnWidgetAddedToList(UCommonActivatableWidget& AddedWidget)
{
	if (MySwitcher)
	{
		MySwitcher->AddSlot() [AddedWidget.TakeWidget()];

		SetSwitcherIndex(MySwitcher->GetNumWidgets() - 1);
	}
}

void UNexus_CommonActiveWidgetStack::SetRootContentWidgetClass(
	TSubclassOf<UNexus_CommonActivatableWidget> InRootContentWidgetClass)
{
	this->RootContentWidgetClass = InRootContentWidgetClass;
	SynchronizeProperties();
}
