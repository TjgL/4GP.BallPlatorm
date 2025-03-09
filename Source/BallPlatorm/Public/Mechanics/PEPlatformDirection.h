#pragma once

#include "PEPlatformDirection.generated.h"

UENUM(BlueprintType)
enum class EPlatformDirection : uint8
{
	Stop = 0,
	Forward = 1,
	Back = 2,
};
