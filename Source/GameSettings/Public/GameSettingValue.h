// Scientific Ways

#pragma once

#include "GameSetting.h"

#include "GameSettingValue.generated.h"

#define MODULE_API GAMESETTINGS_API

class UObject;

//--------------------------------------
// UGameSettingValue
//--------------------------------------

/**
 * The base class for all settings that are conceptually a value, that can be 
 * changed, and thus reset or restored to their initial value.
 */
UCLASS(MinimalAPI, Abstract)
class UGameSettingValue : public UGameSetting
{
	GENERATED_BODY()

public:
	MODULE_API UGameSettingValue();

	/** Stores an initial value for the setting.  This will be called on initialize, but should also be called if you 'apply' the setting. */
	MODULE_API virtual void StoreInitial() PURE_VIRTUAL(, );

	/** Resets the property to the default. */
	MODULE_API virtual void ResetToDefault() PURE_VIRTUAL(, );

	/** Restores the setting to the initial value, this is the value when you open the settings before making any tweaks. */
	MODULE_API virtual void RestoreToInitial() PURE_VIRTUAL(, );

protected:
	MODULE_API virtual void OnInitialized() override;
};

#undef MODULE_API
