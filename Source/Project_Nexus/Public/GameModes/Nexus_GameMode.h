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
	virtual void EndMatch() override;
	
	void CountDown();

	//class ANexus_GameState* GameState;

	TObjectPtr<class ANexus_GameState> GameState;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnStartMatch();
	virtual void OnStartMatch_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEndMatch();
	virtual void OnEndMatch_Implementation();
	
	UFUNCTION(BlueprintNativeEvent)
	void UpdateHealthBar(EPlayerEnum HitEnemy, float DamageValue);
	virtual void UpdateHealthBar_Implementation(EPlayerEnum HitEnemy, float DamageValue);

	UFUNCTION(BlueprintNativeEvent)
	void OnPlayerIsDead(EPlayerEnum Player);
	virtual void OnPlayerIsDead_Implementation(EPlayerEnum Player);
	
	void PlayerIsDead(EPlayerEnum Player);

	UFUNCTION(BlueprintNativeEvent)
	void OnCountDown(int RemainingTime);
	virtual void OnCountDown_Implementation(int RemainingTime);

	UFUNCTION(BlueprintNativeEvent)
	void OnTimeIsUp();
	virtual void OnTimeIsUp_Implementation();
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	bool DebugTimer = false;


private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int32 GameDurationInSeconds;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int32 MaxRounds;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int32 WinCondition;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	FTimerHandle TH_CountDown;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	int CurrentRound;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	int PlayerOneRoundWon;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	int PlayerTwoRoundWon;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(AllowPrivateAccess = "true"))
	bool CheckIfGameIsWon();

	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = "true"))
	void AddPlayerOneRoundWon(EPlayerEnum Player);

protected:
	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = "true"))
	void StartTimer();

	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = "true"))
	void PauseTimer();

	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = "true"))
	void ResumeTimer();

	UFUNCTION(BlueprintCallable, meta=(AllowPrivateAccess = "true"))
	void StopTimer();
};


