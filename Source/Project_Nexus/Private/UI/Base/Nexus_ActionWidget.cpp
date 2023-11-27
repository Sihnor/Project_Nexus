// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Base/Nexus_ActionWidget.h"

#include "CommonInputBaseTypes.h"
#include "CommonInputSubsystem.h"
#include "EnhancedInputSubsystems.h"

FSlateBrush UNexus_ActionWidget::GetIcon() const
{
	// If there is an Enhanced Input action associated with this widget, then search for any
	// keys bound to that action and display those instead of the default data table settings.
	// This covers the case of when a player has rebound a key to something else
	if (AssociatedInputAction)
	{
		UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();
		UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = GetEnhancedInputSubsystem();
		TArray<FKey> BoundKeys = EnhancedInputSubsystem->QueryKeysMappedToAction(AssociatedInputAction);
		FSlateBrush SlateBrush;

		if (!BoundKeys.IsEmpty() && UCommonInputPlatformSettings::Get()->TryGetInputBrush(SlateBrush, BoundKeys[0], CommonInputSubsystem->GetCurrentInputType(), CommonInputSubsystem->GetCurrentGamepadName()))
		{
			return SlateBrush;
		}
	}
	
	return Super::GetIcon();
}

UEnhancedInputLocalPlayerSubsystem* UNexus_ActionWidget::GetEnhancedInputSubsystem() const
{
	const UWidget* BoundWidget = DisplayedBindingHandle.GetBoundWidget();
	const ULocalPlayer* BindingOwner = BoundWidget ? BoundWidget->GetOwningLocalPlayer() : GetOwningLocalPlayer();
	
	return BindingOwner->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
}
