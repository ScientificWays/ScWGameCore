// Scientific Ways

#pragma once

#include "Engine/AssetManager.h"
#include "ScWAssetManagerStartupJob.h"
#include "Templates/SubclassOf.h"

#include "ScWAssetManager.generated.h"

#define MODULE_API SCWGAMECORE_API

struct FScWBundles
{
	static const FName Equipped;
};


/**
 * UScWAssetManager
 *
 *	Game implementation of the asset manager that overrides functionality and stores game-specific types.
 *	It is expected that most games will want to override AssetManager as it provides a good place for game-specific loading logic.
 *	This class is used by setting 'AssetManagerClassName' in DefaultEngine.ini.
 */
UCLASS(MinimalAPI, Config = Game)
class UScWAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	MODULE_API UScWAssetManager();

	// Returns the AssetManager singleton object.
	static MODULE_API UScWAssetManager& Get();

	// Returns the asset referenced by a TSoftObjectPtr.  This will synchronously load the asset if it's not already loaded.
	template<typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	// Returns the subclass referenced by a TSoftClassPtr.  This will synchronously load the asset if it's not already loaded.
	template<typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	// Logs all assets currently loaded and tracked by the asset manager.
	static MODULE_API void DumpLoadedAssets();

	MODULE_API const class UScWGameData& GetGameData();
	MODULE_API const class UScWPawnData* GetDefaultPawnData() const;

protected:
	template <typename GameDataClass>
	const GameDataClass& GetOrLoadTypedGameData(const TSoftObjectPtr<GameDataClass>& DataPath)
	{
		if (TObjectPtr<UPrimaryDataAsset> const* pResult = GameDataMap.Find(GameDataClass::StaticClass()))
		{
			return *CastChecked<GameDataClass>(*pResult);
		}
		// Does a blocking load if needed
		return *CastChecked<const GameDataClass>(LoadGameDataOfClass(GameDataClass::StaticClass(), DataPath, GameDataClass::StaticClass()->GetFName()));
	}


	static MODULE_API UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);
	static MODULE_API bool ShouldLogAssetLoads();

	// Thread safe way of adding a loaded asset to keep in memory.
	MODULE_API void AddLoadedAsset(const UObject* Asset);

	//~UAssetManager interface
	MODULE_API virtual void StartInitialLoading() override;
#if WITH_EDITOR
	MODULE_API virtual void PreBeginPIE(bool bStartSimulate) override;
#endif
	//~End of UAssetManager interface

	MODULE_API UPrimaryDataAsset* LoadGameDataOfClass(TSubclassOf<class UPrimaryDataAsset> DataClass, const TSoftObjectPtr<class UPrimaryDataAsset>& DataClassPath, FPrimaryAssetType PrimaryAssetType);

protected:

	// Global game data asset to use.
	UPROPERTY(Config)
	TSoftObjectPtr<class UScWGameData> ScWGameDataPath;

	// Loaded version of the game data
	UPROPERTY(Transient)
	TMap<TObjectPtr<UClass>, TObjectPtr<UPrimaryDataAsset>> GameDataMap;

	// Pawn data used when spawning player pawns if there isn't one set on the player state.
	UPROPERTY(Config)
	TSoftObjectPtr<UScWPawnData> DefaultPawnData;

private:
	// Flushes the StartupJobs array. Processes all startup work.
	MODULE_API void DoAllStartupJobs();

	// Sets up the ability system
	MODULE_API void InitializeGameplayCueManager();

	// Called periodically during loads, could be used to feed the status to a loading screen
	MODULE_API void UpdateInitialGameContentLoadPercent(float GameContentPercent);

	// The list of tasks to execute on startup. Used to track startup progress.
	TArray<FScWAssetManagerStartupJob> StartupJobs;

private:
	
	// Assets loaded and tracked by the asset manager.
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	// Used for a scope lock when modifying the list of load assets.
	FCriticalSection LoadedAssetsCritical;
};


template<typename AssetType>
AssetType* UScWAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	AssetType* LoadedAsset = nullptr;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedAsset = AssetPointer.Get();
		if (!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedAsset && bKeepInMemory)
		{
			// Added to loaded asset list.
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}
	}

	return LoadedAsset;
}

template<typename AssetType>
TSubclassOf<AssetType> UScWAssetManager::GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedSubclass = AssetPointer.Get();
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to load asset class [%s]"), *AssetPointer.ToString());
		}

		if (LoadedSubclass && bKeepInMemory)
		{
			// Added to loaded asset list.
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
		}
	}

	return LoadedSubclass;
}

#undef MODULE_API
