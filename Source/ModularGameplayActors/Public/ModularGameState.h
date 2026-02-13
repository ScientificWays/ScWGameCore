// Scientific Ways

#pragma once

#include "GameFramework/GameState.h"

#include "ModularGameState.generated.h"

#define MODULE_API MODULARGAMEPLAYACTORS_API

class UObject;

/** Pair this with a ModularGameModeBase */
UCLASS(MinimalAPI, Blueprintable)
class AModularGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	//~ Begin AActor interface
	MODULE_API virtual void PreInitializeComponents() override;
	MODULE_API virtual void BeginPlay() override;
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor interface
};


/** Pair this with a ModularGameState */
UCLASS(MinimalAPI, Blueprintable)
class AModularGameState : public AGameState
{
	GENERATED_BODY()

public:
	//~ Begin AActor interface
	MODULE_API virtual void PreInitializeComponents() override;
	MODULE_API virtual void BeginPlay() override;
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor interface

protected:
	//~ Begin AGameState interface
	MODULE_API virtual void HandleMatchHasStarted() override;
	//~ Begin AGameState interface
};

#undef MODULE_API
