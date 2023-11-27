#pragma once
#include "CoreMinimal.h"
#include "PlayerInformationStruct.generated.h"

enum class EPlayerEnum : uint8;

USTRUCT()
struct FPlayerInformationStruct {
	GENERATED_BODY()

	EPlayerEnum PlayerNumber;

	FName PlayerName;
	FName CharacterName;
	float PlayerHealth;
	int8 RoundWon;
};