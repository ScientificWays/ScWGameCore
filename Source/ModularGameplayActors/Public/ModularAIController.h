// Scientific Ways

#pragma once

#include "AIController.h"

#include "ModularAIController.generated.h"

#define MODULE_API MODULARGAMEPLAYACTORS_API

class UObject;

/** Minimal class that supports extension by game feature plugins */
UCLASS(MinimalAPI, Blueprintable)
class AModularAIController : public AAIController
{
	GENERATED_BODY()

public:
	//~ Begin AActor Interface
	MODULE_API virtual void PreInitializeComponents() override;
	MODULE_API virtual void BeginPlay() override;
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor Interface
};

#undef MODULE_API
