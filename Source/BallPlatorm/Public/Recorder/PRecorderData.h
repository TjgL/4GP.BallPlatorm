#pragma once

#include "PRecorderData.generated.h"

USTRUCT(BlueprintType)
struct FPRecorderData
{
	GENERATED_BODY()

public:
	FVector Velocity;
	FVector AngularVelocityRadians;

	FVector Position;
	FRotator Rotation;
};
