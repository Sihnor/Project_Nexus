#pragma once
#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EAllTimeLimitsEnum : uint8 {
	none,
	first = 50,
	second = 60,
	third = 90,
	fourth = 120,
	fifth = 150,
};