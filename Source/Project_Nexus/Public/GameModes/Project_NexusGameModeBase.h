// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Project_NexusGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_NEXUS_API AProject_NexusGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AProject_NexusGameModeBase();

	void CountDown();
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int32 GameDurationInSeconds;

	UPROPERTY()
	FTimerHandle TH_CountDown;
};
