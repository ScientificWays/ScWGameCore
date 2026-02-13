// Scientific Ways

#pragma once

#include "EnhancedActionKeyMapping.h"
#include "GameSettingValue.h"
#include "UserSettings/EnhancedInputUserSettings.h"

#include "ScWSettingKeyboardInput.generated.h"

#define MODULE_API SCWGAMECORE_API

class UObject;

//--------------------------------------
// UScWSettingKeyboardInput
//--------------------------------------

UCLASS(MinimalAPI)
class UScWSettingKeyboardInput : public UGameSettingValue
{
	GENERATED_BODY()

public:
	MODULE_API UScWSettingKeyboardInput();

	MODULE_API void InitializeInputData(const UEnhancedPlayerMappableKeyProfile* KeyProfile, const FKeyMappingRow& MappingData, const FPlayerMappableKeyQueryOptions& QueryOptions);

	MODULE_API FText GetKeyTextFromSlot(const EPlayerMappableKeySlot InSlot) const;
	
	MODULE_API virtual void StoreInitial() override;
	MODULE_API virtual void ResetToDefault() override;
	MODULE_API virtual void RestoreToInitial() override;

	MODULE_API bool ChangeBinding(int32 InKeyBindSlot, FKey NewKey);
	MODULE_API void GetAllMappedActionsFromKey(int32 InKeyBindSlot, FKey Key, TArray<FName>& OutActionNames) const;

	/** Returns true if mappings on this setting have been customized */
	MODULE_API bool IsMappingCustomized() const;
	
	MODULE_API FText GetSettingDisplayName() const;
	MODULE_API FText GetSettingDisplayCategory() const;

	MODULE_API const FKeyMappingRow* FindKeyMappingRow() const;
	MODULE_API UEnhancedPlayerMappableKeyProfile* FindMappableKeyProfile() const;
	MODULE_API UEnhancedInputUserSettings* GetUserSettings() const;
	
protected:
	/** UScWSetting */
	MODULE_API virtual void OnInitialized() override;

protected:

	/** The name of this action's mappings */
	FName ActionMappingName;

	/** The query options to filter down keys on this setting for */
	FPlayerMappableKeyQueryOptions QueryOptions;

	/** The profile identifier that this key setting is from */
	FString ProfileIdentifier;

	/** Store the initial key mappings that are set on this for each slot */
	TMap<EPlayerMappableKeySlot, FKey> InitialKeyMappings;
};

#undef MODULE_API
