// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Subsystems/WorldSubsystem.h"

#include "ScWWorldAudioSubsystem.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] World Audio Subsystem", KeyWords = "ScWSound"))
class UScWWorldAudioSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

//~ Begin Initialize
public:
	UScWWorldAudioSubsystem();
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override; // UWorldSubsystem
	virtual void Tick(float InDeltaSeconds) override; // UTickableWorldSubsystem
	virtual TStatId GetStatId() const override; // UTickableWorldSubsystem
//~ End Initialize
	
//~ Begin Audio Layers
public:

	UFUNCTION(Category = "Audio Layers", BlueprintCallable, meta = (AutoCreateRefTerm = "InLayer", InLayer = "Default"))
	MODULE_API UAudioComponent* GetSound2D_AtLayer(const FName& InLayer) const { return AudioLayerMap.Contains(InLayer) ? AudioLayerMap[InLayer] : nullptr; }

	UFUNCTION(Category = "Audio Layers", BlueprintCallable, meta = (AutoCreateRefTerm = "InLayer", InLayer = "Default", AdvancedDisplay = "InPitchMultiplier, InStartTime, InConcurrencySettings, bInAutoDestroy"))
	MODULE_API UAudioComponent* PlaySound2D_AtLayer(const FName& InLayer, USoundBase* InSoundAsset, float InFadeInDuration = 0.0f, float InVolumeMultiplier = 1.0f, float InPitchMultiplier = 1.0f, float InStartTime = 0.0f, USoundConcurrency* InConcurrencySettings = nullptr, bool bInAutoDestroy = true);

	UFUNCTION(Category = "Audio Layers", BlueprintCallable, meta = (AutoCreateRefTerm = "InLayer", InLayer = "Default"))
	MODULE_API bool StopSound2D_AtLayer(const FName& InLayer, float InFadeOutDuration = 1.0);

protected:
	void OnAudioComponentFinishedAudio(UAudioComponent* InAudioComponent);
	void HandleStopAndDestroyAudioComponent(UAudioComponent* InAudioComponent);

	UPROPERTY(Category = "Audio Layers", VisibleInstanceOnly, BlueprintReadOnly)
	TMap<FName, TObjectPtr<UAudioComponent>> AudioLayerMap;

	UPROPERTY(Category = "Audio Layers", VisibleInstanceOnly, BlueprintReadOnly)
	TMap<TObjectPtr<UAudioComponent>, float> AudioAutoRemoveTimeLeftMap;
//~ End Audio Layers
};

#undef MODULE_API
