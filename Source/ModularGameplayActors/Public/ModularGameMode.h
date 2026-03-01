// Scientific Ways

#pragma once

#include "GameFramework/GameMode.h"

#include "ModularGameMode.generated.h"

#define MODULE_API MODULARGAMEPLAYACTORS_API

class UObject;

/** Pair this with a ModularGameStateBase */
UCLASS(MinimalAPI, Blueprintable)
class AModularGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	MODULE_API AModularGameModeBase(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());
};

/** Pair this with a ModularGameState */
UCLASS(MinimalAPI, Blueprintable)
class AModularGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	MODULE_API AModularGameMode(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());
};

#undef MODULE_API
