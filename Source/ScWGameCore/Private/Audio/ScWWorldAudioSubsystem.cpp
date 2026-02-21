// Scientific Ways

#include "Audio/ScWWorldAudioSubsystem.h"

#include "Stats/Stats.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWWorldAudioSubsystem)

//~ Begin Initialize
UScWWorldAudioSubsystem::UScWWorldAudioSubsystem()
{
	
}

void UScWWorldAudioSubsystem::OnWorldBeginPlay(UWorld& InWorld) // UWorldSubsystem
{
	Super::OnWorldBeginPlay(InWorld);

	
}

void UScWWorldAudioSubsystem::Tick(float InDeltaSeconds) // UTickableWorldSubsystem
{
	Super::Tick(InDeltaSeconds);

	if (!AudioAutoRemoveTimeLeftMap.IsEmpty())
	{
		TArray<UAudioComponent*> ComponentsToRemove;

		for (auto& SamplePair : AudioAutoRemoveTimeLeftMap)
		{
			if (SamplePair.Value > InDeltaSeconds)
			{
				ComponentsToRemove.Add(SamplePair.Key);
			}
			else
			{
				SamplePair.Value -= InDeltaSeconds;
			}
		}
		for (UAudioComponent* SampleComponent : ComponentsToRemove)
		{
			HandleStopAndDestroyAudioComponent(SampleComponent);
		}
	}
}

TStatId UScWWorldAudioSubsystem::UScWWorldAudioSubsystem::GetStatId() const // UTickableWorldSubsystem
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(ThisClass, STATGROUP_Tickables);
}
//~ End Initialize

//~ Begin Audio Layers
UAudioComponent* UScWWorldAudioSubsystem::PlaySound2D_AtLayer(const FName& InLayer, USoundBase* InSoundAsset, float InFadeInDuration, float InVolumeMultiplier, float InPitchMultiplier, float InStartTime, USoundConcurrency* InConcurrencySettings, bool bInAutoDestroy)
{
	ensureReturn(InSoundAsset, nullptr);

	StopSound2D_AtLayer(InLayer, InFadeInDuration);
	ensureReturn(!AudioLayerMap.Contains(InLayer), nullptr);

	UAudioComponent* NewAudioComponent = UGameplayStatics::SpawnSound2D(this, InSoundAsset, InVolumeMultiplier, InPitchMultiplier, InStartTime, InConcurrencySettings, false, bInAutoDestroy);
	ensureReturn(NewAudioComponent, nullptr);

	AudioLayerMap.Add(InLayer, NewAudioComponent);

	if (bInAutoDestroy)
	{
		NewAudioComponent->OnAudioFinishedNative.AddUObject(this, &ThisClass::OnAudioComponentFinishedAudio);
	}
	if (InFadeInDuration > 0.0f)
	{
		NewAudioComponent->FadeIn(InFadeInDuration, InVolumeMultiplier, InStartTime);
	}
	return NewAudioComponent;
}

bool UScWWorldAudioSubsystem::StopSound2D_AtLayer(const FName& InLayer, float InFadeOutDuration)
{
	if (AudioLayerMap.Contains(InLayer))
	{
		UAudioComponent* AudioComponent = AudioLayerMap[InLayer];
		AudioLayerMap.Remove(InLayer);

		if (AudioComponent)
		{
			if (InFadeOutDuration > 0.0f)
			{
				AudioComponent->FadeOut(InFadeOutDuration, 0.0f);
				AudioAutoRemoveTimeLeftMap.Add(AudioComponent, InFadeOutDuration);
			}
			else
			{
				HandleStopAndDestroyAudioComponent(AudioComponent);
			}
			return true;
		}
	}
	return false;
}

void UScWWorldAudioSubsystem::OnAudioComponentFinishedAudio(UAudioComponent* InAudioComponent)
{
	HandleStopAndDestroyAudioComponent(InAudioComponent);
}

void UScWWorldAudioSubsystem::HandleStopAndDestroyAudioComponent(UAudioComponent* InAudioComponent)
{
	if (auto* SampleLayer = AudioLayerMap.FindKey(InAudioComponent))
	{
		AudioLayerMap.Remove(*SampleLayer);
	}
	if (InAudioComponent)
	{
		InAudioComponent->Stop();
		InAudioComponent->DestroyComponent();
	}
	if (AudioAutoRemoveTimeLeftMap.Contains(InAudioComponent))
	{
		AudioAutoRemoveTimeLeftMap.Remove(InAudioComponent);
	}
}
//~ End Audio Layers
