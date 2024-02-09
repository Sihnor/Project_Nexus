// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameModes/Nexus_GameMode.h"

#include "GameInstances/Nexus_GameInstance.h"
#include "GameState/Nexus_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/Nexus_SettingsSubsystem.h"


void ANexus_GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
	{
		if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
		{
			this->GameDurationInSeconds = SettingsSubsystem->GetTimeLimitIndexSetting();
			this->MaxRounds = SettingsSubsystem->GetNumberOfRoundsSetting();
			this->WinCondition = this->MaxRounds / 2 + 1;
		}
	}

	this->GameState = Cast<ANexus_GameState>(GetWorld()->GetGameState());

	if (this->GameState)
	{
		this->GameState->PlayerReachedZeroHealth.AddUObject(this, &ANexus_GameMode::PlayerIsDead);
		this->GameState->PlayerGotDamage.AddUObject(this, &ANexus_GameMode::UpdateHealthBar);
	}

	this->CurrentRound = 0;
	this->PlayerOneRoundWon = 0;
	this->PlayerTwoRoundWon = 0;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("BeginPlay")));
	}
}

void ANexus_GameMode::StartMatch()
{
	Super::StartMatch();

	OnStartMatch();
}

void ANexus_GameMode::OnStartMatch_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("OnStart Match")));
	}

	if (this->GameState)
	{
		if (UNexus_GameInstance* GameInstance = Cast<UNexus_GameInstance>(GetGameInstance()))
		{
			if (UNexus_SettingsSubsystem* SettingsSubsystem = GameInstance->GetSubsystem<UNexus_SettingsSubsystem>())
			{
				this->GameState->SetRemainingTime(SettingsSubsystem->GetTimeLimitSetting());
			}
		}

		this->GameState->StartNewGame();

		this->GetWorldTimerManager().SetTimer(this->TH_CountDown, this, &ANexus_GameMode::CountDown, 1.0f, true, 1.0f);
	}

	if (this->CurrentRound != 0)
	{
		UpdateHealthBar(EPlayerEnum::PlayerOne, 100.0f);
		UpdateHealthBar(EPlayerEnum::PlayerTwo, 100.0f);
	}
}

void ANexus_GameMode::EndMatch()
{
	Super::EndMatch();

	OnEndMatch();
}

void ANexus_GameMode::OnEndMatch_Implementation()
{
}

void ANexus_GameMode::CountDown()
{
	if (this->GameState->GetRemainingTime() == 0)
	{
		this->GetWorldTimerManager().ClearTimer(this->TH_CountDown);
		this->OnTimeIsUp();
	}

	OnCountDown(this->GameState->GetRemainingTime());

	this->GameState->DecrementRemainingTime();
}

void ANexus_GameMode::UpdateHealthBar_Implementation(EPlayerEnum HitEnemy, float DamageValue)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("->PlayerTwo.CurrentPoint %f"), DamageValue));
	}
}

void ANexus_GameMode::OnPlayerIsDead_Implementation(EPlayerEnum Player)
{
}

void ANexus_GameMode::PlayerIsDead(EPlayerEnum Player)
{
	this->GetWorldTimerManager().ClearTimer(this->TH_CountDown);

	switch (Player)
	{
	case EPlayerEnum::PlayerOne:
		this->AddPlayerOneRoundWon(EPlayerEnum::PlayerTwo);
		break;
	case EPlayerEnum::PlayerTwo:
		this->AddPlayerOneRoundWon(EPlayerEnum::PlayerOne);
		break;
	}

	OnPlayerIsDead(Player);
}

void ANexus_GameMode::OnCountDown_Implementation(int RemainingTime)
{
}

void ANexus_GameMode::OnTimeIsUp_Implementation()
{
}

bool ANexus_GameMode::CheckIfGameIsWon()
{
	if (PlayerOneRoundWon == WinCondition || PlayerTwoRoundWon == WinCondition)
	{
		return true;
	}
	return false;
}

void ANexus_GameMode::AddPlayerOneRoundWon(EPlayerEnum Player)
{
	switch (Player)
	{
		case EPlayerEnum::PlayerOne:
			this->PlayerOneRoundWon++;
			break;
		case EPlayerEnum::PlayerTwo:
			this->PlayerTwoRoundWon++;
			break;
	default: ;
	}
}
