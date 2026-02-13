// Scientific Ways

#pragma once

#include "GameFramework/Pawn.h"

#include "ModularPawn.generated.h"

#define MODULE_API MODULARGAMEPLAYACTORS_API

class UObject;

/** Minimal class that supports extension by game feature plugins */
UCLASS(MinimalAPI, Blueprintable)
class AModularPawn : public APawn
{
	GENERATED_BODY()

public:
	//~ Begin AActor interface
	MODULE_API virtual void PreInitializeComponents() override;
	MODULE_API virtual void BeginPlay() override;
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End AActor interface

};

#undef MODULE_API
