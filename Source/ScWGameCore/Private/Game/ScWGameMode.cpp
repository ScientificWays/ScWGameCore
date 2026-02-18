// Scientific Ways

#include "Game/ScWGameMode.h"

#include "System/ScWAssetManager.h"

#include "Experience/ScWExperience.h"
#include "Experience/ScWExperienceDescription.h"
#include "Experience/ScWExperienceManagerComponent.h"
//#include "Player/ScWPlayerSpawningManagerComponent.h"
//#include "CommonUserSubsystem.h"
//#include "CommonSessionSubsystem.h"
#include "GameMapsSettings.h"

#include "Game/ScWGameState.h"
#include "Game/ScWGameSession.h"
#include "Game/ScWGameInstance.h"

#include "Player/ScWHUD.h"
#include "Player/ScWPlayerState.h"
#include "Player/ScWPlayerController.h"

#include "Development/ScWDeveloperSettings.h"

#include "World/ScWWorldSettings.h"
#include "World/ScWLevelScriptActor.h"

#include "Character/ScWPawnData.h"
#include "Character/ScWPawnExtensionComponent.h"
#include "Character/ScWCharacter.h"

#include "Engine/PlayerStartPIE.h"
#include "AssetRegistry/AssetData.h"

AScWGameMode::AScWGameMode(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	GameStateClass = AScWGameState::StaticClass();
	GameSessionClass = AScWGameSession::StaticClass();
	PlayerControllerClass = AScWPlayerController::StaticClass();
	//ReplaySpectatorPlayerControllerClass = AScWReplayPlayerController::StaticClass();
	PlayerStateClass = AScWPlayerState::StaticClass();
	DefaultPawnClass = AScWCharacter::StaticClass();
	HUDClass = AScWHUD::StaticClass();

	DefaultPlayerName = FText::FromString(TEXT("zanayn"));
}

const UScWPawnData* AScWGameMode::GetPawnDataForController(const AController* InController) const
{
	// See if pawn data is already set on the player state
	if (InController != nullptr)
	{
		if (const AScWPlayerState* TargetPlayerState = InController->GetPlayerState<AScWPlayerState>())
		{
			if (const UScWPawnData* PawnData = TargetPlayerState->GetPawnData<UScWPawnData>())
			{
				return PawnData;
			}
		}
	}
	// If not, fall back to the the default for the current experience
	check(GameState);
	UScWExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UScWExperienceManagerComponent>();
	check(ExperienceComponent);

	if (ExperienceComponent->IsExperienceLoaded())
	{
		const UScWExperience* Experience = ExperienceComponent->GetCurrentExperienceChecked();
		if (Experience->DefaultPawnDataAsset != nullptr)
		{
			return Experience->DefaultPawnDataAsset;
		}
		// Experience is loaded and there's still no pawn data, fall back to the default for now
		return UScWAssetManager::Get().GetDefaultPawnData();
	}
	// Experience not loaded yet, so there is no pawn data to be had
	return nullptr;
}

void AScWGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// Wait for the next frame to give time to initialize startup settings
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void AScWGameMode::HandleMatchAssignmentIfNotExpectingOne()
{
	FPrimaryAssetId ExperienceId;
	FString ExperienceIdSource;

	// Precedence order (highest wins)
	//  - Matchmaking assignment (if present)
	//  - URL Options override
	//  - Developer Settings (PIE only)
	//  - Command Line override
	//  - World Settings
	//  - Dedicated server
	//  - Default experience

	UWorld* World = GetWorld();

	if (!ExperienceId.IsValid() && UGameplayStatics::HasOption(OptionsString, TEXT("Experience")))
	{
		const FString ExperienceFromOptions = UGameplayStatics::ParseOption(OptionsString, TEXT("Experience"));
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType(UScWExperience::StaticClass()->GetFName()), FName(*ExperienceFromOptions));
		ExperienceIdSource = TEXT("OptionsString");
	}
	if (!ExperienceId.IsValid() && World->IsPlayInEditor())
	{
		ExperienceId = GetDefault<UScWDeveloperSettings>()->ExperienceOverride;
		ExperienceIdSource = TEXT("DeveloperSettings");
	}
	// See if the command line wants to set the experience
	if (!ExperienceId.IsValid())
	{
		FString ExperienceFromCommandLine;
		if (FParse::Value(FCommandLine::Get(), TEXT("Experience="), ExperienceFromCommandLine))
		{
			ExperienceId = FPrimaryAssetId::ParseTypeAndName(ExperienceFromCommandLine);
			if (!ExperienceId.PrimaryAssetType.IsValid())
			{
				ExperienceId = FPrimaryAssetId(FPrimaryAssetType(UScWExperience::StaticClass()->GetFName()), FName(*ExperienceFromCommandLine));
			}
			ExperienceIdSource = TEXT("CommandLine");
		}
	}
	// See if the world settings has a default experience
	if (!ExperienceId.IsValid())
	{
		if (AScWWorldSettings* TypedWorldSettings = Cast<AScWWorldSettings>(GetWorldSettings()))
		{
			ExperienceId = TypedWorldSettings->GetDefaultExperience();
			ExperienceIdSource = TEXT("WorldSettings");
		}
	}
	UAssetManager& AssetManager = UAssetManager::Get();
	FAssetData Dummy;
	if (ExperienceId.IsValid() && !AssetManager.GetPrimaryAssetData(ExperienceId, /*out*/ Dummy))
	{
		UE_LOG(LogScWGameCore, Error, TEXT("EXPERIENCE: Wanted to use %s but couldn't find it, falling back to the default)"), *ExperienceId.ToString());
		ExperienceId = FPrimaryAssetId();
	}
	// Final fallback to the default experience
	if (!ExperienceId.IsValid())
	{
		/*if (TryDedicatedServerLogin())
		{
			// This will start to host as a dedicated server
			return;
		}*/
		//@TODO: Pull this from a config setting or something
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("ScWExperience"), FName("Exp_DefaultExperience"));
		ExperienceIdSource = TEXT("Default");
	}
	OnMatchAssignmentGiven(ExperienceId, ExperienceIdSource);
}

/*bool AScWGameMode::TryDedicatedServerLogin()
{
	// Some basic code to register as an active dedicated server, this would be heavily modified by the game
	FString DefaultMap = UGameMapsSettings::GetGameDefaultMap();
	UWorld* World = GetWorld();
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance && World && World->GetNetMode() == NM_DedicatedServer && World->URL.Map == DefaultMap)
	{
		// Only register if this is the default map on a dedicated server
		UCommonUserSubsystem* UserSubsystem = GameInstance->GetSubsystem<UCommonUserSubsystem>();

		// Dedicated servers may need to do an online login
		UserSubsystem->OnUserInitializeComplete.AddDynamic(this, &AScWGameMode::OnUserInitializedForDedicatedServer);

		// There are no local users on dedicated server, but index 0 means the default platform user which is handled by the online login code
		if (!UserSubsystem->TryToLoginForOnlinePlay(0))
		{
			OnUserInitializedForDedicatedServer(nullptr, false, FText(), ECommonUserPrivilege::CanPlayOnline, ECommonUserOnlineContext::Default);
		}
		return true;
	}
	return false;
}*/

