// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/Nexus_GameMode.h"
#include "GameState/Nexus_GameState.h"

ANexus_GameMode::ANexus_GameMode() {
	this->GameDurationInSeconds = 150;

	this->GameState = this->GetGameState<ANexus_GameState>();
	
}

void ANexus_GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (this->GameState)
	{
		this->GameState->ReductionOfLifeEvent.AddUObject(this, &ANexus_GameMode::CheckIfDeath);
	}
	
}

void ANexus_GameMode::StartMatch() {
	Super::StartMatch();

	if(GameState){

		this->GameState->SetRemainingTime(150);
	
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

