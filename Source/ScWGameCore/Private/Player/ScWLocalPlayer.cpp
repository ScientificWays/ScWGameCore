// Scientific Ways

#include "Player/ScWLocalPlayer.h"

#include "Tags/ScWCoreTags.h"

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
	FGameplayTag OldTeamTag;
	if (IScWTeamAgentInterface* ControllerAsTeamProvider = Cast<IScWTeamAgentInterface>(LastBoundPC.Get()))
	{
		OldTeamTag = ControllerAsTeamProvider->GetTeamTag();
		ControllerAsTeamProvider->GetTeamChangedDelegateChecked().RemoveAll(this);
	}
	// Grab the current team ID and listen for future changes
	FGameplayTag NewTeamTag;
	if (IScWTeamAgentInterface* ControllerAsTeamProvider = Cast<IScWTeamAgentInterface>(NewController))
	{
		NewTeamTag = ControllerAsTeamProvider->GetTeamTag();
		ControllerAsTeamProvider->GetTeamChangedDelegateChecked().AddDynamic(this, &ThisClass::OnControllerChangedTeam);
		LastBoundPC = NewController;
	}
	ConditionalBroadcastTeamChanged(this, OldTeamTag, NewTeamTag);
}

//~ Begin Team
FGenericTeamId UScWLocalPlayer::GetGenericTeamId() const // IGenericTeamAgentInterface
{
	const IScWTeamAgentInterface* PlayerControllerTeamInterface = Cast<IScWTeamAgentInterface>(PlayerController);
	ensureReturn(PlayerControllerTeamInterface, FGenericTeamId::NoTeam);
	return PlayerControllerTeamInterface->GetGenericTeamId();
}

void UScWLocalPlayer::SetGenericTeamId(const FGenericTeamId& InTeamID) // IGenericTeamAgentInterface
{
	IScWTeamAgentInterface* PlayerControllerTeamInterface = Cast<IScWTeamAgentInterface>(PlayerController);
	ensureReturn(PlayerControllerTeamInterface);
	PlayerControllerTeamInterface->SetGenericTeamId(InTeamID);
}

const FGameplayTag& UScWLocalPlayer::GetTeamTag() const // IScWTeamAgentInterface
{
	const IScWTeamAgentInterface* PlayerControllerTeamInterface = Cast<IScWTeamAgentInterface>(PlayerController);
	ensureReturn(PlayerControllerTeamInterface, IScWTeamAgentInterface::TeamNoneTag);
	return PlayerControllerTeamInterface->GetTeamTag();
}

void UScWLocalPlayer::SetTeamTag(const FGameplayTag& InTeamTag) // IScWTeamAgentInterface
{
	IScWTeamAgentInterface* PlayerControllerTeamInterface = Cast<IScWTeamAgentInterface>(PlayerController);
	ensureReturn(PlayerControllerTeamInterface);
	PlayerControllerTeamInterface->SetTeamTag(InTeamTag);
}

FOnScWTeamIndexChangedDelegate* UScWLocalPlayer::GetOnTeamIndexChangedDelegate() // IScWTeamAgentInterface
{
	return &OnTeamChangedDelegate;
}

void UScWLocalPlayer::OnControllerChangedTeam(UObject* TeamAgent, const FGameplayTag& InPrevTeamTag, const FGameplayTag& InNewTeamTag)
{
	ConditionalBroadcastTeamChanged(this, InPrevTeamTag, InNewTeamTag);
}
//~ End Team

//~ Begin Settings
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
//~ End Settings
