// Scientific Ways

#include "Features/ScWGameFeaturesProjectPolicies.h"

#include "AbilitySystem/ScWGameplayCueManager.h"
#include "GameFeatureData.h"
#include "GameplayCueSet.h"

UScWGameFeaturesProjectPolicies::UScWGameFeaturesProjectPolicies(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
}

UScWGameFeaturesProjectPolicies& UScWGameFeaturesProjectPolicies::Get()
{
	return UGameFeaturesSubsystem::Get().GetPolicy<UScWGameFeaturesProjectPolicies>();
}

void UScWGameFeaturesProjectPolicies::InitGameFeatureManager()
{
	//Observers.Add(NewObject<UScWGameFeature_HotfixManager>());
	Observers.Add(NewObject<UScWGameFeature_AddGameplayCuePaths>());

	UGameFeaturesSubsystem& Subsystem = UGameFeaturesSubsystem::Get();
	for (UObject* Observer : Observers)
	{
		Subsystem.AddObserver(Observer);
	}

	Super::InitGameFeatureManager();
}

void UScWGameFeaturesProjectPolicies::ShutdownGameFeatureManager()
{
	Super::ShutdownGameFeatureManager();

	UGameFeaturesSubsystem& Subsystem = UGameFeaturesSubsystem::Get();
	for (UObject* Observer : Observers)
	{
		Subsystem.RemoveObserver(Observer);
	}
	Observers.Empty();
}

TArray<FPrimaryAssetId> UScWGameFeaturesProjectPolicies::GetPreloadAssetListForGameFeature(const UGameFeatureData* GameFeatureToLoad, bool bIncludeLoadedAssets) const
{
	return Super::GetPreloadAssetListForGameFeature(GameFeatureToLoad, bIncludeLoadedAssets);
}

const TArray<FName> UScWGameFeaturesProjectPolicies::GetPreloadBundleStateForGameFeature() const
{
	return Super::GetPreloadBundleStateForGameFeature();
}

void UScWGameFeaturesProjectPolicies::GetGameFeatureLoadingMode(bool& bLoadClientData, bool& bLoadServerData) const
{
	// Editor will load both, this can cause hitching as the bundles are set to not preload in editor
	bLoadClientData = !IsRunningDedicatedServer();
	bLoadServerData = !IsRunningClientOnly();
}

bool UScWGameFeaturesProjectPolicies::IsPluginAllowed(const FString& PluginURL, FString* OutReason) const
{
	return Super::IsPluginAllowed(PluginURL, OutReason);
}

//////////////////////////////////////////////////////////////////////
//

/*#include "Hotfix/ScWHotfixManager.h"

void UScWGameFeature_HotfixManager::OnGameFeatureLoading(const UGameFeatureData* GameFeatureData, const FString& PluginURL)
{
	if (UScWHotfixManager* HotfixManager = Cast<UScWHotfixManager>(UOnlineHotfixManager::Get(nullptr)))
	{
		HotfixManager->RequestPatchAssetsFromIniFiles();
	}
}*/

//////////////////////////////////////////////////////////////////////
//

#include "AbilitySystemGlobals.h"
#include "Features/ScWGFA_AddGameplayCuePath.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameFeaturesProjectPolicies)

class FName;
struct FPrimaryAssetId;

void UScWGameFeature_AddGameplayCuePaths::OnGameFeatureRegistering(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FString& PluginURL)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UScWGameFeature_AddGameplayCuePaths::OnGameFeatureRegistering);
	
	const FString PluginRootPath = TEXT("/") + PluginName;
	for (const UGameFeatureAction* Action : GameFeatureData->GetActions())
	{
		if (const UScWGFA_AddGameplayCuePath* AddGameplayCueGFA = Cast<UScWGFA_AddGameplayCuePath>(Action))
		{
			const TArray<FDirectoryPath>& DirsToAdd = AddGameplayCueGFA->GetDirectoryPathsToAdd();
			
			if (UScWGameplayCueManager* GCM = UScWGameplayCueManager::Get())
			{
				UGameplayCueSet* RuntimeGameplayCueSet = GCM->GetRuntimeCueSet();
				const int32 PreInitializeNumCues = RuntimeGameplayCueSet ? RuntimeGameplayCueSet->GameplayCueData.Num() : 0;

				for (const FDirectoryPath& Directory : DirsToAdd)
				{
					FString MutablePath = Directory.Path;
					UGameFeaturesSubsystem::FixPluginPackagePath(MutablePath, PluginRootPath, false);
					GCM->AddGameplayCueNotifyPath(MutablePath, /** bShouldRescanCueAssets = */ false);	
				}
				
				// Rebuild the runtime library with these new paths
				if (!DirsToAdd.IsEmpty())
				{
					GCM->InitializeRuntimeObjectLibrary();	
				}

				const int32 PostInitializeNumCues = RuntimeGameplayCueSet ? RuntimeGameplayCueSet->GameplayCueData.Num() : 0;
				if (PreInitializeNumCues != PostInitializeNumCues)
				{
					GCM->RefreshGameplayCuePrimaryAsset();
				}
			}
		}
	}
}

void UScWGameFeature_AddGameplayCuePaths::OnGameFeatureUnregistering(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FString& PluginURL)
{
	const FString PluginRootPath = TEXT("/") + PluginName;
	for (const UGameFeatureAction* Action : GameFeatureData->GetActions())
	{
		if (const UScWGFA_AddGameplayCuePath* AddGameplayCueGFA = Cast<UScWGFA_AddGameplayCuePath>(Action))
		{
			const TArray<FDirectoryPath>& DirsToAdd = AddGameplayCueGFA->GetDirectoryPathsToAdd();
			
			if (UGameplayCueManager* GCM = UAbilitySystemGlobals::Get().GetGameplayCueManager())
			{
				int32 NumRemoved = 0;
				for (const FDirectoryPath& Directory : DirsToAdd)
				{
					FString MutablePath = Directory.Path;
					UGameFeaturesSubsystem::FixPluginPackagePath(MutablePath, PluginRootPath, false);
					NumRemoved += GCM->RemoveGameplayCueNotifyPath(MutablePath, /** bShouldRescanCueAssets = */ false);
				}

				ensure(NumRemoved == DirsToAdd.Num());
				
				// Rebuild the runtime library only if there is a need to
				if (NumRemoved > 0)
				{
					GCM->InitializeRuntimeObjectLibrary();	
				}			
			}
	}
	}
}
