// Scientific Ways

#pragma once

#include "Engine/DeveloperSettings.h"
#include "UObject/PrimaryAssetId.h"
#include "UObject/SoftObjectPath.h"

#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"

#include "ScWTeamSettings.generated.h"

#define MODULE_API SCWGAMECORE_API

struct FPropertyChangedEvent;

class UScWExperience;

/**
 *	Team system settings
 */
UCLASS(MinimalAPI, Config = Game, DefaultConfig, meta = (DisplayName = "[ScW] Team Settings"))
class UScWTeamSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UScWTeamSettings();
	
//~ Begin Editor
#if WITH_EDITOR
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override; // UObject
	virtual void PostReloadConfig(FProperty* PropertyThatWasLoaded) override; // UObject
	virtual void PostInitProperties() override; // UObject
public:
	// Called by the editor engine to let us pop reminder notifications when cheats are active
	//MODULE_API void OnPlayInEditorStarted() const;
private:
	void ApplySettings();
#endif
//~ End Editor

public:
	virtual FName GetCategoryName() const override; // UDeveloperSettings

	UFUNCTION(Category = "Teams", BlueprintCallable, meta = (GameplayTagFilter = "Team"))
	MODULE_API FORCEINLINE FGenericTeamId GetGenericTeamIdFromTag(const FGameplayTag& InTeamTag) const;

	UFUNCTION(Category = "Teams", BlueprintCallable)
	MODULE_API const FGameplayTag& GetTagFromGenericTeamId(FGenericTeamId InTeamId) const;

	UPROPERTY(Category = "Teams", Config, EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, FGenericTeamId> TeamTagToGenericTeamIdMap;
};

#undef MODULE_API
