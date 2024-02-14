#pragma once
#include <CoreMinimal.h>
//#include "UENUMS/ActualPlayer.h"
//#include "UENUMS/AllFighters.h"
#include "PlayerInfo.generated.h"

enum class EPlayerEnum : uint8;
enum class EAllFighterEnum : uint8;

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	EPlayerEnum ActualPlayer;
	
	UPROPERTY(BlueprintReadOnly)
	float HealthPointMax = 100.0f;
	
	UPROPERTY(BlueprintReadOnly)
	float CurrentPoint = 100.0f;
	
};
	