/*void AScWGameMode::HostDedicatedServerMatch(ECommonSessionOnlineMode OnlineMode)
{
	FPrimaryAssetType UserExperienceType = UScWExperienceDescription::StaticClass()->GetFName();

	// Figure out what UserFacingExperience to load
	FPrimaryAssetId UserExperienceId;
	FString UserExperienceFromCommandLine;
	if (FParse::Value(FCommandLine::Get(), TEXT("UserExperience="), UserExperienceFromCommandLine) ||
		FParse::Value(FCommandLine::Get(), TEXT("Playlist="), UserExperienceFromCommandLine))
	{
		UserExperienceId = FPrimaryAssetId::ParseTypeAndName(UserExperienceFromCommandLine);
		if (!UserExperienceId.PrimaryAssetType.IsValid())
		{
			UserExperienceId = FPrimaryAssetId(FPrimaryAssetType(UserExperienceType), FName(*UserExperienceFromCommandLine));
		}
	}

	// Search for the matching experience, it's fine to force load them because we're in dedicated server startup
	UScWAssetManager& AssetManager = UScWAssetManager::Get();
	TSharedPtr<FStreamableHandle> Handle = AssetManager.LoadPrimaryAssetsWithType(UserExperienceType);
	if (ensure(Handle.IsValid()))
	{
		Handle->WaitUntilComplete();
	}

	TArray<UObject*> UserExperiences;
	AssetManager.GetPrimaryAssetObjectList(UserExperienceType, UserExperiences);
	UScWExperienceDescription* FoundExperience = nullptr;
	UScWExperienceDescription* DefaultExperience = nullptr;

	for (UObject* Object : UserExperiences)
	{
		UScWExperienceDescription* UserExperience = Cast<UScWExperienceDescription>(Object);
		if (ensure(UserExperience))
		{
			if (UserExperience->GetPrimaryAssetId() == UserExperienceId)
			{
				FoundExperience = UserExperience;
				break;
			}

			if (UserExperience->bIsDefaultExperience && DefaultExperience == nullptr)
			{
				DefaultExperience = UserExperience;
			}
		}
	}

	if (FoundExperience == nullptr)
	{
		FoundExperience = DefaultExperience;
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (ensure(FoundExperience && GameInstance))
	{
		// Actually host the game
		UCommonSession_HostSessionRequest* HostRequest = FoundExperience->CreateHostingRequest(this);
		if (ensure(HostRequest))
		{
			HostRequest->OnlineMode = OnlineMode;

			// TODO override other parameters?

			UCommonSessionSubsystem* SessionSubsystem = GameInstance->GetSubsystem<UCommonSessionSubsystem>();
			SessionSubsystem->HostSession(nullptr, HostRequest);

			// This will handle the map travel
		}
	}
	check(false); // Dedicated server hosting not implemented yet
}*/

/*void AScWGameMode::OnUserInitializedForDedicatedServer(const UCommonUserInfo* UserInfo, bool bSuccess, FText Error, ECommonUserPrivilege RequestedPrivilege, ECommonUserOnlineContext OnlineContext)
{
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		// Unbind
		UCommonUserSubsystem* UserSubsystem = GameInstance->GetSubsystem<UCommonUserSubsystem>();
		UserSubsystem->OnUserInitializeComplete.RemoveDynamic(this, &AScWGameMode::OnUserInitializedForDedicatedServer);

		// Dedicated servers do not require user login, but some online subsystems may expect it
		if (bSuccess && ensure(UserInfo))
		{
			UE_LOG(LogScWGameCore, Log, TEXT("Dedicated server user login succeeded for id %s, starting online server"), *UserInfo->GetNetId().ToString());
		}
		else
		{
			UE_LOG(LogScWGameCore, Log, TEXT("Dedicated server user login unsuccessful, starting online server as login is not required"));
		}

		HostDedicatedServerMatch(ECommonSessionOnlineMode::Online);
	}
	check(false); // Dedicated server hosting not implemented yet
}*/

void AScWGameMode::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId, const FString& ExperienceIdSource)
{
	if (ExperienceId.IsValid())
	{
		UE_LOG(LogScWGameCore, Log, TEXT("Identified experience %s (Source: %s)"), *ExperienceId.ToString(), *ExperienceIdSource);

		UScWExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UScWExperienceManagerComponent>();
		check(ExperienceComponent);
		ExperienceComponent->SetCurrentExperience(ExperienceId);
	}
	else
	{
		UE_LOG(LogScWGameCore, Error, TEXT("Failed to identify experience, loading screen will stay up forever"));
	}
}

