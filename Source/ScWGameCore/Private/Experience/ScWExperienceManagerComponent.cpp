// Scientific Ways

#include "Experience/ScWExperienceManagerComponent.h"

#include "Experience/ScWExperience.h"
#include "Experience/ScWExperienceActionSet.h"
#include "Experience/ScWExperienceSubsystem.h"

#include "Development/ScWLogsFunctionLibrary.h"

#include "Settings/ScWSettingsLocal.h"

#include "TimerManager.h"
#include "GameFeatureAction.h"
#include "GameFeaturesSubsystem.h"
#include "GameFeaturesSubsystemSettings.h"

#include "Engine/World.h"
#include "Engine/AssetManager.h"

#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWExperienceManagerComponent)

//@TODO: Async load the experience definition itself
//@TODO: Handle failures explicitly (go into a 'completed but failed' state rather than check()-ing)
//@TODO: Do the action phases at the appropriate times instead of all at once
//@TODO: Think about what deactivation/cleanup means for preloaded assets
// (for a client moving from experience to experience we actually want to diff the requirements and only unload some, not unload everything for them to just be immediately reloaded)
//@TODO: Handle both built-in and URL-based plugins (search for colon?)

namespace ScWConsoleVariables
{
	static float ExperienceLoadRandomDelayMin = 0.0f;
	static FAutoConsoleVariableRef CVarExperienceLoadRandomDelayMin(
		TEXT("scw.chaos.ExperienceDelayLoad.MinSecs"),
		ExperienceLoadRandomDelayMin,
		TEXT("This value (in seconds) will be added as a delay of load completion of the experience (along with the random value scw.chaos.ExperienceDelayLoad.RandomSecs)"),
		ECVF_Default);

	static float ExperienceLoadRandomDelayRange = 0.0f;
	static FAutoConsoleVariableRef CVarExperienceLoadRandomDelayRange(
		TEXT("scw.chaos.ExperienceDelayLoad.RandomSecs"),
		ExperienceLoadRandomDelayRange,
		TEXT("A random amount of time between 0 and this value (in seconds) will be added as a delay of load completion of the experience (along with the fixed value scw.chaos.ExperienceDelayLoad.MinSecs)"),
		ECVF_Default);

	float GetExperienceLoadDelayDuration()
	{
		return FMath::Max(0.0f, ExperienceLoadRandomDelayMin + FMath::FRand() * ExperienceLoadRandomDelayRange);
	}
}

namespace
{
	const TCHAR* ExperienceLoadStateToString(const EScWExperienceLoadState InLoadState)
	{
		switch (InLoadState)
		{
			case EScWExperienceLoadState::Unloaded: return TEXT("Unloaded");
			case EScWExperienceLoadState::Loading: return TEXT("Loading");
			case EScWExperienceLoadState::LoadingGameFeatures: return TEXT("LoadingGameFeatures");
			case EScWExperienceLoadState::LoadingChaosTestingDelay: return TEXT("LoadingChaosTestingDelay");
			case EScWExperienceLoadState::ExecutingActions: return TEXT("ExecutingActions");
			case EScWExperienceLoadState::Loaded: return TEXT("Loaded");
			case EScWExperienceLoadState::Deactivating: return TEXT("Deactivating");
		}
		return TEXT("Unknown");
	}

	FString GetExperienceIdString(const UScWExperience* InExperience)
	{
		return InExperience ? InExperience->GetPrimaryAssetId().ToString() : TEXT("None");
	}

	void LogExperienceManagerLifecycle(const UObject* InContext, const FString& InMessage)
	{
		UScWLogsFunctionLibrary::Log_Experience(InContext, InMessage, EBlueprintLogVerbosity::Log, true, false);
	}
}

UScWExperienceManagerComponent::UScWExperienceManagerComponent(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	SetIsReplicatedByDefault(true);
}

#if WITH_EDITOR
#include "Editor.h"
#include "Misc/MessageDialog.h"
#endif

