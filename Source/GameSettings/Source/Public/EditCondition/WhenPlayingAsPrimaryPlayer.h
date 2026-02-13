// Scientific Ways

#pragma once

#include "GameSettingFilterState.h"

#define MODULE_API GAMESETTINGS_API

class ULocalPlayer;


class FWhenPlayingAsPrimaryPlayer : public FGameSettingEditCondition
{
public:
	static MODULE_API TSharedRef<FWhenPlayingAsPrimaryPlayer> Get();

	MODULE_API virtual void GatherEditState(const ULocalPlayer* InLocalPlayer, FGameSettingEditableState& InOutEditState) const override;
};

#undef MODULE_API
