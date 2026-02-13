// Scientific Ways

#include "Settings/Customization/ScWSettingValueDiscrete_PerfStat.h"

#include "CommonUIVisibilitySubsystem.h"
#include "Performance/ScWPerformanceSettings.h"
#include "Performance/ScWPerformanceStatTypes.h"
#include "Settings/ScWSettingsLocal.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWSettingValueDiscrete_PerfStat)

class ULocalPlayer;

#define LOCTEXT_NAMESPACE "ScWSettings"

//////////////////////////////////////////////////////////////////////

class FGameSettingEditCondition_PerfStatAllowed : public FGameSettingEditCondition
{
public:
	static TSharedRef<FGameSettingEditCondition_PerfStatAllowed> Get(EScWDisplayablePerformanceStat Stat)
	{
		return MakeShared<FGameSettingEditCondition_PerfStatAllowed>(Stat);
	}

	FGameSettingEditCondition_PerfStatAllowed(EScWDisplayablePerformanceStat Stat)
		: AssociatedStat(Stat)
	{
	}

	//~FGameSettingEditCondition interface
	virtual void GatherEditState(const ULocalPlayer* InLocalPlayer, FGameSettingEditableState& InOutEditState) const override
	{
		const FGameplayTagContainer& VisibilityTags = UCommonUIVisibilitySubsystem::GetChecked(InLocalPlayer)->GetVisibilityTags();

		bool bCanShowStat = false;
		for (const FScWPerformanceStatGroup& Group : GetDefault<UScWPerformanceSettings>()->UserFacingPerformanceStats) //@TODO: Move this stuff to per-platform instead of doing vis queries too?
		{
			if (Group.AllowedStats.Contains(AssociatedStat))
			{
				const bool bShowGroup = (Group.VisibilityQuery.IsEmpty() || Group.VisibilityQuery.Matches(VisibilityTags));
				if (bShowGroup)
				{
					bCanShowStat = true;
					break;
				}
			}
		}

		if (!bCanShowStat)
		{
			InOutEditState.Hide(TEXT("Stat is not listed in UScWPerformanceSettings or is suppressed by current platform traits"));
		}
	}
	//~End of FGameSettingEditCondition interface

private:
	EScWDisplayablePerformanceStat AssociatedStat;
};

//////////////////////////////////////////////////////////////////////

UScWSettingValueDiscrete_PerfStat::UScWSettingValueDiscrete_PerfStat()
{
}

void UScWSettingValueDiscrete_PerfStat::SetStat(EScWDisplayablePerformanceStat InStat)
{
	StatToDisplay = InStat;
	SetDevName(FName(*FString::Printf(TEXT("PerfStat_%d"), (int32)StatToDisplay)));
	AddEditCondition(FGameSettingEditCondition_PerfStatAllowed::Get(StatToDisplay));
}

void UScWSettingValueDiscrete_PerfStat::AddMode(FText&& Label, EScWStatDisplayMode Mode)
{
	Options.Emplace(MoveTemp(Label));
	DisplayModes.Add(Mode);
}

void UScWSettingValueDiscrete_PerfStat::OnInitialized()
{
	Super::OnInitialized();

	AddMode(LOCTEXT("PerfStatDisplayMode_None", "None"), EScWStatDisplayMode::Hidden);
	AddMode(LOCTEXT("PerfStatDisplayMode_TextOnly", "Text Only"), EScWStatDisplayMode::TextOnly);
	AddMode(LOCTEXT("PerfStatDisplayMode_GraphOnly", "Graph Only"), EScWStatDisplayMode::GraphOnly);
	AddMode(LOCTEXT("PerfStatDisplayMode_TextAndGraph", "Text and Graph"), EScWStatDisplayMode::TextAndGraph);
}

void UScWSettingValueDiscrete_PerfStat::StoreInitial()
{
	const UScWSettingsLocal* Settings = UScWSettingsLocal::Get();
	InitialMode = Settings->GetPerfStatDisplayState(StatToDisplay);
}

void UScWSettingValueDiscrete_PerfStat::ResetToDefault()
{
	UScWSettingsLocal* Settings = UScWSettingsLocal::Get();
	Settings->SetPerfStatDisplayState(StatToDisplay, EScWStatDisplayMode::Hidden);
	NotifySettingChanged(EGameSettingChangeReason::ResetToDefault);
}

void UScWSettingValueDiscrete_PerfStat::RestoreToInitial()
{
	UScWSettingsLocal* Settings = UScWSettingsLocal::Get();
	Settings->SetPerfStatDisplayState(StatToDisplay, InitialMode);
	NotifySettingChanged(EGameSettingChangeReason::RestoreToInitial);
}

void UScWSettingValueDiscrete_PerfStat::SetDiscreteOptionByIndex(int32 Index)
{
	if (DisplayModes.IsValidIndex(Index))
	{
		const EScWStatDisplayMode DisplayMode = DisplayModes[Index];

		UScWSettingsLocal* Settings = UScWSettingsLocal::Get();
		Settings->SetPerfStatDisplayState(StatToDisplay, DisplayMode);
	}
	NotifySettingChanged(EGameSettingChangeReason::Change);
}

int32 UScWSettingValueDiscrete_PerfStat::GetDiscreteOptionIndex() const
{
	const UScWSettingsLocal* Settings = UScWSettingsLocal::Get();
	return DisplayModes.Find(Settings->GetPerfStatDisplayState(StatToDisplay));
}

TArray<FText> UScWSettingValueDiscrete_PerfStat::GetDiscreteOptions() const
{
	return Options;
}

#undef LOCTEXT_NAMESPACE
