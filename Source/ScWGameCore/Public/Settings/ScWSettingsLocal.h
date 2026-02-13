// Scientific Ways

#pragma once

#include "GameFramework/GameUserSettings.h"
#include "InputCoreTypes.h"

#include "ScWSettingsLocal.generated.h"

#define MODULE_API SCWGAMECORE_API

enum class ECommonInputType : uint8;
enum class EScWDisplayablePerformanceStat : uint8;
enum class EScWStatDisplayMode : uint8;

class UScWLocalPlayer;
class UObject;
class USoundControlBus;
class USoundControlBusMix;
struct FFrame;

USTRUCT()
struct FScWScalabilitySnapshot
{
	GENERATED_BODY()

	FScWScalabilitySnapshot();

	Scalability::FQualityLevels Qualities;
	bool bActive = false;
	bool bHasOverrides = false;
};

/**
 *	UScWSettingsLocal
 */
UCLASS(MinimalAPI)
class UScWSettingsLocal : public UGameUserSettings
{
	GENERATED_BODY()

public:

	UScWSettingsLocal();

	static MODULE_API UScWSettingsLocal* Get();

	//~UObject interface
	virtual void BeginDestroy() override;
	//~End of UObject interface

	//~UGameUserSettings interface
	virtual void SetToDefaults() override;
	virtual void LoadSettings(bool bForceReload) override;
	virtual void ConfirmVideoMode() override;
	virtual float GetEffectiveFrameRateLimit() override;
	virtual void ResetToCurrentSettings() override;
	virtual void ApplyNonResolutionSettings() override;
	virtual int32 GetOverallScalabilityLevel() const override;
	virtual void SetOverallScalabilityLevel(int32 Value) override;
	//~End of UGameUserSettings interface

	MODULE_API void OnExperienceLoaded();
	MODULE_API void OnHotfixDeviceProfileApplied();

	//////////////////////////////////////////////////////////////////
	// Frontend state

public:
	MODULE_API void SetShouldUseFrontendPerformanceSettings(bool bInFrontEnd);
protected:
	bool ShouldUseFrontendPerformanceSettings() const;
private:
	bool bInFrontEndForPerformancePurposes = false;

	//////////////////////////////////////////////////////////////////
	// Performance stats
public:
	// Returns the display mode for the specified performance stat
	MODULE_API EScWStatDisplayMode GetPerfStatDisplayState(EScWDisplayablePerformanceStat Stat) const;
	
	// Sets the display mode for the specified performance stat
	MODULE_API void SetPerfStatDisplayState(EScWDisplayablePerformanceStat Stat, EScWStatDisplayMode DisplayMode);

	// Fired when the display state for a performance stat has changed, or the settings are applied
	DECLARE_EVENT(UScWSettingsLocal, FPerfStatSettingsChanged);
	MODULE_API FPerfStatSettingsChanged& OnPerfStatDisplayStateChanged() { return PerfStatSettingsChangedEvent; }

	// Latency flash indicators
	static MODULE_API bool DoesPlatformSupportLatencyMarkers();
	
	DECLARE_EVENT(UScWSettingsLocal, FLatencyFlashInidicatorSettingChanged);
	UFUNCTION()
	MODULE_API void SetEnableLatencyFlashIndicators(const bool bNewVal);
	UFUNCTION()
	MODULE_API bool GetEnableLatencyFlashIndicators() const { return bEnableLatencyFlashIndicators; }
	MODULE_API FLatencyFlashInidicatorSettingChanged& OnLatencyFlashInidicatorSettingsChangedEvent() { return LatencyFlashInidicatorSettingsChangedEvent; }

	// Latency tracking stats
	static MODULE_API bool DoesPlatformSupportLatencyTrackingStats();
	
	DECLARE_EVENT(UScWSettingsLocal, FLatencyStatEnabledSettingChanged);
	FLatencyStatEnabledSettingChanged& OnLatencyStatIndicatorSettingsChangedEvent() { return LatencyStatIndicatorSettingsChangedEvent; }
	
	UFUNCTION()
	MODULE_API void SetEnableLatencyTrackingStats(const bool bNewVal);
	UFUNCTION()
	MODULE_API bool GetEnableLatencyTrackingStats() const { return bEnableLatencyTrackingStats; }

private:

	void ApplyLatencyTrackingStatSetting();
	
