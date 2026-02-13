// Scientific Ways

#include "Settings/Customization/ScWSettingAction_SafeZoneEditor.h"

#include "Player/ScWLocalPlayer.h"

#include "Settings/ScWGameSettingRegistry.h"

#include "Widgets/Layout/SSafeZone.h"
#include "DataSource/GameSettingDataSource.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWSettingAction_SafeZoneEditor)

class UGameSetting;

#define LOCTEXT_NAMESPACE "ScWSettings"

UScWSettingAction_SafeZoneEditor::UScWSettingAction_SafeZoneEditor()
{
	SafeZoneValueSetting = NewObject<UScWSettingValueScalarDynamic_SafeZoneValue>();
	SafeZoneValueSetting->SetDevName(TEXT("SafeZoneValue"));
	SafeZoneValueSetting->SetDisplayName(LOCTEXT("SafeZoneValue_Name", "Safe Zone Value"));
	SafeZoneValueSetting->SetDescriptionRichText(LOCTEXT("SafeZoneValue_Description", "The safezone area percentage."));
	SafeZoneValueSetting->SetDefaultValue(0.0f);
	SafeZoneValueSetting->SetDynamicGetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(GetSafeZone));
	SafeZoneValueSetting->SetDynamicSetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(SetSafeZone));
	SafeZoneValueSetting->SetDisplayFormat([](double SourceValue, double NormalizedValue){ return FText::AsNumber(SourceValue); });
	SafeZoneValueSetting->SetSettingParent(this);
}

TArray<UGameSetting*> UScWSettingAction_SafeZoneEditor::GetChildSettings()
{
	return { SafeZoneValueSetting };
}

void UScWSettingValueScalarDynamic_SafeZoneValue::ResetToDefault()
{
	Super::ResetToDefault();
	SSafeZone::SetGlobalSafeZoneScale(TOptional<float>(DefaultValue.Get(0.0f)));
}

void UScWSettingValueScalarDynamic_SafeZoneValue::RestoreToInitial()
{
	Super::RestoreToInitial();
	SSafeZone::SetGlobalSafeZoneScale(TOptional<float>(InitialValue));
}

#undef LOCTEXT_NAMESPACE
