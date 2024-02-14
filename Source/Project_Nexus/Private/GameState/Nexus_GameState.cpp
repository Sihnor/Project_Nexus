// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/Nexus_GameState.h"
#include "UENUMS/ActualPlayer.h"

ANexus_GameState::ANexus_GameState()
{
	this->RemainingGameTime = 0;

	this->PlayerOne.HealthPointMax = 100.0f;
	this->PlayerTwo.HealthPointMax = 100.0f;
}

void ANexus_GameState::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerOne.ActualPlayer = EPlayerEnum::PlayerOne;
	this->PlayerTwo.ActualPlayer = EPlayerEnum::PlayerTwo;

	
}

void ANexus_GameState::StartNewGame()
{
	this->PlayerOne.CurrentPoint = this->PlayerOne.HealthPointMax;
	this->PlayerTwo.CurrentPoint = this->PlayerTwo.HealthPointMax;
}

int32 ANexus_GameState::GetRemainingTime() const
{
	return this->RemainingGameTime;
}

void ANexus_GameState::SetRemainingTime(const int32 Duration)
{
	this->RemainingGameTime = Duration;
}

void ANexus_GameState::DecrementRemainingTime()
{
	this->RemainingGameTime--;

	this->OnCounterTick.Broadcast(this->RemainingGameTime);
}

void ANexus_GameState::RefreshHealth(EPlayerEnum HitEnemy, float DamageValue)
{
	if (DamageValue <= 0.0f)
	{
		return;
	}
	
	if (HitEnemy == EPlayerEnum::PlayerOne)
	{
		this->PlayerOne.CurrentPoint -= DamageValue;
		this->PlayerGotDamage.Broadcast(HitEnemy, this->PlayerOne.CurrentPoint);

		if (this->PlayerOne.CurrentPoint > 0.0f) return;
		this->PlayerReachedZeroHealth.Broadcast(HitEnemy);
	}

	if (HitEnemy == EPlayerEnum::PlayerTwo)
	{
		this->PlayerTwo.CurrentPoint -= DamageValue;			
		this->PlayerGotDamage.Broadcast(HitEnemy, this->PlayerTwo.CurrentPoint);

		if (this->PlayerTwo.CurrentPoint > 0.0f) return;
		this->PlayerReachedZeroHealth.Broadcast(HitEnemy);
	}
	
	

	
	
}
