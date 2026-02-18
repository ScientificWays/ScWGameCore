// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWWorldSettings.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * The default world settings object, used primarily to set the default experience to use when playing on this map
 */
UCLASS(MinimalAPI)
class AScWWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:

	MODULE_API AScWWorldSettings(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
	MODULE_API virtual void CheckForErrors() override; // AActor
#endif

public:
	// Returns the default experience to use when a server opens this map if it is not overridden by the user-facing experience
	MODULE_API FPrimaryAssetId GetDefaultExperience() const;

protected:

	// The default experience to use when a server opens this map if it is not overridden by the user-facing experience
	UPROPERTY(Category = "GameMode", EditDefaultsOnly)
	TSoftObjectPtr<class UScWExperience> DefaultExperience;

public:

#if WITH_EDITORONLY_DATA
	// Is this level part of a front-end or other standalone experience?
	// When set, the net mode will be forced to Standalone when you hit Play in the editor
	UPROPERTY(Category = "PIE", EditDefaultsOnly)
	bool ForceStandaloneNetMode = false;
#endif
};

#undef MODULE_API
