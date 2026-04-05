// Scientific Ways

#pragma once

#include "Engine/DataAsset.h"

#include "GameSettingVisualData.generated.h"

#define MODULE_API GAMESETTINGS_API

class FName;
class UGameSetting;
class UGameSettingDetailExtension;
class UGameSettingListEntryBase;
class UObject;

USTRUCT(BlueprintType)
struct FGameSettingClassExtensions
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Extensions", EditAnywhere)
	TArray<TSoftClassPtr<UGameSettingDetailExtension>> Extensions;
};

USTRUCT(BlueprintType)
struct FGameSettingNameExtensions
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Extensions", EditAnywhere)
	bool bIncludeClassDefaultExtensions = false;

	UPROPERTY(Category = "Extensions", EditAnywhere)
	TArray<TSoftClassPtr<UGameSettingDetailExtension>> Extensions;
};

/**
 * 
 */
UCLASS(MinimalAPI, BlueprintType)
class UGameSettingVisualData : public UDataAsset
{
	GENERATED_BODY()

public:
	MODULE_API TSubclassOf<UGameSettingListEntryBase> GetEntryForSetting(UGameSetting* InSetting);

	MODULE_API virtual TArray<TSoftClassPtr<UGameSettingDetailExtension>> GatherDetailExtensions(UGameSetting* InSetting);
	
protected:
	MODULE_API virtual TSubclassOf<UGameSettingListEntryBase> GetCustomEntryForSetting(UGameSetting* InSetting);

protected:
	UPROPERTY(Category = "ListEntries", EditDefaultsOnly, meta = (AllowAbstract))
	TMap<TSubclassOf<UGameSetting>, TSubclassOf<UGameSettingListEntryBase>> EntryWidgetForClass;

	UPROPERTY(Category = "ListEntries", EditDefaultsOnly, meta = (AllowAbstract))
	TMap<FName, TSubclassOf<UGameSettingListEntryBase>> EntryWidgetForName;

	UPROPERTY(Category = "Extensions", EditDefaultsOnly, meta = (AllowAbstract))
	TMap<TSubclassOf<UGameSetting>, FGameSettingClassExtensions> ExtensionsForClasses;

	UPROPERTY(Category = "Extensions", EditDefaultsOnly)
	TMap<FName, FGameSettingNameExtensions> ExtensionsForName;
};

#undef MODULE_API