	// List of stats to display in the HUD
	UPROPERTY(Config)
	TMap<EScWDisplayablePerformanceStat, EScWStatDisplayMode> DisplayStatList;

	// Event for display stat widget containers to bind to
	FPerfStatSettingsChanged PerfStatSettingsChangedEvent;

	// If true, enable latency flash markers which can be used to measure input latency.
	UPROPERTY(Config)
	bool bEnableLatencyFlashIndicators = false;

	// Event for when the latency flash indicator setting had changed for player input to bind to.
	FLatencyFlashInidicatorSettingChanged LatencyFlashInidicatorSettingsChangedEvent;

	// Event for when the latency stats being toggled on or off has changed
	FLatencyStatEnabledSettingChanged LatencyStatIndicatorSettingsChangedEvent;

	// If true, then the game will track latency stats via ILatencyMarkerModule modules.
	// This enables you to view some more latency oriented performance stats.
	// The default value is set to true if the platform supports it, false otherwise.
	UPROPERTY(Config)
	bool bEnableLatencyTrackingStats;

	//////////////////////////////////////////////////////////////////
	// Brightness/Gamma
public:
	
	UFUNCTION()
	MODULE_API float GetDisplayGamma() const;
	
	UFUNCTION()
	MODULE_API void SetDisplayGamma(float InGamma);

private:
	void ApplyDisplayGamma();
	
	UPROPERTY(Config)
	float DisplayGamma = 2.2;

	//////////////////////////////////////////////////////////////////
	// Display
public:
	UFUNCTION()
	MODULE_API float GetFrameRateLimit_OnBattery() const;
	
	UFUNCTION()
	MODULE_API void SetFrameRateLimit_OnBattery(float NewLimitFPS);

	UFUNCTION()
	MODULE_API float GetFrameRateLimit_InMenu() const;
	
	UFUNCTION()
	MODULE_API void SetFrameRateLimit_InMenu(float NewLimitFPS);

	UFUNCTION()
	MODULE_API float GetFrameRateLimit_WhenBackgrounded() const;
	
	UFUNCTION()
	MODULE_API void SetFrameRateLimit_WhenBackgrounded(float NewLimitFPS);

	UFUNCTION()
	MODULE_API float GetFrameRateLimit_Always() const;
	
	UFUNCTION()
	MODULE_API void SetFrameRateLimit_Always(float NewLimitFPS);

protected:
	void UpdateEffectiveFrameRateLimit();

private:
	UPROPERTY(Config)
	float FrameRateLimit_OnBattery;
	UPROPERTY(Config)
	float FrameRateLimit_InMenu;
	UPROPERTY(Config)
	float FrameRateLimit_WhenBackgrounded;

	//////////////////////////////////////////////////////////////////
	// Display - Mobile quality settings
public:
	
	static MODULE_API int32 GetDefaultMobileFrameRate();
	static MODULE_API int32 GetMaxMobileFrameRate();

	static MODULE_API bool IsSupportedMobileFramePace(int32 TestFPS);

	// Returns the first frame rate at which overall quality is restricted/limited by the current device profile
	int32 GetFirstFrameRateWithQualityLimit() const;

	// Returns the lowest quality at which there's a limit on the overall frame rate (or -1 if there is no limit)
	int32 GetLowestQualityWithFrameRateLimit() const;

	void ResetToMobileDeviceDefaults();

	int32 GetMaxSupportedOverallQualityLevel() const;

private:
	void SetMobileFPSMode(int32 NewLimitFPS);

	void ClampMobileResolutionQuality(int32 TargetFPS);
	void RemapMobileResolutionQuality(int32 FromFPS, int32 ToFPS);

	void ClampMobileFPSQualityLevels(bool bWriteBack);
	void ClampMobileQuality();
	
	int32 GetHighestLevelOfAnyScalabilityChannel() const;

	/* Modifies the input levels based on the active mode's overrides */
	void OverrideQualityLevelsToScalabilityMode(const FScWScalabilitySnapshot& InMode, Scalability::FQualityLevels& InOutLevels);

	/* Clamps the input levels based on the active device profile's default allowed levels */
	void ClampQualityLevelsToDeviceProfile(const Scalability::FQualityLevels& ClampLevels, Scalability::FQualityLevels& InOutLevels);

public:
	int32 GetDesiredMobileFrameRateLimit() const { return DesiredMobileFrameRateLimit; }

