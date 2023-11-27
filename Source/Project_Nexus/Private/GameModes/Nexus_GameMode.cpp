// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/Nexus_GameMode.h"

#include "GameInstances/Nexus_GameInstance.h"
#include "GameState/Nexus_GameState.h"
#include "Subsystems/Nexus_SettingsSubsystem.h"


void ANexus_GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
	{
		if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
		{
			this->GameDurationInSeconds = SettingsSubsystem->GetTimeLimitSetting();
			this->MaxRounds = SettingsSubsystem->GetNumberOfRoundsSetting();
		}
	}
	
	this->GameState = Cast<ANexus_GameState>(GetWorld()->GetGameState());

	if (this->GameState)
	{
		this->GameState->ReductionOfLifeEvent.AddUObject(this, &ANexus_GameMode::CheckIfDeath);
	}
	
}

void ANexus_GameMode::StartMatch() {
	Super::StartMatch();

	if(GameState){
		if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
		{
			if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
			{
				this->GameState->SetRemainingTime(SettingsSubsystem->GetTimeLimitSetting());
			}
		}
		
		
	
		this->GetWorldTimerManager().SetTimer(this->TH_CountDown, this, &ANexus_GameMode::CountDown, 1.0f, true, 1.0f);
	}
}

void ANexus_GameMode::CountDown() {
	if (this->GameState->GetRemainingTime() == 0) {
		this->GetWorldTimerManager().ClearTimer(this->TH_CountDown);
		return;
	}
	
	this->GameState->DecrementRemainingTime();
}

void ANexus_GameMode::CheckIfDeath(EPlayerEnum Player) {
	
}

