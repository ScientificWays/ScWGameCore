// Scientific Ways

#pragma once

#include "GameFeatureAction.h"
#include "GameFeaturesSubsystem.h"

#include "ScWGFA_WorldActionBase.generated.h"

#define MODULE_API SCWGAMECORE_API

class FDelegateHandle;
class UGameInstance;
class UObject;
struct FGameFeatureActivatingContext;
struct FGameFeatureDeactivatingContext;
struct FGameFeatureStateChangeContext;
struct FWorldContext;

/**
 * Base class for GameFeatureActions that wish to do something world specific.
 */
UCLASS(MinimalAPI, Abstract)
class UScWGFA_WorldActionBase : public UGameFeatureAction
{
	GENERATED_BODY()

public:
	//~ Begin UGameFeatureAction interface
	MODULE_API virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;
	MODULE_API virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
	//~ End UGameFeatureAction interface

private:
	void HandleGameInstanceStart(UGameInstance* GameInstance, FGameFeatureStateChangeContext ChangeContext);

	/** Override with the action-specific logic */
	virtual void AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext) PURE_VIRTUAL(UScWGFA_WorldActionBase::AddToWorld,);

private:
	TMap<FGameFeatureStateChangeContext, FDelegateHandle> GameInstanceStartHandles;
};

#undef MODULE_API