	void SetDesiredMobileFrameRateLimit(int32 NewLimitFPS);

private:
	UPROPERTY(Config)
	int32 MobileFrameRateLimit = 30;

	FScWScalabilitySnapshot DeviceDefaultScalabilitySettings;

	bool bSettingOverallQualityGuard = false;

	int32 DesiredMobileFrameRateLimit = 0;

private:

	//////////////////////////////////////////////////////////////////
	// Display - Console quality presets
public:
	
	UFUNCTION()
	FString GetDesiredDeviceProfileQualitySuffix() const;
	
	UFUNCTION()
	MODULE_API void SetDesiredDeviceProfileQualitySuffix(const FString& InDesiredSuffix);

protected:
	/** Updates device profiles, FPS mode etc for the current game mode */
	void UpdateGameModeDeviceProfileAndFps();

	void UpdateConsoleFramePacing();
	void UpdateDesktopFramePacing();
	void UpdateMobileFramePacing();

	void UpdateDynamicResFrameTime(float TargetFPS);

private:
	UPROPERTY(Transient)
	FString DesiredUserChosenDeviceProfileSuffix;

	UPROPERTY(Transient)
	FString CurrentAppliedDeviceProfileOverrideSuffix;

	UPROPERTY(config)
	FString UserChosenDeviceProfileSuffix;

	//////////////////////////////////////////////////////////////////
	// Audio - Volume
public:
	DECLARE_EVENT_OneParam(UScWSettingsLocal, FAudioDeviceChanged, const FString& /*DeviceId*/);
	FAudioDeviceChanged OnAudioOutputDeviceChanged;

public:
	/** Returns if we're using headphone mode (HRTF) **/
	UFUNCTION()
	MODULE_API bool IsHeadphoneModeEnabled() const;

	/** Enables or disables headphone mode (HRTF) - NOTE this setting will be overruled if au.DisableBinauralSpatialization is set */
	UFUNCTION()
	MODULE_API void SetHeadphoneModeEnabled(bool bEnabled);

	/** Returns if we can enable/disable headphone mode (i.e., if it's not forced on or off by the platform) */
	UFUNCTION()
	MODULE_API bool CanModifyHeadphoneModeEnabled() const;

public:
	/** Whether we *want* to use headphone mode (HRTF); may or may not actually be applied **/
	UPROPERTY(Transient)
	bool bDesiredHeadphoneMode;

private:
	/** Whether to use headphone mode (HRTF) **/
	UPROPERTY(config)
	bool bUseHeadphoneMode;

public:
	/** Returns if we're using High Dynamic Range Audio mode (HDR Audio) **/
	UFUNCTION()
	MODULE_API bool IsHDRAudioModeEnabled() const;

	/** Enables or disables High Dynamic Range Audio mode (HDR Audio) */
	UFUNCTION()
	MODULE_API void SetHDRAudioModeEnabled(bool bEnabled);

	/** Whether to use High Dynamic Range Audio mode (HDR Audio) **/
	UPROPERTY(config)
	bool bUseHDRAudioMode;

public:
	/** Returns true if this platform can run the auto benchmark */
	UFUNCTION(BlueprintCallable, Category = Settings)
	MODULE_API bool CanRunAutoBenchmark() const;

	/** Returns true if this user should run the auto benchmark as it has never been run */
	UFUNCTION(BlueprintCallable, Category = Settings)
	MODULE_API bool ShouldRunAutoBenchmarkAtStartup() const;

	/** Run the auto benchmark, optionally saving right away */
	UFUNCTION(BlueprintCallable, Category = Settings)
	MODULE_API void RunAutoBenchmark(bool bSaveImmediately);

	/** Apply just the quality scalability settings */
	MODULE_API void ApplyScalabilitySettings();

	UFUNCTION()
	MODULE_API float GetOverallVolume() const;
	
	UFUNCTION()
	MODULE_API void SetOverallVolume(float InVolume);

	UFUNCTION()
	MODULE_API float GetMusicVolume() const;
	
	UFUNCTION()
	MODULE_API void SetMusicVolume(float InVolume);

	UFUNCTION()
	MODULE_API float GetSoundFXVolume() const;
	
	UFUNCTION()
	MODULE_API void SetSoundFXVolume(float InVolume);

	UFUNCTION()
	MODULE_API float GetDialogueVolume() const;
	
