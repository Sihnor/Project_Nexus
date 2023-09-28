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
	void BeginPlay() override;
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 GameDurationInSeconds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTimerHandle TH_CountDown;
};
