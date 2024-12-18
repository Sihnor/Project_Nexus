// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Nexus_GameOverlay.h"

#include "CommonTextBlock.h"
#include "GameInstances/Nexus_GameInstance.h"
#include "GameState/Nexus_GameState.h"
#include "Subsystems/Nexus_SettingsSubsystem.h"


void UNexus_GameOverlay::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ANexus_GameState* temp = Cast<ANexus_GameState>(GetWorld()->GetGameState()))
	{
		temp->OnCounterTick.AddUniqueDynamic(this, &UNexus_GameOverlay::OnTickEvent);
	}

	if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
	{
		if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
		{
			this->ActualTime->SetText(FText::FromString(FString::FromInt(SettingsSubsystem->GetTimeLimitIndexSetting())));
		}
	}
}

void UNexus_GameOverlay::OnTickEvent(const int32 RemainingTimer)
{
	this->ActualTime->SetText(FText::FromString(FString::FromInt(RemainingTimer)));
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("asdasdjnk")));
	//}

}