void UScWExperienceManagerComponent::SetCurrentExperience(FPrimaryAssetId ExperienceId)
{
	/*UAssetManager& AssetManager = UAssetManager::Get();
	FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(ExperienceId);
	TSubclassOf<UScWExperience> AssetClass = Cast<UClass>(AssetPath.TryLoad());
	check(AssetClass);
	const UScWExperience* Experience = GetDefault<UScWExperience>(AssetClass);

	check(Experience != nullptr);
	check(CurrentExperience == nullptr);
	CurrentExperience = Experience;
	StartExperienceLoad();*/

	ensureReturn(LoadState == EScWExperienceLoadState::Unloaded);
	ensureReturn(CurrentExperience == nullptr);
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.SetCurrentExperience: RequestedExperience=%s, LoadState=%s, Context=%s"),
		*ExperienceId.ToString(),
		ExperienceLoadStateToString(LoadState),
		*GetClientServerContextString(this)));

	// Sync load
	const auto AssetPath = UAssetManager::Get().GetPrimaryAssetPath(ExperienceId);
	const auto Experience = Cast<UScWExperience>(AssetPath.TryLoad());

#if WITH_EDITOR
	if (!Experience)
	{
		FMessageLog("PIE").Error()
			->AddToken(FTextToken::Create(FText::FromString("Experience not found. Aborting PIE."))
		);
		GEditor->RequestEndPlayMap();
		return;
	}
#endif
	check(Experience != nullptr);

	CurrentExperience = Experience;
	StartExperienceLoad();
}

void UScWExperienceManagerComponent::CallOrRegister_OnExperienceLoaded_HighPriority(FOnScWExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded_HighPriority.Add(MoveTemp(Delegate));
	}
}

void UScWExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(FOnScWExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}

void UScWExperienceManagerComponent::CallOrRegister_OnExperienceLoaded_LowPriority(FOnScWExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded_LowPriority.Add(MoveTemp(Delegate));
	}
}

const UScWExperience* UScWExperienceManagerComponent::GetCurrentExperienceChecked() const
{
	check(LoadState == EScWExperienceLoadState::Loaded);
	check(CurrentExperience != nullptr);
	return CurrentExperience;
}

bool UScWExperienceManagerComponent::IsExperienceLoaded() const
{
	return (LoadState == EScWExperienceLoadState::Loaded) && (CurrentExperience != nullptr);
}

void UScWExperienceManagerComponent::OnRep_CurrentExperience()
{
	ensureReturn(CurrentExperience);
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.OnRep_CurrentExperience: Experience=%s, LoadState=%s, Context=%s"),
		*GetExperienceIdString(CurrentExperience),
		ExperienceLoadStateToString(LoadState),
		*GetClientServerContextString(this)));
	StartExperienceLoad();
}

