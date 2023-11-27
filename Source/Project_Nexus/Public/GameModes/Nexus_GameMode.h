// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Nexus_GameMode.generated.h"

/**
 * 
 */


enum class EPlayerEnum : uint8;

UCLASS()
class PROJECT_NEXUS_API ANexus_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void StartMatch() override;
	
	void CountDown();

	//class ANexus_GameState* GameState;

	TObjectPtr<class ANexus_GameState> GameState;

	void CheckIfDeath(EPlayerEnum Player);

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int32 GameDurationInSeconds;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int32 MaxRounds;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int32 WinCondition;

	UPROPERTY()
	FTimerHandle TH_CountDown;
};
