// Scientific Ways

#pragma once

#include "GameFeatureAction.h"
#include "UObject/SoftObjectPath.h"
#include "ScWGFA_AddGameplayCuePath.generated.h"

/**
 * GameFeatureAction responsible for adding gameplay cue paths to the gameplay cue manager.
 *
 * @see UAbilitySystemGlobals::GameplayCueNotifyPaths
 */
UCLASS(MinimalAPI, meta = (DisplayName = "Add Gameplay Cue Path"))
class UScWGFA_AddGameplayCuePath final : public UGameFeatureAction
{
	GENERATED_BODY()

public:

	UScWGFA_AddGameplayCuePath();

	//~UObject interface
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
	//~End of UObject interface

	const TArray<FDirectoryPath>& GetDirectoryPathsToAdd() const { return DirectoryPathsToAdd; }

private:
	/** List of paths to register to the gameplay cue manager. These are relative tot he game content directory */
	UPROPERTY(EditAnywhere, Category = "Game Feature | Gameplay Cues", meta = (RelativeToGameContentDir, LongPackageName))
	TArray<FDirectoryPath> DirectoryPathsToAdd;
};