void UScWExperienceManagerComponent::StartExperienceLoad()
{
	ensureReturn(CurrentExperience);
	ensureReturn(LoadState == EScWExperienceLoadState::Unloaded);
	ensure(ActivatedActions.IsEmpty());
	ensure(NumGameFeaturePluginsDeactivating == 0);

	LoadState = EScWExperienceLoadState::Loading;
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.StartExperienceLoad: Experience=%s, LoadState=%s, Context=%s"),
		*GetExperienceIdString(CurrentExperience),
		ExperienceLoadStateToString(LoadState),
		*GetClientServerContextString(this)));

	UAssetManager& AssetManager = UAssetManager::Get();

	TSet<FPrimaryAssetId> BundleAssetList;
	TSet<FSoftObjectPath> RawAssetList;

	BundleAssetList.Add(CurrentExperience->GetPrimaryAssetId());
	for (const TObjectPtr<UScWExperienceActionSet>& ActionSet : CurrentExperience->ActionSets)
	{
		if (ActionSet != nullptr)
		{
			BundleAssetList.Add(ActionSet->GetPrimaryAssetId());
		}
	}

	// Load assets associated with the experience

	TArray<FName> BundlesToLoad;
	//BundlesToLoad.Add(FScWBundles::Equipped);

	//@TODO: Centralize this client/server stuff into the ScWAssetManager
	const ENetMode OwnerNetMode = GetOwner()->GetNetMode();
	const bool bLoadClient = GIsEditor || (OwnerNetMode != NM_DedicatedServer);
	const bool bLoadServer = GIsEditor || (OwnerNetMode != NM_Client);
	if (bLoadClient)
	{
		BundlesToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateClient);
	}
	if (bLoadServer)
	{
		BundlesToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateServer);
	}

	TSharedPtr<FStreamableHandle> BundleLoadHandle = nullptr;
	if (BundleAssetList.Num() > 0)
	{
		BundleLoadHandle = AssetManager.ChangeBundleStateForPrimaryAssets(BundleAssetList.Array(), BundlesToLoad, {}, false, FStreamableDelegate(), FStreamableManager::AsyncLoadHighPriority);
	}

	TSharedPtr<FStreamableHandle> RawLoadHandle = nullptr;
	if (RawAssetList.Num() > 0)
	{
		RawLoadHandle = AssetManager.LoadAssetList(RawAssetList.Array(), FStreamableDelegate(), FStreamableManager::AsyncLoadHighPriority, TEXT("StartExperienceLoad()"));
	}

	// If both async loads are running, combine them
	TSharedPtr<FStreamableHandle> Handle = nullptr;
	if (BundleLoadHandle.IsValid() && RawLoadHandle.IsValid())
	{
		Handle = AssetManager.GetStreamableManager().CreateCombinedHandle({ BundleLoadHandle, RawLoadHandle });
	}
	else
	{
		Handle = BundleLoadHandle.IsValid() ? BundleLoadHandle : RawLoadHandle;
	}

	FStreamableDelegate OnAssetsLoadedDelegate = FStreamableDelegate::CreateUObject(this, &ThisClass::OnExperienceLoadComplete);
	if (!Handle.IsValid() || Handle->HasLoadCompleted())
	{
		// Assets were already loaded, call the delegate now
		FStreamableHandle::ExecuteDelegate(OnAssetsLoadedDelegate);
	}
	else
	{
		Handle->BindCompleteDelegate(OnAssetsLoadedDelegate);

		Handle->BindCancelDelegate(FStreamableDelegate::CreateLambda([OnAssetsLoadedDelegate]()
			{
				OnAssetsLoadedDelegate.ExecuteIfBound();
			}));
	}

	// This set of assets gets preloaded, but we don't block the start of the experience based on it
	TSet<FPrimaryAssetId> PreloadAssetList;
	//@TODO: Determine assets to preload (but not blocking-ly)
	if (PreloadAssetList.Num() > 0)
	{
		AssetManager.ChangeBundleStateForPrimaryAssets(PreloadAssetList.Array(), BundlesToLoad, {});
	}
}

void UScWExperienceManagerComponent::OnExperienceLoadComplete()
{
	if ((LoadState != EScWExperienceLoadState::Loading) || (CurrentExperience == nullptr))
	{
		return;
	}

	// find the URLs for our GameFeaturePlugins - filtering out dupes and ones that don't have a valid mapping
	GameFeaturePluginURLs.Reset();

	auto CollectGameFeaturePluginURLs = [This=this](const UPrimaryDataAsset* Context, const TArray<FString>& FeaturePluginList)
	{
		for (const FString& PluginName : FeaturePluginList)
		{
			FString PluginURL;
			if (UGameFeaturesSubsystem::Get().GetPluginURLByName(PluginName, /*out*/ PluginURL))
			{
				This->GameFeaturePluginURLs.AddUnique(PluginURL);
			}
			else
			{
				ensureMsgf(false, TEXT("OnExperienceLoadComplete failed to find plugin URL from PluginName %s for experience %s - fix data, ignoring for this run"), *PluginName, *Context->GetPrimaryAssetId().ToString());
			}
		}

		// 		// Add in our extra plugin
		// 		if (!CurrentPlaylistData->GameFeaturePluginToActivateUntilDownloadedContentIsPresent.IsEmpty())
		// 		{
		// 			FString PluginURL;
		// 			if (UGameFeaturesSubsystem::Get().GetPluginURLByName(CurrentPlaylistData->GameFeaturePluginToActivateUntilDownloadedContentIsPresent, PluginURL))
		// 			{
		// 				GameFeaturePluginURLs.AddUnique(PluginURL);
		// 			}
		// 		}
	};

	CollectGameFeaturePluginURLs(CurrentExperience, CurrentExperience->GameFeaturesToEnable);
	for (const TObjectPtr<UScWExperienceActionSet>& ActionSet : CurrentExperience->ActionSets)
	{
		if (ActionSet != nullptr)
		{
			CollectGameFeaturePluginURLs(ActionSet, ActionSet->GameFeaturesToEnable);
		}
	}

	// Load and activate the features	
	NumGameFeaturePluginsLoading = GameFeaturePluginURLs.Num();
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.OnExperienceLoadComplete: Experience=%s, PluginsToLoad=%d, Context=%s"),
		*GetExperienceIdString(CurrentExperience),
		NumGameFeaturePluginsLoading,
		*GetClientServerContextString(this)));
	if (NumGameFeaturePluginsLoading > 0)
	{
		LoadState = EScWExperienceLoadState::LoadingGameFeatures;
		for (const FString& PluginURL : GameFeaturePluginURLs)
		{
			UScWExperienceSubsystem::NotifyOfPluginActivation(PluginURL);
			UGameFeaturesSubsystem::Get().LoadAndActivateGameFeaturePlugin(PluginURL, FGameFeaturePluginLoadComplete::CreateUObject(this, &ThisClass::OnGameFeaturePluginLoadComplete));
		}
	}
	else
	{
		OnExperienceFullLoadCompleted();
	}
}

