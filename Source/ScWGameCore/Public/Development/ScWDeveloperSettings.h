// Scientific Ways

#pragma once

#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "UObject/PrimaryAssetId.h"
#include "UObject/SoftObjectPath.h"
#include "ScWDeveloperSettings.generated.h"

#define MODULE_API SCWGAMECORE_API

struct FPropertyChangedEvent;

class UScWExperience;

/**
 *	Determines when an auto-run cheat command is executed during Play in Editor.
 */
UENUM()
enum class ECheatExecutionTime
{
	// When the cheat manager is created
	OnCheatManagerCreated,

	// When a pawn is possessed by a player
	OnPlayerPawnPossession
};

/**
 *	Pairs a cheat console command with the phase at which it should be auto-executed during PIE.
 */
USTRUCT()
struct FScWCheatToRun
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ECheatExecutionTime Phase = ECheatExecutionTime::OnPlayerPawnPossession;

	UPROPERTY(EditAnywhere)
	FString Cheat;
};

/**
 *	Developer settings / editor cheats
 */
UCLASS(Config = EditorPerProjectUserSettings, MinimalAPI)
class UScWDeveloperSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	UScWDeveloperSettings();

	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface

public:
	// The experience override to use for Play in Editor (if not set, the default for the world settings of the open map will be used)
	UPROPERTY(Category = "ScW", EditDefaultsOnly, BlueprintReadOnly, Config, meta = (AllowedTypes="ScWExperience"))
	FPrimaryAssetId ExperienceOverride;

	UPROPERTY(Category = "ScWBots", EditDefaultsOnly, BlueprintReadOnly, Config, meta = (InlineEditConditionToggle))
	bool bOverrideBotCount = false;

	UPROPERTY(Category = "ScWBots", EditDefaultsOnly, BlueprintReadOnly, Config, meta = (EditCondition=bOverrideBotCount))
	int32 OverrideNumPlayerBotsToSpawn = 0;

	UPROPERTY(Category = "ScWBots", EditDefaultsOnly, BlueprintReadOnly, Config)
	bool bAllowPlayerBotsToAttack = true;

	// Do the full game flow when playing in the editor, or skip 'waiting for player' / etc... game phases?
	UPROPERTY(Category = "ScW", EditDefaultsOnly, BlueprintReadOnly, Config)
	bool bTestFullGameFlowInPIE = false;

	/**
	* Should force feedback effects be played, even if the last input device was not a gamepad?
	* The default behavior in ScW is to only play force feedback if the most recent input device was a gamepad.
	*/
	UPROPERTY(Category = "ScW", config, EditAnywhere, meta = (ConsoleVariable = "ScWPC.ShouldAlwaysPlayForceFeedback"))
	bool bShouldAlwaysPlayForceFeedback = false;

	// Should game logic load cosmetic backgrounds in the editor or skip them for iteration speed?
	UPROPERTY(Category = "ScW", EditDefaultsOnly, BlueprintReadOnly, Config)
	bool bSkipLoadingCosmeticBackgroundsInPIE = false;

	// List of cheats to auto-run during 'play in editor'
	UPROPERTY(Category = "ScW", config, EditAnywhere)
	TArray<FScWCheatToRun> CheatsToRun;
	
	// Should messages broadcast through the gameplay message subsystem be logged?
	//UPROPERTY(config, EditAnywhere, Category=GameplayMessages, meta = (ConsoleVariable="GameplayMessageSubsystem.LogMessages"))
	//bool LogGameplayMessages = false;

#if WITH_EDITORONLY_DATA
	/** A list of common maps that will be accessible via the editor detoolbar */
	UPROPERTY(Category = "Maps", config, EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "/Script/Engine.World"))
	TArray<FSoftObjectPath> CommonEditorMaps;
#endif
	
#if WITH_EDITOR
public:
	// Called by the editor engine to let us pop reminder notifications when cheats are active
	//MODULE_API void OnPlayInEditorStarted() const;

private:
	void ApplySettings();
#endif

public:
	//~UObject interface
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostReloadConfig(FProperty* PropertyThatWasLoaded) override;
	virtual void PostInitProperties() override;
#endif
	//~End of UObject interface
};

#undef MODULE_API
