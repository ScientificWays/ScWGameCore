// Scientific Ways

#include "Experience/ScWExperienceSubsystem.h"

#include "Engine/Engine.h"
#include "Subsystems/SubsystemCollection.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWExperienceSubsystem)

#if WITH_EDITOR

void UScWExperienceSubsystem::OnPlayInEditorBegun()
{
	ensure(GameFeaturePluginRequestCountMap.IsEmpty());
	GameFeaturePluginRequestCountMap.Empty();
}

void UScWExperienceSubsystem::NotifyOfPluginActivation(const FString PluginURL)
{
	if (GIsEditor)
	{
		UScWExperienceSubsystem* ExperienceSubsystem = GEngine->GetEngineSubsystem<UScWExperienceSubsystem>();
		check(ExperienceSubsystem);

		// Track the number of requesters who activate this plugin. Multiple load/activation requests are always allowed because concurrent requests are handled.
		int32& Count = ExperienceSubsystem->GameFeaturePluginRequestCountMap.FindOrAdd(PluginURL);
		++Count;
	}
}

bool UScWExperienceSubsystem::RequestToDeactivatePlugin(const FString PluginURL)
{
	if (GIsEditor)
	{
		UScWExperienceSubsystem* ExperienceSubsystem = GEngine->GetEngineSubsystem<UScWExperienceSubsystem>();
		check(ExperienceSubsystem);

		// Only let the last requester to get this far deactivate the plugin
		int32& Count = ExperienceSubsystem->GameFeaturePluginRequestCountMap.FindChecked(PluginURL);
		--Count;

		if (Count == 0)
		{
			ExperienceSubsystem->GameFeaturePluginRequestCountMap.Remove(PluginURL);
			return true;
		}

		return false;
	}

	return true;
}

#endif
