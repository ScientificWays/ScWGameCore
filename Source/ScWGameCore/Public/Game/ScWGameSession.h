// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWGameSession.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Game Session"))
class AScWGameSession : public AGameSession
{
	GENERATED_BODY()
	
};

#undef MODULE_API