void UScWExperienceManagerComponent::OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result)
{
	static_cast<void>(Result);

	if (LoadState != EScWExperienceLoadState::LoadingGameFeatures)
	{
		return;
	}

	ensureReturn(NumGameFeaturePluginsLoading > 0);

	// decrement the number of plugins that are loading
	NumGameFeaturePluginsLoading--;
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.OnGameFeaturePluginLoadComplete: RemainingPlugins=%d, Context=%s"),
		NumGameFeaturePluginsLoading,
		*GetClientServerContextString(this)));

	if (NumGameFeaturePluginsLoading == 0)
	{
		OnExperienceFullLoadCompleted();
	}
}

void UScWExperienceManagerComponent::ActivateExperienceActions()
{
	ensureReturn(CurrentExperience);

	if (!ensure(ActivatedActions.IsEmpty()))
	{
		ActivatedActions.Reset();
	}

	int32 NumActionsToActivate = CurrentExperience->Actions.Num();
	for (const TObjectPtr<UScWExperienceActionSet>& ActionSet : CurrentExperience->ActionSets)
	{
		if (ActionSet != nullptr)
		{
			NumActionsToActivate += ActionSet->Actions.Num();
		}
	}

	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.ActivateExperienceActions: Experience=%s, Actions=%d, Context=%s"),
		*GetExperienceIdString(CurrentExperience),
		NumActionsToActivate,
		*GetClientServerContextString(this)));

	ActivatedActions.Reserve(NumActionsToActivate);

	FGameFeatureActivatingContext Context;

	// Only apply to our specific world context if set
	const FWorldContext* ExistingWorldContext = GEngine->GetWorldContextFromWorld(GetWorld());
	if (ExistingWorldContext)
	{
		Context.SetRequiredWorldContextHandle(ExistingWorldContext->ContextHandle);
	}

	auto ActivateListOfActions = [this, &Context](const TArray<TObjectPtr<UGameFeatureAction>>& ActionList)
	{
		for (UGameFeatureAction* Action : ActionList)
		{
			if (Action != nullptr)
			{
				//@TODO: The fact that these don't take a world are potentially problematic in client-server PIE
				// The current behavior matches systems like gameplay tags where loading and registering apply to the entire process,
				// but actually applying the results to actors is restricted to a specific world
				Action->OnGameFeatureRegistering();
				Action->OnGameFeatureLoading();
				Action->OnGameFeatureActivating(Context);
				ActivatedActions.Add(Action);
			}
		}
	};

	ActivateListOfActions(CurrentExperience->Actions);
	for (const TObjectPtr<UScWExperienceActionSet>& ActionSet : CurrentExperience->ActionSets)
	{
		if (ActionSet != nullptr)
		{
			ActivateListOfActions(ActionSet->Actions);
		}
	}
}

void UScWExperienceManagerComponent::DeactivateExperienceActions(FGameFeatureDeactivatingContext& Context)
{
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.DeactivateExperienceActions: ActivatedActions=%d, Context=%s"),
		ActivatedActions.Num(),
		*GetClientServerContextString(this)));

	for (int32 ActionIndex = ActivatedActions.Num() - 1; ActionIndex >= 0; --ActionIndex)
	{
		if (UGameFeatureAction* Action = ActivatedActions[ActionIndex])
		{
			Action->OnGameFeatureDeactivating(Context);
			Action->OnGameFeatureUnregistering();
		}
	}

	ActivatedActions.Reset();
}

