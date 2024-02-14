// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "UENUMS/ActualPlayer.h"
#include "USTRUCT/PlayerInfo.h"
#include "Nexus_GameState.generated.h"

/**
 * 
 */
enum class EPlayerEnum :uint8;


DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerIsDeadEvent, EPlayerEnum);
DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerGotDamageEvent, EPlayerEnum, float);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDecrementTimer, int32, remainingTime);

UCLASS()
class PROJECT_NEXUS_API ANexus_GameState : public AGameState {
	GENERATED_BODY()

public:
	ANexus_GameState();

	virtual void BeginPlay() override;
	void StartNewGame();
	
	int32 GetRemainingTime() const;
	void SetRemainingTime(const int32 Duration);

	FOnDecrementTimer OnCounterTick;
	void DecrementRemainingTime();

	FPlayerGotDamageEvent PlayerGotDamage;
	FPlayerIsDeadEvent PlayerReachedZeroHealth;

	UFUNCTION(BlueprintCallable)
	void RefreshHealth(EPlayerEnum HitEnemy, float DamageValue);

private:
	int32 RemainingGameTime;

	UPROPERTY()
	FPlayerInfo PlayerOne;
	
	UPROPERTY()
	FPlayerInfo PlayerTwo;

};
