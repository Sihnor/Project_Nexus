#pragma once
#include <CoreMinimal.h>
//#include "UENUMS/ActualPlayer.h"
//#include "UENUMS/AllFighters.h"
#include "PlayerSelect.generated.h"

enum class EPlayerEnum : uint8;
enum class EAllFighterEnum : uint8;

USTRUCT(BlueprintType)
struct FPlayerSelect
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	EPlayerEnum Player;
	
	UPROPERTY(BlueprintReadWrite)
	EAllFighterEnum Fighter;
	
};
	