// Scientific Ways

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/EngineSubsystem.h"

#include "ScWExperienceSubsystem.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *	Subsystem for experiences - primarily for arbitration between multiple PIE sessions
 */
UCLASS(MinimalAPI)
class UScWExperienceSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	MODULE_API void OnPlayInEditorBegun();

	static void NotifyOfPluginActivation(const FString PluginURL);
	static bool RequestToDeactivatePlugin(const FString PluginURL);
#else
	static void NotifyOfPluginActivation(const FString PluginURL) {}
	static bool RequestToDeactivatePlugin(const FString PluginURL) { return true; }
#endif

private:
	// The map of requests to active count for a given game feature plugin
	// (to allow first in, last out activation management during PIE)
	TMap<FString, int32> GameFeaturePluginRequestCountMap;
};

#undef MODULE_API
