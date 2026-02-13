// Scientific Ways

#include "Performance/ScWPerformanceSettings.h"

#include "Performance/ScWPerformanceStatTypes.h"

#include "Engine/PlatformSettingsManager.h"
#include "Misc/EnumRange.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWPerformanceSettings)

//////////////////////////////////////////////////////////////////////

UScWPlatformSpecificRenderingSettings::UScWPlatformSpecificRenderingSettings()
{
	MobileFrameRateLimits.Append({ 20, 30, 45, 60, 90, 120 });
}

const UScWPlatformSpecificRenderingSettings* UScWPlatformSpecificRenderingSettings::Get()
{
	UScWPlatformSpecificRenderingSettings* Result = UPlatformSettingsManager::Get().GetSettingsForPlatform<ThisClass>();
	check(Result);
	return Result;
}

//////////////////////////////////////////////////////////////////////

UScWPerformanceSettings::UScWPerformanceSettings()
{
	PerPlatformSettings.Initialize(UScWPlatformSpecificRenderingSettings::StaticClass());

	CategoryName = TEXT("Game");

	DesktopFrameRateLimits.Append({ 30, 60, 120, 144, 160, 165, 180, 200, 240, 360 });

	// Default to all stats are allowed
	FScWPerformanceStatGroup& StatGroup = UserFacingPerformanceStats.AddDefaulted_GetRef();
	for (EScWDisplayablePerformanceStat PerfStat : TEnumRange<EScWDisplayablePerformanceStat>())
	{
		StatGroup.AllowedStats.Add(PerfStat);
	}
}

