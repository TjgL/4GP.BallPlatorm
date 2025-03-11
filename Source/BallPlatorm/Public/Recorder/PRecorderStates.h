#pragma once

UENUM(BlueprintType)
enum class ERecordState : uint8
{
	ERS_Stopped UMETA(DisplayName = "Stopped"),
	ERS_Recording UMETA(DisplayName = "Recording"),
	ERS_Rewinding UMETA(DisplayName = "Rewinding"),
};
