// Scientific Ways

#pragma once

#include "ScwGameCore.h"

#include "CommonGameInstance.h"

#include "ScWGameInstance.generated.h"

#define MODULE_API SCWGAMECORE_API

/*USTRUCT(BlueprintType)
struct FGameAnalyticsSettings
{
	GENERATED_BODY()

	UPROPERTY(Category = "Setup", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "Your GameAnalytics Game Key - copy/paste from the GA website."))
	FString GameKey;

	UPROPERTY(Category = "Setup", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "Your GameAnalytics Secret Key - copy/paste from the GA website."))
	FString SecretKey;

	UPROPERTY(Category = "Setup", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "The current version of the game. Updating the build name for each test version of the game will allow you to filter by build when viewing your data on the GA website."))
	FString Build = TEXT("0.1");

	UPROPERTY(Category = "Events", EditDefaultsOnly, BlueprintReadOnly)
	bool bEnableEventSubmission = true;

	UPROPERTY(Category = "CustomDimensions", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "List of custom dimensions 01."))
    TArray<FString> CustomDimensions01;

	UPROPERTY(Category = "CustomDimensions", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "List of custom dimensions 02."))
    TArray<FString> CustomDimensions02;

	UPROPERTY(Category = "CustomDimensions", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "List of custom dimensions 03."))
    TArray<FString> CustomDimensions03;

	UPROPERTY(Category = "ResourceTypes", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "List of Resource Currencies."))
    TArray<FString> ResourceCurrencies;

	UPROPERTY(Category = "ResourceTypes", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "List of Resource Item Types."))
    TArray<FString> ResourceItemTypes;

	UPROPERTY(Category = "Advanced", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "Use manual session handling. Manually choose when to end and start a new session. Note initializing of the SDK will automatically start the first session."))
    bool bUseManualSessionHandling = false;

	UPROPERTY(Category = "Advanced", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "Auto detect app version to use for build field (only for Android and iOS)."))
    bool bAutoDetectAppVersion = false;

	UPROPERTY(Category = "Advanced", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "Disable device info (only Mac, Windows and Linux)."))
    bool bDisableDeviceInfo = false;

	UPROPERTY(Category = "Advanced", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "Use automatic error reporting."))
    bool bUseErrorReporting = true;

	UPROPERTY(Category = "Advanced", EditDefaultsOnly, BlueprintReadOnly)
    bool bEnableFpsHistogram = false;

	UPROPERTY(Category = "Advanced", EditDefaultsOnly, BlueprintReadOnly)
	bool bEnableMemoryHistogram = false;

	UPROPERTY(Category = "Advanced", EditDefaultsOnly, BlueprintReadOnly)
	bool bEnableHealthHardwareInfo = false;

	UPROPERTY(Category = "Debug", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "Show info messages from GA in builds (e.g. Xcode for iOS)."))
    bool bInfoLogBuild = true;

	UPROPERTY(Category = "Debug", EditDefaultsOnly, BlueprintReadOnly, meta = (ToolTip = "Show full info messages from GA in builds (e.g. Xcode for iOS). Noet that this option includes long JSON messages sent to the server."))
    bool bVerboseLogBuild = false;
};*/

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Game Instance"))
class UScWGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

public:

	UScWGameInstance(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());
	
//~ Begin Initialize
public:
	virtual void Init() override; // UGameInstance
	virtual void Shutdown() override; // UGameInstance
//~ End Initialize

//~ Begin Analytics
/*protected:

	UFUNCTION(Category = "Analytics", BlueprintNativeEvent)
	UGameAnalytics* BP_InitGameAnalytics();

	UPROPERTY(Category = "Analytics", EditDefaultsOnly, BlueprintReadOnly)
	bool bInitGameAnalytics;

	UPROPERTY(Category = "Analytics", EditDefaultsOnly, BlueprintReadOnly)
	FGameAnalyticsSettings GameAnalyticsSettings;*/
//~ End Analytics
};

#undef MODULE_API