void UScWExperienceManagerComponent::DeactivateGameFeaturePlugins()
{
	TArray<FString> PluginsToDeactivate;
	PluginsToDeactivate.Reserve(GameFeaturePluginURLs.Num());

	for (int32 PluginIndex = GameFeaturePluginURLs.Num() - 1; PluginIndex >= 0; --PluginIndex)
	{
		const FString& PluginURL = GameFeaturePluginURLs[PluginIndex];
		if (UScWExperienceSubsystem::RequestToDeactivatePlugin(PluginURL))
		{
			PluginsToDeactivate.Add(PluginURL);
		}
	}

	GameFeaturePluginURLs.Reset();
	NumGameFeaturePluginsLoading = 0;
	NumGameFeaturePluginsDeactivating = PluginsToDeactivate.Num();
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.DeactivateGameFeaturePlugins: PluginsToDeactivate=%d, Context=%s"),
		NumGameFeaturePluginsDeactivating,
		*GetClientServerContextString(this)));

	if (NumGameFeaturePluginsDeactivating == 0)
	{
		FinalizeExperienceUnload();
		return;
	}

	for (const FString& PluginURL : PluginsToDeactivate)
	{
		UGameFeaturesSubsystem::Get().DeactivateGameFeaturePlugin(PluginURL, FGameFeaturePluginDeactivateComplete::CreateUObject(this, &ThisClass::OnGameFeaturePluginDeactivateComplete));
	}
}

void UScWExperienceManagerComponent::OnGameFeaturePluginDeactivateComplete(const UE::GameFeatures::FResult& Result)
{
	static_cast<void>(Result);

	if (NumGameFeaturePluginsDeactivating <= 0)
	{
		return;
	}

	--NumGameFeaturePluginsDeactivating;
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.OnGameFeaturePluginDeactivateComplete: RemainingPlugins=%d, Context=%s"),
		NumGameFeaturePluginsDeactivating,
		*GetClientServerContextString(this)));

	if (NumGameFeaturePluginsDeactivating == 0)
	{
		FinalizeExperienceUnload();
	}
}

void UScWExperienceManagerComponent::FinalizeExperienceUnload()
{
	if (LoadState == EScWExperienceLoadState::Unloaded)
	{
		return;
	}
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.FinalizeExperienceUnload: PreviousState=%s, Context=%s"),
		ExperienceLoadStateToString(LoadState),
		*GetClientServerContextString(this)));

	NumGameFeaturePluginsLoading = 0;
	NumGameFeaturePluginsDeactivating = 0;
	NumObservedPausers = 0;
	NumExpectedPausers = 0;
	ActivatedActions.Reset();
	GameFeaturePluginURLs.Reset();
	OnExperienceLoaded_HighPriority.Clear();
	OnExperienceLoaded.Clear();
	OnExperienceLoaded_LowPriority.Clear();

	LoadState = EScWExperienceLoadState::Unloaded;
	CurrentExperience = nullptr;
}

void UScWExperienceManagerComponent::OnExperienceFullLoadCompleted()
{
	const bool bValidLoadState =
		(LoadState == EScWExperienceLoadState::Loading)
		|| (LoadState == EScWExperienceLoadState::LoadingGameFeatures)
		|| (LoadState == EScWExperienceLoadState::LoadingChaosTestingDelay);
	if (!bValidLoadState || (CurrentExperience == nullptr))
	{
		return;
	}

	// Insert a random delay for testing (if configured)
	if (LoadState != EScWExperienceLoadState::LoadingChaosTestingDelay)
	{
		const float DelaySecs = ScWConsoleVariables::GetExperienceLoadDelayDuration();
		if (DelaySecs > 0.0f)
		{
			FTimerHandle DummyHandle;

			LoadState = EScWExperienceLoadState::LoadingChaosTestingDelay;
			LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.OnExperienceFullLoadCompleted: EnteringDelay=%.2fs, Context=%s"),
				DelaySecs,
				*GetClientServerContextString(this)));
			GetWorld()->GetTimerManager().SetTimer(DummyHandle, this, &ThisClass::OnExperienceFullLoadCompleted, DelaySecs, /*bLooping=*/ false);

			return;
		}
	}

	LoadState = EScWExperienceLoadState::ExecutingActions;
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.OnExperienceFullLoadCompleted: LoadState=%s, Experience=%s, Context=%s"),
		ExperienceLoadStateToString(LoadState),
		*GetExperienceIdString(CurrentExperience),
		*GetClientServerContextString(this)));

	ActivateExperienceActions();

	LoadState = EScWExperienceLoadState::Loaded;
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.OnExperienceFullLoadCompleted: LoadState=%s, Experience=%s, Context=%s"),
		ExperienceLoadStateToString(LoadState),
		*GetExperienceIdString(CurrentExperience),
		*GetClientServerContextString(this)));

	OnExperienceLoaded_HighPriority.Broadcast(CurrentExperience);
	OnExperienceLoaded_HighPriority.Clear();

	OnExperienceLoaded.Broadcast(CurrentExperience);
	OnExperienceLoaded.Clear();

	OnExperienceLoaded_LowPriority.Broadcast(CurrentExperience);
	OnExperienceLoaded_LowPriority.Clear();

	// Apply any necessary scalability settings
