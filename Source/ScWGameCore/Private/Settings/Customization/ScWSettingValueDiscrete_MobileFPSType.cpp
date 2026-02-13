// Scientific Ways

#include "Settings/Customization/ScWSettingValueDiscrete_MobileFPSType.h"

#include "Performance/ScWPerformanceSettings.h"
#include "Settings/ScWSettingsLocal.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWSettingValueDiscrete_MobileFPSType)

#define LOCTEXT_NAMESPACE "ScWSettings"

UScWSettingValueDiscrete_MobileFPSType::UScWSettingValueDiscrete_MobileFPSType()
{
}

void UScWSettingValueDiscrete_MobileFPSType::OnInitialized()
{
	Super::OnInitialized();

	const UScWPlatformSpecificRenderingSettings* PlatformSettings = UScWPlatformSpecificRenderingSettings::Get();
	const UScWSettingsLocal* UserSettings = UScWSettingsLocal::Get();

	for (int32 TestLimit : PlatformSettings->MobileFrameRateLimits)
	{
		if (UScWSettingsLocal::IsSupportedMobileFramePace(TestLimit))
		{
			FPSOptions.Add(TestLimit, MakeLimitString(TestLimit));
		}
	}

	const int32 FirstFrameRateWithQualityLimit = UserSettings->GetFirstFrameRateWithQualityLimit();
	if (FirstFrameRateWithQualityLimit > 0)
	{
		SetWarningRichText(FText::Format(LOCTEXT("MobileFPSType_Note", "<strong>Note: Changing the framerate setting to {0} or higher might lower your Quality Presets.</>"), MakeLimitString(FirstFrameRateWithQualityLimit)));
	}
}

int32 UScWSettingValueDiscrete_MobileFPSType::GetDefaultFPS() const
{
	return UScWSettingsLocal::GetDefaultMobileFrameRate();
}

FText UScWSettingValueDiscrete_MobileFPSType::MakeLimitString(int32 Number)
{
	return FText::Format(LOCTEXT("MobileFrameRateOption", "{0} FPS"), FText::AsNumber(Number));
}

void UScWSettingValueDiscrete_MobileFPSType::StoreInitial()
{
	InitialValue = GetValue();
}

void UScWSettingValueDiscrete_MobileFPSType::ResetToDefault()
{
	SetValue(GetDefaultFPS(), EGameSettingChangeReason::ResetToDefault);
}

void UScWSettingValueDiscrete_MobileFPSType::RestoreToInitial()
{
	SetValue(InitialValue, EGameSettingChangeReason::RestoreToInitial);
}

void UScWSettingValueDiscrete_MobileFPSType::SetDiscreteOptionByIndex(int32 Index)
{
	TArray<int32> FPSOptionsModes;
	FPSOptions.GenerateKeyArray(FPSOptionsModes);

	int32 NewMode = FPSOptionsModes.IsValidIndex(Index) ? FPSOptionsModes[Index] : GetDefaultFPS();

	SetValue(NewMode, EGameSettingChangeReason::Change);
}

int32 UScWSettingValueDiscrete_MobileFPSType::GetDiscreteOptionIndex() const
{
	TArray<int32> FPSOptionsModes;
	FPSOptions.GenerateKeyArray(FPSOptionsModes);
	return FPSOptionsModes.IndexOfByKey(GetValue());
}

TArray<FText> UScWSettingValueDiscrete_MobileFPSType::GetDiscreteOptions() const
{
	TArray<FText> Options;
	FPSOptions.GenerateValueArray(Options);

	return Options;
}

int32 UScWSettingValueDiscrete_MobileFPSType::GetValue() const
{
	return UScWSettingsLocal::Get()->GetDesiredMobileFrameRateLimit();
}

void UScWSettingValueDiscrete_MobileFPSType::SetValue(int32 NewLimitFPS, EGameSettingChangeReason InReason)
{
	UScWSettingsLocal::Get()->SetDesiredMobileFrameRateLimit(NewLimitFPS);

	NotifySettingChanged(InReason);
}

#undef LOCTEXT_NAMESPACE