	UFUNCTION()
	MODULE_API void SetDialogueVolume(float InVolume);

	UFUNCTION()
	MODULE_API float GetVoiceChatVolume() const;
	
	UFUNCTION()
	MODULE_API void SetVoiceChatVolume(float InVolume);

	//////////////////////////////////////////////////////////////////
	// Audio - Sound
public:
	/** Returns the user's audio device id */
	UFUNCTION()
	MODULE_API FString GetAudioOutputDeviceId() const { return AudioOutputDeviceId; }

	/** Sets the user's audio device by id */
	UFUNCTION()
	MODULE_API void SetAudioOutputDeviceId(const FString& InAudioOutputDeviceId);

private:
	UPROPERTY(Config)
	FString AudioOutputDeviceId;
	
	void SetVolumeForSoundClass(FName ChannelName, float InVolume);
	

	//////////////////////////////////////////////////////////////////
	// Safezone
public:
	
	UFUNCTION()
	MODULE_API bool IsSafeZoneSet() const { return SafeZoneScale != -1; }
	
	UFUNCTION()
	MODULE_API float GetSafeZone() const { return SafeZoneScale >= 0 ? SafeZoneScale : 0; }
	
	UFUNCTION()
	MODULE_API void SetSafeZone(float Value) { SafeZoneScale = Value; ApplySafeZoneScale(); }

	MODULE_API void ApplySafeZoneScale();
private:
	void SetVolumeForControlBus(USoundControlBus* InSoundControlBus, float InVolume);

	//////////////////////////////////////////////////////////////////
	// Keybindings
public:
	
	// Sets the controller representation to use, a single platform might support multiple kinds of controllers.  For
	// example, Win64 games could be played with both an XBox or Playstation controller.
	UFUNCTION()
	MODULE_API void SetControllerPlatform(const FName InControllerPlatform);
	
	UFUNCTION()
	MODULE_API FName GetControllerPlatform() const;

private:
	void LoadUserControlBusMix();

	UPROPERTY(Config)
	float OverallVolume = 1.0f;
	UPROPERTY(Config)
	float MusicVolume = 1.0f;
	UPROPERTY(Config)
	float SoundFXVolume = 1.0f;
	UPROPERTY(Config)
	float DialogueVolume = 1.0f;
	UPROPERTY(Config)
	float VoiceChatVolume = 1.0f;

	UPROPERTY(Transient)
	TMap<FName/*SoundClassName*/, TObjectPtr<USoundControlBus>> ControlBusMap;

	UPROPERTY(Transient)
	TObjectPtr<USoundControlBusMix> ControlBusMix = nullptr;

	UPROPERTY(Transient)
	bool bSoundControlBusMixLoaded;

	UPROPERTY(Config)
	float SafeZoneScale = -1;

	/**
	 * The name of the controller the player is using.  This is maps to the name of a UCommonInputBaseControllerData
	 * that is available on this current platform.  The gamepad data are registered per platform, you'll find them
	 * in <Platform>Game.ini files listed under +ControllerData=...
	 */
	UPROPERTY(Config)
	FName ControllerPlatform;

	UPROPERTY(Config)
	FName ControllerPreset = TEXT("Default");

	/** The name of the current input config that the user has selected. */
	UPROPERTY(Config)
	FName InputConfigName = TEXT("Default");

	// Replays
public:

	UFUNCTION()
	MODULE_API bool ShouldAutoRecordReplays() const { return bShouldAutoRecordReplays; }
	UFUNCTION()
	MODULE_API void SetShouldAutoRecordReplays(bool bEnabled) { bShouldAutoRecordReplays = bEnabled;}

	UFUNCTION()
	MODULE_API int32 GetNumberOfReplaysToKeep() const { return NumberOfReplaysToKeep; }
	UFUNCTION()
	MODULE_API void SetNumberOfReplaysToKeep(int32 InNumberOfReplays) { NumberOfReplaysToKeep = InNumberOfReplays; }

private:

	UPROPERTY(Config)
	bool bShouldAutoRecordReplays = false;

	UPROPERTY(Config)
	int32 NumberOfReplaysToKeep = 5;

private:
	void OnAppActivationStateChanged(bool bIsActive);
	void ReapplyThingsDueToPossibleDeviceProfileChange();

private:
	FDelegateHandle OnApplicationActivationStateChangedHandle;
};

#undef MODULE_API
