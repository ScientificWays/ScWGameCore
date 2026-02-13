// Scientific Ways

#pragma once

#include "UserSettings/EnhancedInputUserSettings.h"

#include "ScWPlayerMappableKeyProfile.generated.h"

#define MODULE_API SCWGAMECORE_API

UCLASS(MinimalAPI)
class UScWPlayerMappableKeyProfile : public UEnhancedPlayerMappableKeyProfile
{
	GENERATED_BODY()

protected:

	//~ Begin UEnhancedPlayerMappableKeyProfile interface
	MODULE_API virtual void EquipProfile() override;
	MODULE_API virtual void UnEquipProfile() override;
	//~ End UEnhancedPlayerMappableKeyProfile interface
};

#undef MODULE_API
