// Scientific Ways

#pragma once

#include "Engine/DataAsset.h"

#include "ScWAimSensitivityData.generated.h"

#define MODULE_API SCWGAMECORE_API

UENUM(BlueprintType)
enum class EScWGamepadSensitivity : uint8
{
	Invalid = 0		UMETA(Hidden),

	Slow			UMETA(DisplayName = "01 - Slow"),
	SlowPlus		UMETA(DisplayName = "02 - Slow+"),
	SlowPlusPlus	UMETA(DisplayName = "03 - Slow++"),
	Normal			UMETA(DisplayName = "04 - Normal"),
	NormalPlus		UMETA(DisplayName = "05 - Normal+"),
	NormalPlusPlus	UMETA(DisplayName = "06 - Normal++"),
	Fast			UMETA(DisplayName = "07 - Fast"),
	FastPlus		UMETA(DisplayName = "08 - Fast+"),
	FastPlusPlus	UMETA(DisplayName = "09 - Fast++"),
	Insane			UMETA(DisplayName = "10 - Insane"),

	MAX				UMETA(Hidden),
};

class UObject;

/** Defines a set of gamepad sensitivity to a float value. */
UCLASS(MinimalAPI, BlueprintType, Const, Meta = (DisplayName = "ScW Aim Sensitivity Data", ShortTooltip = "Data asset used to define a map of Gamepad Sensitivty to a float value."))
class UScWAimSensitivityData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	MODULE_API UScWAimSensitivityData(const FObjectInitializer& InObjectInitializer);
	
	MODULE_API const float SensitivtyEnumToFloat(const EScWGamepadSensitivity InSensitivity) const;
	
protected:
	/** Map of SensitivityMap settings to their corresponding float */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EScWGamepadSensitivity, float> SensitivityMap;
};

#undef MODULE_API
