// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "UENUMS/ActualPlayer.h"
#include "Nexus_GameState.generated.h"

/**
 * 
 */
enum class EPlayerEnum :uint8;


DECLARE_MULTICAST_DELEGATE_OneParam(FReductionOfLifeEvent, EPlayerEnum);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDecrementTimer, int32, remainingTime);

UCLASS()
class PROJECT_NEXUS_API ANexus_GameState : public AGameState {
	GENERATED_BODY()

public:
	ANexus_GameState();

	virtual void BeginPlay() override;
	
	int32 GetRemainingTime() const;
	void SetRemainingTime(const int32 Duration);

	FOnDecrementTimer OnCounterTick;
	void DecrementRemainingTime();
	
	FReductionOfLifeEvent ReductionOfLifeEvent;


	void RefreshHealth(EPlayerEnum HitEnemy);

private:
	int32 RemainingGameTime;

	UPROPERTY()
	EPlayerEnum PlayerOne;
	
	UPROPERTY()
	EPlayerEnum PlayerTwo;
};
