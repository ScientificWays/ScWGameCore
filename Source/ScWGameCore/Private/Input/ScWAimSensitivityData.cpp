// Scientific Ways

#include "Input/ScWAimSensitivityData.h"

//#include "Settings/ScWSettingsShared.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWAimSensitivityData)

UScWAimSensitivityData::UScWAimSensitivityData(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	SensitivityMap =
	{
		{ EScWGamepadSensitivity::Slow,			0.5f },
		{ EScWGamepadSensitivity::SlowPlus,		0.75f },
		{ EScWGamepadSensitivity::SlowPlusPlus,	0.9f },
		{ EScWGamepadSensitivity::Normal,		1.0f },
		{ EScWGamepadSensitivity::NormalPlus,	1.1f },
		{ EScWGamepadSensitivity::NormalPlusPlus,1.25f },
		{ EScWGamepadSensitivity::Fast,			1.5f },
		{ EScWGamepadSensitivity::FastPlus,		1.75f },
		{ EScWGamepadSensitivity::FastPlusPlus,	2.0f },
		{ EScWGamepadSensitivity::Insane,		2.5f },
	};
}

const float UScWAimSensitivityData::SensitivtyEnumToFloat(const EScWGamepadSensitivity InSensitivity) const
{
	if (const float* Sens = SensitivityMap.Find(InSensitivity))
	{
		return *Sens;
	}
	return 1.0f;
}

