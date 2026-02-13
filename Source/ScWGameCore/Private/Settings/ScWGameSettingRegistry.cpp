// Scientific Ways

#include "Settings/ScWGameSettingRegistry.h"

#include "Player/ScWLocalPlayer.h"

#include "Settings/ScWSettingsLocal.h"
#include "Settings/ScWSettingsShared.h"

#include "GameSettingCollection.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameSettingRegistry)

DEFINE_LOG_CATEGORY(LogScWGameSettingRegistry);

#define LOCTEXT_NAMESPACE "ScW"

//--------------------------------------
// UScWGameSettingRegistry
//--------------------------------------

UScWGameSettingRegistry::UScWGameSettingRegistry()
{
}

UScWGameSettingRegistry* UScWGameSettingRegistry::Get(UScWLocalPlayer* InLocalPlayer)
{
	UScWGameSettingRegistry* Registry = FindObject<UScWGameSettingRegistry>(InLocalPlayer, TEXT("ScWGameSettingRegistry"), true);
	if (Registry == nullptr)
	{
		Registry = NewObject<UScWGameSettingRegistry>(InLocalPlayer, TEXT("ScWGameSettingRegistry"));
		Registry->Initialize(InLocalPlayer);
	}

	return Registry;
}

bool UScWGameSettingRegistry::IsFinishedInitializing() const
{
	if (Super::IsFinishedInitializing())
	{
		if (UScWLocalPlayer* LocalPlayer = Cast<UScWLocalPlayer>(OwningLocalPlayer))
		{
			if (LocalPlayer->GetSharedSettings() == nullptr)
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

void UScWGameSettingRegistry::OnInitialize(ULocalPlayer* InLocalPlayer)
{
	UScWLocalPlayer* ScWLocalPlayer = Cast<UScWLocalPlayer>(InLocalPlayer);

	VideoSettings = InitializeVideoSettings(ScWLocalPlayer);
	InitializeVideoSettings_FrameRates(VideoSettings, ScWLocalPlayer);
	RegisterSetting(VideoSettings);

	AudioSettings = InitializeAudioSettings(ScWLocalPlayer);
	RegisterSetting(AudioSettings);

	GameplaySettings = InitializeGameplaySettings(ScWLocalPlayer);
	RegisterSetting(GameplaySettings);

	MouseAndKeyboardSettings = InitializeMouseAndKeyboardSettings(ScWLocalPlayer);
	RegisterSetting(MouseAndKeyboardSettings);

	GamepadSettings = InitializeGamepadSettings(ScWLocalPlayer);
	RegisterSetting(GamepadSettings);
}

void UScWGameSettingRegistry::SaveChanges()
{
	Super::SaveChanges();
	
	if (UScWLocalPlayer* LocalPlayer = Cast<UScWLocalPlayer>(OwningLocalPlayer))
	{
		// Game user settings need to be applied to handle things like resolution, this saves indirectly
		LocalPlayer->GetLocalSettings()->ApplySettings(false);
		
		LocalPlayer->GetSharedSettings()->ApplySettings();
		LocalPlayer->GetSharedSettings()->SaveSettings();
	}
}

#undef LOCTEXT_NAMESPACE

