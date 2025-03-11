#pragma once

UENUM(BlueprintType)
enum class ERecordState : uint8
{
	ERS_Stopped,
	ERS_Recording,
	ERS_Rewinding
};
