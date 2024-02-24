// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Nexus_CommonUserWidget.h"
#include "Nexus_StartBase.generated.h"


UCLASS()
class PROJECT_NEXUS_API UNexus_StartBase : public UNexus_CommonUserWidget
{
public:
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UOverlay* OverlayPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	class UNexus_WidgetContainerStack* MenuStack;



	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UNexus_MainMenu> MainMenuClass;
	TObjectPtr<UNexus_MainMenu> MainMenu;


	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenLobby();

	//me
	UFUNCTION()
	void OpenOnlineLobby();

	UFUNCTION(BlueprintCallable)
	void PushMenu(TSubclassOf<UNexus_CommonActivatableWidget> ActivatableWidgetClass);
};
