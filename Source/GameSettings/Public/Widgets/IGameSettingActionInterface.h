// Scientific Ways

#pragma once

#include "GameplayTagContainer.h"
#include "UObject/Interface.h"

#include "IGameSettingActionInterface.generated.h"

#define MODULE_API GAMESETTINGS_API

class UGameSetting;
class UObject;
struct FFrame;

UINTERFACE(MinimalAPI, meta = (BlueprintType))
class UGameSettingActionInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IGameSettingActionInterface
{
	GENERATED_BODY()

public:
	/** */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	MODULE_API bool ExecuteActionForSetting(FGameplayTag ActionTag, UGameSetting* InSetting);
};

#undef MODULE_API
