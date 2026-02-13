// Scientific Ways

#include "Player/ScWLocalPlayer.h"

#include "Settings/ScWSettingsLocal.h"
#include "Settings/ScWSettingsShared.h"

#include "AudioMixerBlueprintLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWLocalPlayer)

class UObject;

UScWLocalPlayer::UScWLocalPlayer()
{
	
}

void UScWLocalPlayer::PostInitProperties()
{
	Super::PostInitProperties();

	if (UScWSettingsLocal* LocalSettings = GetLocalSettings())
	{
		LocalSettings->OnAudioOutputDeviceChanged.AddUObject(this, &UScWLocalPlayer::OnAudioOutputDeviceChanged);
	}
}

void UScWLocalPlayer::SwitchController(class APlayerController* PC)
{
	Super::SwitchController(PC);

	OnPlayerControllerChanged(PlayerController);
}

bool UScWLocalPlayer::SpawnPlayActor(const FString& URL, FString& OutError, UWorld* InWorld)
{
	const bool bResult = Super::SpawnPlayActor(URL, OutError, InWorld);

	OnPlayerControllerChanged(PlayerController);

	return bResult;
}

void UScWLocalPlayer::InitOnlineSession()
{
	OnPlayerControllerChanged(PlayerController);

	Super::InitOnlineSession();
}

void UScWLocalPlayer::OnPlayerControllerChanged(APlayerController* NewController)
{
	// Stop listening for changes from the old controller
	FGenericTeamId OldTeamID = FGenericTeamId::NoTeam;
	if (IScWTeamAgentInterface* ControllerAsTeamProvider = Cast<IScWTeamAgentInterface>(LastBoundPC.Get()))
	{
		OldTeamID = ControllerAsTeamProvider->GetGenericTeamId();
		ControllerAsTeamProvider->GetTeamChangedDelegateChecked().RemoveAll(this);
	}

	// Grab the current team ID and listen for future changes
	FGenericTeamId NewTeamID = FGenericTeamId::NoTeam;
	if (IScWTeamAgentInterface* ControllerAsTeamProvider = Cast<IScWTeamAgentInterface>(NewController))
	{
		NewTeamID = ControllerAsTeamProvider->GetGenericTeamId();
		ControllerAsTeamProvider->GetTeamChangedDelegateChecked().AddDynamic(this, &ThisClass::OnControllerChangedTeam);
		LastBoundPC = NewController;
	}

	ConditionalBroadcastTeamChanged(this, OldTeamID, NewTeamID);
}

void UScWLocalPlayer::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	ensureMsgf(false, TEXT("UScWLocalPlayer::SetGenericTeamId should never be called directly as the local player doesn't own team ID, it observes the team of its PlayerController"));
}

FGenericTeamId UScWLocalPlayer::GetGenericTeamId() const
{
	if (IScWTeamAgentInterface* ControllerAsTeamProvider = Cast<IScWTeamAgentInterface>(PlayerController))
	{
		return ControllerAsTeamProvider->GetGenericTeamId();
	}
	else
	{
		return FGenericTeamId::NoTeam;
	}
}

FOnScWTeamIndexChangedDelegate* UScWLocalPlayer::GetOnTeamIndexChangedDelegate()
{
	return &OnTeamChangedDelegate;
}

UScWSettingsLocal* UScWLocalPlayer::GetLocalSettings() const
{
	return UScWSettingsLocal::Get();
}

UScWSettingsShared* UScWLocalPlayer::GetSharedSettings() const
{
	if (!SharedSettings)
	{
		// On PC it's okay to use the sync load because it only checks the disk
		// This could use a platform tag to check for proper save support instead
		bool bCanLoadBeforeLogin = PLATFORM_DESKTOP;
		
		if (bCanLoadBeforeLogin)
		{
			SharedSettings = UScWSettingsShared::LoadOrCreateSettings(this);
		}
		else
		{
			// We need to wait for user login to get the real settings so return temp ones
			SharedSettings = UScWSettingsShared::CreateTemporarySettings(this);
		}
	}

	return SharedSettings;
}

void UScWLocalPlayer::LoadSharedSettingsFromDisk(bool bForceLoad)
{
	FUniqueNetIdRepl CurrentNetId = GetCachedUniqueNetId();
	if (!bForceLoad && SharedSettings && CurrentNetId == NetIdForSharedSettings)
	{
		// Already loaded once, don't reload
		return;
	}

	ensure(UScWSettingsShared::AsyncLoadOrCreateSettings(this, UScWSettingsShared::FOnSettingsLoadedEvent::CreateUObject(this, &UScWLocalPlayer::OnSharedSettingsLoaded)));
}

void UScWLocalPlayer::OnSharedSettingsLoaded(UScWSettingsShared* LoadedOrCreatedSettings)
{
	// The settings are applied before it gets here
	if (ensure(LoadedOrCreatedSettings))
	{
		// This will replace the temporary or previously loaded object which will GC out normally
		SharedSettings = LoadedOrCreatedSettings;

		NetIdForSharedSettings = GetCachedUniqueNetId();
	}
}

void UScWLocalPlayer::OnAudioOutputDeviceChanged(const FString& InAudioOutputDeviceId)
{
	FOnCompletedDeviceSwap DevicesSwappedCallback;
	DevicesSwappedCallback.BindUFunction(this, FName("OnCompletedAudioDeviceSwap"));
	UAudioMixerBlueprintLibrary::SwapAudioOutputDevice(GetWorld(), InAudioOutputDeviceId, DevicesSwappedCallback);
}

void UScWLocalPlayer::OnCompletedAudioDeviceSwap(const FSwapAudioOutputResult& SwapResult)
{
	if (SwapResult.Result == ESwapAudioOutputDeviceResultState::Failure)
	{
	}
}

void UScWLocalPlayer::OnControllerChangedTeam(UObject* TeamAgent, int32 OldTeam, int32 NewTeam)
{
	ConditionalBroadcastTeamChanged(this, IntegerToGenericTeamId(OldTeam), IntegerToGenericTeamId(NewTeam));
}