void AScWGameMode::OnExperienceLoaded(const UScWExperience* CurrentExperience)
{
	// Spawn any players that are already attached
	//@TODO: Here we're handling only *player* controllers, but in GetDefaultPawnClassForController_Implementation we skipped all controllers
	// GetDefaultPawnClassForController_Implementation might only be getting called for players anyways
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(*Iterator);
		if ((PC != nullptr) && (PC->GetPawn() == nullptr))
		{
			if (PlayerCanRestart(PC))
			{
				RestartPlayer(PC);
			}
		}
	}
}

bool AScWGameMode::IsExperienceLoaded() const
{
	check(GameState);
	UScWExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UScWExperienceManagerComponent>();
	check(ExperienceComponent);

	return ExperienceComponent->IsExperienceLoaded();
}

UClass* AScWGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (const UScWPawnData* PawnData = GetPawnDataForController(InController))
	{
		if (PawnData->PawnClass)
		{
			return PawnData->PawnClass;
		}
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

APawn* AScWGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* InNewPlayer, const FTransform& InSpawnTransform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// Never save the default player pawns into a map.
	SpawnInfo.bDeferConstruction = true;

	if (UClass* PawnClass = GetDefaultPawnClassForController(InNewPlayer))
	{
		if (APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnClass, InSpawnTransform, SpawnInfo))
		{
			if (UScWPawnExtensionComponent* PawnExtComp = UScWPawnExtensionComponent::GetPawnExtensionComponent(SpawnedPawn))
			{
				if (const UScWPawnData* PawnData = GetPawnDataForController(InNewPlayer))
				{
					PawnExtComp->SetPawnData(PawnData);
				}
				else
				{
					UE_LOG(LogScWGameCore, Error, TEXT("Game mode was unable to set PawnData on the spawned pawn [%s]."), *GetNameSafe(SpawnedPawn));
				}
			}
			//SpawnedPawn->FinishSpawning(InSpawnTransform);
			return SpawnedPawn;
		}
		else
		{
			UE_LOG(LogScWGameCore, Error, TEXT("Game mode was unable to spawn Pawn of class [%s] at [%s]."), *GetNameSafe(PawnClass), *InSpawnTransform.ToHumanReadableString());
		}
	}
	else
	{
		UE_LOG(LogScWGameCore, Error, TEXT("Game mode was unable to spawn Pawn due to NULL pawn class."));
	}
	return Super::SpawnDefaultPawnAtTransform_Implementation(InNewPlayer, InSpawnTransform);
}

bool AScWGameMode::ShouldSpawnAtStartSpot(AController* Player)
{
	// We never want to use the start spot, always use the spawn management component.
	return false;
}

void AScWGameMode::HandleStartingNewPlayer_Implementation(APlayerController* InNewPlayer)
{
	// Delay starting new players until the experience has been loaded
	// (players who log in prior to that will be started by OnExperienceLoaded)
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(InNewPlayer);
	}
}

AActor* AScWGameMode::ChoosePlayerStart_Implementation(AController* InPlayer)
{
	/*if (UScWPlayerSpawningManagerComponent* PlayerSpawningComponent = GameState->FindComponentByClass<UScWPlayerSpawningManagerComponent>())
	{
		return PlayerSpawningComponent->ChoosePlayerStart(InPlayer);
	}*/

	// Old framework implementation
	UWorld* World = GetWorld();
	ensureReturn(World, nullptr);

	for (TActorIterator<APlayerStartPIE> It(World); It; ++It)
	{
		APlayerStartPIE* PlayFromHereStart = *It;
		ensureContinue(PlayFromHereStart);
		return PlayFromHereStart; // Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
	}
	if (AScWLevelScriptActor* LevelScriptActor = Cast<AScWLevelScriptActor>(World->GetLevelScriptActor()))
	{
		if (AActor* LevelPlayerStart = LevelScriptActor->BP_ChoosePlayerStart(InPlayer))
		{
			return LevelPlayerStart;
		}
	}
	return Super::ChoosePlayerStart_Implementation(InPlayer);
}

