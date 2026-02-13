// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Components/GameStateComponent.h"
#include "LoadingProcessInterface.h"

#include "ScWExperienceManagerComponent.generated.h"

#define MODULE_API SCWGAMECORE_API

namespace UE::GameFeatures { struct FResult; }

class UScWExperience;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnScWExperienceLoaded, const UScWExperience* /*Experience*/);

enum class EScWExperienceLoadState
{
	Unloaded,
	Loading,
	LoadingGameFeatures,
	LoadingChaosTestingDelay,
	ExecutingActions,
	Loaded,
	Deactivating
};

UCLASS(MinimalAPI)
class UScWExperienceManagerComponent final : public UGameStateComponent, public ILoadingProcessInterface
{
	GENERATED_BODY()

public:

	MODULE_API UScWExperienceManagerComponent(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

	//~UActorComponent interface
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of UActorComponent interface

	//~ILoadingProcessInterface interface
	MODULE_API virtual bool ShouldShowLoadingScreen(FString& OutReason) const override;
	//~End of ILoadingProcessInterface

	// Tries to set the current experience, either a UI or gameplay one
	MODULE_API void SetCurrentExperience(FPrimaryAssetId ExperienceId);

	// Ensures the delegate is called once the experience has been loaded,
	// before others are called.
	// However, if the experience has already loaded, calls the delegate immediately.
	MODULE_API void CallOrRegister_OnExperienceLoaded_HighPriority(FOnScWExperienceLoaded::FDelegate&& Delegate);

	// Ensures the delegate is called once the experience has been loaded
	// If the experience has already loaded, calls the delegate immediately
	MODULE_API void CallOrRegister_OnExperienceLoaded(FOnScWExperienceLoaded::FDelegate&& Delegate);

	// Ensures the delegate is called once the experience has been loaded
	// If the experience has already loaded, calls the delegate immediately
	MODULE_API void CallOrRegister_OnExperienceLoaded_LowPriority(FOnScWExperienceLoaded::FDelegate&& Delegate);

	// This returns the current experience if it is fully loaded, asserting otherwise
	// (i.e., if you called it too soon)
	MODULE_API const UScWExperience* GetCurrentExperienceChecked() const;

	// Returns true if the experience is fully loaded
	MODULE_API bool IsExperienceLoaded() const;

private:
	UFUNCTION()
	void OnRep_CurrentExperience();

	void StartExperienceLoad();
	void OnExperienceLoadComplete();
	void OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result);
	void OnExperienceFullLoadCompleted();

	void OnActionDeactivationCompleted();
	void OnAllActionsDeactivated();

private:
	UPROPERTY(ReplicatedUsing=OnRep_CurrentExperience)
	TObjectPtr<const UScWExperience> CurrentExperience;

	EScWExperienceLoadState LoadState = EScWExperienceLoadState::Unloaded;

	int32 NumGameFeaturePluginsLoading = 0;
	TArray<FString> GameFeaturePluginURLs;

	int32 NumObservedPausers = 0;
	int32 NumExpectedPausers = 0;

	/**
	 * Delegate called when the experience has finished loading just before others
	 * (e.g., subsystems that set up for regular gameplay)
	 */
	FOnScWExperienceLoaded OnExperienceLoaded_HighPriority;

	/** Delegate called when the experience has finished loading */
	FOnScWExperienceLoaded OnExperienceLoaded;

	/** Delegate called when the experience has finished loading */
	FOnScWExperienceLoaded OnExperienceLoaded_LowPriority;
};

#undef MODULE_API
