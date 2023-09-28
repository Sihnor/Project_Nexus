// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/Project_NexusGameModeBase.h"


AProject_NexusGameModeBase::AProject_NexusGameModeBase()
{
	this->GameDurationInSeconds = 150;
}

void AProject_NexusGameModeBase::CountDown()
{
	if (this->GameDurationInSeconds == 0)
	{
		return;
	}

	this->GameDurationInSeconds--;
	UE_LOG(LogTemp,Warning, TEXT("%i"), this->GameDurationInSeconds);
	
}

void AProject_NexusGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	this->GetWorldTimerManager().SetTimer(this->TH_CountDown, this, &AProject_NexusGameModeBase::CountDown, 1.0f, true, 1.0f);
}