#if !UE_SERVER
	UScWSettingsLocal::Get()->OnExperienceLoaded();
#endif
}

void UScWExperienceManagerComponent::OnActionDeactivationCompleted()
{
	if (LoadState != EScWExperienceLoadState::Deactivating)
	{
		return;
	}

	check(IsInGameThread());
	++NumObservedPausers;
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.OnActionDeactivationCompleted: ObservedPausers=%d, ExpectedPausers=%d, Context=%s"),
		NumObservedPausers,
		NumExpectedPausers,
		*GetClientServerContextString(this)));

	if (NumObservedPausers == NumExpectedPausers)
	{
		OnAllActionsDeactivated();
	}
}

void UScWExperienceManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentExperience);
}

void UScWExperienceManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if ((LoadState == EScWExperienceLoadState::Unloaded) || (LoadState == EScWExperienceLoadState::Deactivating))
	{
		return;
	}

	const EScWExperienceLoadState PreviousLoadState = LoadState;
	LoadState = EScWExperienceLoadState::Deactivating;
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.EndPlay: PreviousState=%s, NewState=%s, Context=%s"),
		ExperienceLoadStateToString(PreviousLoadState),
		ExperienceLoadStateToString(LoadState),
		*GetClientServerContextString(this)));

	if (PreviousLoadState == EScWExperienceLoadState::Loaded)
	{
		// Make sure we won't complete the transition prematurely if someone registers as a pauser but fires immediately
		NumExpectedPausers = INDEX_NONE;
		NumObservedPausers = 0;

		// Deactivate and unload the actions
		FGameFeatureDeactivatingContext Context(TEXT(""), [this](FStringView) { this->OnActionDeactivationCompleted(); });

		const FWorldContext* ExistingWorldContext = GEngine->GetWorldContextFromWorld(GetWorld());
		if (ExistingWorldContext)
		{
			Context.SetRequiredWorldContextHandle(ExistingWorldContext->ContextHandle);
		}

		DeactivateExperienceActions(Context);

		NumExpectedPausers = Context.GetNumPausers();

		if (NumExpectedPausers == NumObservedPausers)
		{
			OnAllActionsDeactivated();
		}
	}
	else
	{
		OnAllActionsDeactivated();
	}
}

bool UScWExperienceManagerComponent::ShouldShowLoadingScreen(FString& OutReason) const
{
	if (LoadState != EScWExperienceLoadState::Loaded)
	{
		OutReason = TEXT("Experience still loading");
		return true;
	}
	else
	{
		return false;
	}
}

void UScWExperienceManagerComponent::OnAllActionsDeactivated()
{
	if ((LoadState == EScWExperienceLoadState::Unloaded) || (LoadState == EScWExperienceLoadState::Deactivating && (NumGameFeaturePluginsDeactivating > 0)))
	{
		return;
	}
	LogExperienceManagerLifecycle(this, FString::Printf(TEXT("ExperienceManager.OnAllActionsDeactivated: RemainingPluginDeactivations=%d, Context=%s"),
		NumGameFeaturePluginsDeactivating,
		*GetClientServerContextString(this)));

	ActivatedActions.Reset();
	DeactivateGameFeaturePlugins();
	//@TODO:	GEngine->ForceGarbageCollection(true);
}

