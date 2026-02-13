// Scientific Ways

#pragma once

#include "Blueprint/UserWidget.h"

#include "GameSettingDetailExtension.generated.h"

#define MODULE_API GAMESETTINGS_API

enum class EGameSettingChangeReason : uint8;

class UGameSetting;
class UObject;

/**
 * 
 */
UCLASS(MinimalAPI, Abstract, meta = (Category = "Settings", DisableNativeTick))
class UGameSettingDetailExtension : public UUserWidget
{
	GENERATED_BODY()

public:
	MODULE_API void SetSetting(UGameSetting* InSetting);
	
protected:
	MODULE_API virtual void NativeSettingAssigned(UGameSetting* InSetting);
	MODULE_API virtual void NativeSettingValueChanged(UGameSetting* InSetting, EGameSettingChangeReason Reason);

	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API void OnSettingAssigned(UGameSetting* InSetting);

	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API void OnSettingValueChanged(UGameSetting* InSetting);

protected:
	UPROPERTY(Transient)
	TObjectPtr<UGameSetting> Setting;
};

#undef MODULE_API