void AScWGameMode::FinishRestartPlayer(AController* InNewPlayer, const FRotator& StartRotation)
{
	/*if (UScWPlayerSpawningManagerComponent* PlayerSpawningComponent = GameState->FindComponentByClass<UScWPlayerSpawningManagerComponent>())
	{
		PlayerSpawningComponent->FinishRestartPlayer(InNewPlayer, StartRotation);
	}*/
	Super::FinishRestartPlayer(InNewPlayer, StartRotation);
}

bool AScWGameMode::PlayerCanRestart_Implementation(APlayerController* InPlayerController)
{
	return ControllerCanRestart(InPlayerController);
}

bool AScWGameMode::ControllerCanRestart(AController* InController)
{
	if (APlayerController* PC = Cast<APlayerController>(InController))
	{
		if (!Super::PlayerCanRestart_Implementation(PC))
		{
			return false;
		}
	}
	else
	{
		// Bot version of Super::PlayerCanRestart_Implementation
		if ((InController == nullptr) || InController->IsPendingKillPending())
		{
			return false;
		}
	}
	/*if (UScWPlayerSpawningManagerComponent* PlayerSpawningComponent = GameState->FindComponentByClass<UScWPlayerSpawningManagerComponent>())
	{
		return PlayerSpawningComponent->ControllerCanRestart(Controller);
	}*/
	return true;
}

void AScWGameMode::InitGameState()
{
	Super::InitGameState();

	// Listen for the experience load to complete	
	UScWExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UScWExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded(FOnScWExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void AScWGameMode::GenericPlayerInitialization(AController* InNewPlayer)
{
	Super::GenericPlayerInitialization(InNewPlayer);

	OnGameModePlayerInitialized.Broadcast(this, InNewPlayer);
}

void AScWGameMode::RequestPlayerRestartNextFrame(AController* Controller, bool bForceReset)
{
	if (bForceReset && (Controller != nullptr))
	{
		Controller->Reset();
	}
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		GetWorldTimerManager().SetTimerForNextTick(PC, &APlayerController::ServerRestartPlayer_Implementation);
	}
	/*else if (AScWPlayerBotController* BotController = Cast<AScWPlayerBotController>(Controller))
	{
		GetWorldTimerManager().SetTimerForNextTick(BotController, &AScWPlayerBotController::ServerRestartController);
	}*/
}

bool AScWGameMode::UpdatePlayerStartSpot(AController* Player, const FString& Portal, FString& OutErrorMessage)
{
	// Do nothing, we'll wait until PostLogin when we try to spawn the player for real.
	// Doing anything right now is no good, systems like team assignment haven't even occurred yet.
	return true;
}

void AScWGameMode::FailedToRestartPlayer(AController* InNewPlayer)
{
	Super::FailedToRestartPlayer(InNewPlayer);

	// If we tried to spawn a pawn and it failed, lets try again *note* check if there's actually a pawn class
	// before we try this forever.
	if (UClass* PawnClass = GetDefaultPawnClassForController(InNewPlayer))
	{
		if (APlayerController* NewPC = Cast<APlayerController>(InNewPlayer))
		{
			// If it's a player don't loop forever, maybe something changed and they can no longer restart if so stop trying.
			if (PlayerCanRestart(NewPC))
			{
				RequestPlayerRestartNextFrame(InNewPlayer, false);
			}
			else
			{
				UE_LOG(LogScWGameCore, Verbose, TEXT("FailedToRestartPlayer(%s) and PlayerCanRestart returned false, so we're not going to try again."), *GetPathNameSafe(InNewPlayer));
			}
		}
		else
		{
			RequestPlayerRestartNextFrame(InNewPlayer, false);
		}
	}
	else
	{
		UE_LOG(LogScWGameCore, Verbose, TEXT("FailedToRestartPlayer(%s) but there's no pawn class so giving up."), *GetPathNameSafe(InNewPlayer));
	}
}
