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
	UPROPERTY(EditAnywhere, Category = Extensions)
	TArray<TSoftClassPtr<UGameSettingDetailExtension>> Extensions;
};

USTRUCT(BlueprintType)
struct FGameSettingNameExtensions
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Extensions)
	bool bIncludeClassDefaultExtensions = false;

	UPROPERTY(EditAnywhere, Category = Extensions)
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
	UPROPERTY(EditDefaultsOnly, Category = ListEntries, meta = (AllowAbstract))
	TMap<TSubclassOf<UGameSetting>, TSubclassOf<UGameSettingListEntryBase>> EntryWidgetForClass;

	UPROPERTY(EditDefaultsOnly, Category = ListEntries, meta = (AllowAbstract))
	TMap<FName, TSubclassOf<UGameSettingListEntryBase>> EntryWidgetForName;

	UPROPERTY(EditDefaultsOnly, Category = Extensions, meta = (AllowAbstract))
	TMap<TSubclassOf<UGameSetting>, FGameSettingClassExtensions> ExtensionsForClasses;

	UPROPERTY(EditDefaultsOnly, Category = Extensions)
	TMap<FName, FGameSettingNameExtensions> ExtensionsForName;
};

#undef MODULE_API
