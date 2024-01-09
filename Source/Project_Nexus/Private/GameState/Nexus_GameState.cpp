// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/Nexus_GameState.h"
#include "UENUMS/ActualPlayer.h"

ANexus_GameState::ANexus_GameState() {
	this->RemainingGameTime = 0;
}

void ANexus_GameState::BeginPlay() {
	Super::BeginPlay();
}

int32 ANexus_GameState::GetRemainingTime() const {
	return this->RemainingGameTime;
}

void ANexus_GameState::SetRemainingTime(const int32 Duration) {
	this->RemainingGameTime = Duration;
}

void ANexus_GameState::DecrementRemainingTime() {
	this->RemainingGameTime--;

	this->OnCounterTick.Broadcast(this->RemainingGameTime);
}

void ANexus_GameState::RefreshHealth(EPlayerEnum HitEnemy, float DamageValue) {

	this->ReductionOfLifeEvent.Broadcast(HitEnemy, DamageValue);
}
