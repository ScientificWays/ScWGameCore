// Scientific Ways

#pragma once

#include "DataSource/GameSettingDataSourceDynamic.h" // IWYU pragma: keep
#include "GameSettingRegistry.h"
#include "Settings/ScWSettingsLocal.h" // IWYU pragma: keep

#include "ScWGameSettingRegistry.generated.h"

class ULocalPlayer;
class UObject;

//--------------------------------------
// UScWGameSettingRegistry
//--------------------------------------

class UGameSettingCollection;
class UScWLocalPlayer;

DECLARE_LOG_CATEGORY_EXTERN(LogScWGameSettingRegistry, Log, Log);

#define GET_SHARED_SETTINGS_FUNCTION_PATH(FunctionOrPropertyName)							\
	MakeShared<FGameSettingDataSourceDynamic>(TArray<FString>({								\
		GET_FUNCTION_NAME_STRING_CHECKED(UScWLocalPlayer, GetSharedSettings),				\
		GET_FUNCTION_NAME_STRING_CHECKED(UScWSettingsShared, FunctionOrPropertyName)		\
	}))

#define GET_LOCAL_SETTINGS_FUNCTION_PATH(FunctionOrPropertyName)							\
	MakeShared<FGameSettingDataSourceDynamic>(TArray<FString>({								\
		GET_FUNCTION_NAME_STRING_CHECKED(UScWLocalPlayer, GetLocalSettings),				\
		GET_FUNCTION_NAME_STRING_CHECKED(UScWSettingsLocal, FunctionOrPropertyName)		\
	}))

/**
 * 
 */
UCLASS()
class UScWGameSettingRegistry : public UGameSettingRegistry
{
	GENERATED_BODY()

public:
	UScWGameSettingRegistry();

	static UScWGameSettingRegistry* Get(UScWLocalPlayer* InLocalPlayer);
	
	virtual void SaveChanges() override;

protected:
	virtual void OnInitialize(ULocalPlayer* InLocalPlayer) override;
	virtual bool IsFinishedInitializing() const override;

	UGameSettingCollection* InitializeVideoSettings(UScWLocalPlayer* InLocalPlayer);
	void InitializeVideoSettings_FrameRates(UGameSettingCollection* Screen, UScWLocalPlayer* InLocalPlayer);
	void AddPerformanceStatPage(UGameSettingCollection* Screen, UScWLocalPlayer* InLocalPlayer);

	UGameSettingCollection* InitializeAudioSettings(UScWLocalPlayer* InLocalPlayer);
	UGameSettingCollection* InitializeGameplaySettings(UScWLocalPlayer* InLocalPlayer);

	UGameSettingCollection* InitializeMouseAndKeyboardSettings(UScWLocalPlayer* InLocalPlayer);
	UGameSettingCollection* InitializeGamepadSettings(UScWLocalPlayer* InLocalPlayer);

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> VideoSettings;

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> AudioSettings;

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> GameplaySettings;

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> MouseAndKeyboardSettings;

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> GamepadSettings;
};
