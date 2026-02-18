// Scientific Ways

#pragma once

#include "CommonRotator.h"

#include "GameSettingRotator.generated.h"

#define MODULE_API GAMESETTINGS_API

class UObject;

/**
 * 
 */
UCLASS(MinimalAPI, Abstract, meta = (Category = "Settings", DisableNativeTick))
class UGameSettingRotator : public UCommonRotator
{
	GENERATED_BODY()

public:
	MODULE_API UGameSettingRotator(const FObjectInitializer& Initializer);

	MODULE_API void SetDefaultOption(int32 DefaultOptionIndex);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Events, meta = (DisplayName = "On Default Option Specified"))
	MODULE_API void BP_OnDefaultOptionSpecified(int32 DefaultOptionIndex);
};

#undef MODULE_API
