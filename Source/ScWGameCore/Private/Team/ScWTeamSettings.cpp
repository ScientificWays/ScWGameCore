// Scientific Ways

#include "Team/ScWTeamSettings.h"

#include "Tags/ScWCoreTags.h"

#include "Team/ScWTeamAgentInterface.h"

#include "Misc/App.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWTeamSettings)

#define LOCTEXT_NAMESPACE "ScWTeams"

UScWTeamSettings::UScWTeamSettings()
{
	TeamTagToGenericTeamIdMap = {
		{ FScWCoreTags::Team_None, FGenericTeamId::NoTeam },
		{ FScWCoreTags::Team_Player, 0u },
		{ FScWCoreTags::Team_Enemy, 1u }
	};
}

//~ Begin Editor
#if WITH_EDITOR
void UScWTeamSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) // UObject
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ApplySettings();
}

void UScWTeamSettings::PostReloadConfig(FProperty* PropertyThatWasLoaded) // UObject
{
	Super::PostReloadConfig(PropertyThatWasLoaded);

	ApplySettings();
}

void UScWTeamSettings::PostInitProperties() // UObject
{
	Super::PostInitProperties();

	ApplySettings();
}

/*void UScWTeamSettings::OnPlayInEditorStarted() const
{
	// Show a notification toast to remind the user that there's an experience override set
	if (ExperienceOverride.IsValid())
	{
		FNotificationInfo Info(FText::Format(
			LOCTEXT("ExperienceOverrideActive", "Developer Settings Override\nExperience {0}"),
			FText::FromName(ExperienceOverride.PrimaryAssetName)
		));
		Info.ExpireDuration = 2.0f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}
}*/

void UScWTeamSettings::ApplySettings()
{

}
//~ End Editor
#endif

FName UScWTeamSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}

FGenericTeamId UScWTeamSettings::GetGenericTeamIdFromTag(const FGameplayTag& InTeamTag) const
{
	const FGenericTeamId* SampleTeamId = TeamTagToGenericTeamIdMap.Find(InTeamTag);
	ensureReturn(SampleTeamId, FGenericTeamId::NoTeam);
	return *SampleTeamId;
}

const FGameplayTag& UScWTeamSettings::GetTagFromGenericTeamId(FGenericTeamId InTeamId) const
{
	const FGameplayTag* SampleTeamTag = TeamTagToGenericTeamIdMap.FindKey(InTeamId);
	ensureReturn(SampleTeamTag, IScWTeamAgentInterface::TeamNoneTag);
	return *SampleTeamTag;
}

#undef LOCTEXT_NAMESPACE
