// Scientific Ways

#pragma once

#include "UObject/ObjectKey.h"
#include "UObject/WeakObjectPtrTemplates.h"

#define MODULE_API GAMESETTINGS_API

enum class EGameSettingChangeReason : uint8;

class UGameSetting;
class UGameSettingRegistry;
struct FObjectKey;

/**
 * 
 */
class FGameSettingRegistryChangeTracker : public FNoncopyable
{
public:
	MODULE_API FGameSettingRegistryChangeTracker();
	MODULE_API ~FGameSettingRegistryChangeTracker();

	MODULE_API void WatchRegistry(UGameSettingRegistry* InRegistry);
	MODULE_API void StopWatchingRegistry();

	MODULE_API void ApplyChanges();

	MODULE_API void RestoreToInitial();

	MODULE_API void ClearDirtyState();

	bool IsRestoringSettings() const { return bRestoringSettings; }
	bool HaveSettingsBeenChanged() const { return bSettingsChanged; }

private:
	MODULE_API void HandleSettingChanged(UGameSetting* Setting, EGameSettingChangeReason Reason);

	bool bSettingsChanged = false;
	bool bRestoringSettings = false;

	TWeakObjectPtr<UGameSettingRegistry> Registry;
	TMap<FObjectKey, TWeakObjectPtr<UGameSetting>> DirtySettings;
};

#undef MODULE_API
