// Scientific Ways

#pragma once

#include "GameFramework/PlayerState.h"

#include "ModularPlayerState.generated.h"

#define MODULE_API MODULARGAMEPLAYACTORS_API

namespace EEndPlayReason { enum Type : int; }

class UObject;

/** Minimal class that supports extension by game feature plugins */
UCLASS(MinimalAPI, Blueprintable)
class AModularPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	//~ Begin AActor interface
	MODULE_API virtual void PreInitializeComponents() override;
	MODULE_API virtual void BeginPlay() override;
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	MODULE_API virtual void Reset() override;
	//~ End AActor interface

protected:
	//~ Begin APlayerState interface
	MODULE_API virtual void CopyProperties(APlayerState* PlayerState);
	//~ End APlayerState interface
};

#undef MODULE_API
