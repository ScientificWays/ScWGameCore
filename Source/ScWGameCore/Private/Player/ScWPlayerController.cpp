// Scientific Ways

#include "Player/ScWPlayerController.h"

#include "AbilitySystem/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"

//#include "Game/ScWGameState.h"
#include "Game/ScWCheatManager.h"

#include "Player/ScWLocalPlayer.h"
#include "Player/ScWPlayerState.h"
//#include "Camera/ScWPlayerCameraManager.h"
//#include "UI/ScWHUD.h"

#include "Settings/ScWSettingsLocal.h"
#include "Settings/ScWSettingsShared.h"
#include "Settings/ScWDeveloperSettings.h"

//#include "ReplaySubsystem.h"
//#include "Replays/ScWReplaySubsystem.h"
#include "GameMapsSettings.h"
#include "CommonInputTypeEnum.h"
#include "CommonInputSubsystem.h"

/*#if WITH_RPC_REGISTRY
#include "Tests/ScWGameplayRpcRegistrationComponent.h"
#include "HttpServerModule.h"
#endif*/

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWPlayerController)

namespace ScW
{
	namespace Input
	{
		static int32 ShouldAlwaysPlayForceFeedback = 0;
		static FAutoConsoleVariableRef CVarShouldAlwaysPlayForceFeedback(TEXT("ScWPC.ShouldAlwaysPlayForceFeedback"),
			ShouldAlwaysPlayForceFeedback,
			TEXT("Should force feedback effects be played, even if the last input device was not a gamepad?"));
	}
}

AScWPlayerController::AScWPlayerController(const FObjectInitializer& InObjectInitializer)
{
	//PlayerCameraManagerClass = AScWPlayerCameraManager::StaticClass();

#if USING_CHEAT_MANAGER
	CheatClass = UScWCheatManager::StaticClass();
#endif // #if USING_CHEAT_MANAGER

	bTryFindCalcCameraComponentOnPostInitializeComponents = true;
}

//~ Begin Initialize
void AScWPlayerController::PostInitializeComponents() // AActor
{
	Super::PostInitializeComponents();

	if (bTryFindCalcCameraComponentOnPostInitializeComponents && (CalcCameraComponent == nullptr))
	{
		// Look for the first active camera component and assign that to CalcCameraComponent
		TInlineComponentArray<UCameraComponent*> CameraComponents;
		GetComponents(CameraComponents);

		for (UCameraComponent* SampleCameraComponent : CameraComponents)
		{
			if (SampleCameraComponent->IsActive())
			{
				CalcCameraComponent = SampleCameraComponent;
				break;
			}
		}
	}
}

void AScWPlayerController::SetPlayer(UPlayer* InPlayer) // APlayerController
{
	Super::SetPlayer(InPlayer);

	if (const UScWLocalPlayer* ScWLocalPlayer = Cast<UScWLocalPlayer>(InPlayer))
	{
		UScWSettingsShared* UserSettings = ScWLocalPlayer->GetSharedSettings();
		UserSettings->OnSettingChanged.AddUObject(this, &ThisClass::OnSettingsChanged);

		OnSettingsChanged(UserSettings);
	}
}

void AScWPlayerController::BeginPlay() // AActor
{
	Super::BeginPlay();

/*#if WITH_RPC_REGISTRY
	FHttpServerModule::Get().StartAllListeners();
	int32 RpcPort = 0;
	if (FParse::Value(FCommandLine::Get(), TEXT("rpcport="), RpcPort))
	{
		UScWGameplayRpcRegistrationComponent* ObjectInstance = UScWGameplayRpcRegistrationComponent::GetInstance();
		if (ObjectInstance && ObjectInstance->IsValidLowLevel())
		{
			ObjectInstance->RegisterAlwaysOnHttpCallbacks();
			ObjectInstance->RegisterInMatchHttpCallbacks();
		}
	}
#endif*/
	SetActorHiddenInGame(false);
}

void AScWPlayerController::EndPlay(const EEndPlayReason::Type InReason) // AActor
{
	

	Super::EndPlay(InReason);
}
//~ End Initialize

//~ Begin Player State
void AScWPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	BroadcastOnPlayerStateChanged();
}

void AScWPlayerController::CleanupPlayerState()
{
	Super::CleanupPlayerState();
	BroadcastOnPlayerStateChanged();
}

void AScWPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	BroadcastOnPlayerStateChanged();

	// When we're a client connected to a remote server, the player controller may replicate later than the PlayerState and AbilitySystemComponent.
	// However, TryActivateAbilitiesOnSpawn depends on the player controller being replicated in order to check whether on-spawn abilities should
	// execute locally. Therefore once the PlayerController exists and has resolved the PlayerState, try once again to activate on-spawn abilities.
	// On other net modes the PlayerController will never replicate late, so ScWASC's own TryActivateAbilitiesOnSpawn calls will succeed. The handling 
	// here is only for when the PlayerState and ASC replicated before the PC and incorrectly thought the abilities were not for the local player.
	if (GetWorld()->IsNetMode(NM_Client))
	{
		if (AScWPlayerState* ScWPS = GetPlayerState<AScWPlayerState>())
		{
			if (UScWAbilitySystemComponent* ScWASC = ScWPS->GetScWAbilitySystemComponent())
			{
				ScWASC->RefreshAbilityActorInfo();
				ScWASC->TryActivateAbilitiesOnSpawn();
			}
		}
	}
}

void AScWPlayerController::OnPlayerStateChanged()
{
	// Empty, place for derived classes to implement without having to hook all the other events
}

void AScWPlayerController::BroadcastOnPlayerStateChanged()
{
	OnPlayerStateChanged();

	// Unbind from the old player state, if any
	FGenericTeamId OldTeamID = FGenericTeamId::NoTeam;
	if (LastSeenPlayerState != nullptr)
	{
		if (IScWTeamAgentInterface* PlayerStateTeamInterface = Cast<IScWTeamAgentInterface>(LastSeenPlayerState))
		{
			OldTeamID = PlayerStateTeamInterface->GetGenericTeamId();
			PlayerStateTeamInterface->GetTeamChangedDelegateChecked().RemoveAll(this);
		}
	}

	// Bind to the new player state, if any
	FGenericTeamId NewTeamID = FGenericTeamId::NoTeam;
	if (PlayerState != nullptr)
	{
		if (IScWTeamAgentInterface* PlayerStateTeamInterface = Cast<IScWTeamAgentInterface>(PlayerState))
		{
			NewTeamID = PlayerStateTeamInterface->GetGenericTeamId();
			PlayerStateTeamInterface->GetTeamChangedDelegateChecked().AddDynamic(this, &ThisClass::OnPlayerStateChangedTeam);
		}
	}

	// Broadcast the team change (if it really has)
	ConditionalBroadcastTeamChanged(this, OldTeamID, NewTeamID);

	LastSeenPlayerState = PlayerState;
}
//~ End Player State

//~ Begin Settings
void AScWPlayerController::OnSettingsChanged(UScWSettingsShared* InSettings)
{
	bForceFeedbackEnabled = InSettings->GetForceFeedbackEnabled();
}
//~ End Settings

//~ Begin Ability System
UAbilitySystemComponent* AScWPlayerController::GetAbilitySystemComponent() const // IAbilitySystemInterface
{
	return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPawn());
}
//~ End Ability System

//~ Begin Camera
void AScWPlayerController::CalcCamera(float InDeltaSeconds, FMinimalViewInfo& InOutResult) // AActor
{
	if (CalcCameraComponent)
	{
		CalcCameraComponent->GetCameraView(InDeltaSeconds, InOutResult);
	}
	else
	{
		Super::CalcCamera(InDeltaSeconds, InOutResult);
	}
}
//~ End Camera

//~ Begin Pawn
void AScWPlayerController::OnPossess(APawn* InPawn) // AController
{
	Super::OnPossess(InPawn);

#if WITH_SERVER_CODE && WITH_EDITOR
	if (GIsEditor && (InPawn != nullptr) && (GetPawn() == InPawn))
	{
		for (const FScWCheatToRun& CheatRow : GetDefault<UScWDeveloperSettings>()->CheatsToRun)
		{
			if (CheatRow.Phase == ECheatExecutionTime::OnPlayerPawnPossession)
			{
				ConsoleCommand(CheatRow.Cheat, /*bWriteToLog=*/ true);
			}
		}
	}
#endif
}

void AScWPlayerController::OnUnPossess() // AController
{
	// Make sure the pawn that is being unpossessed doesn't remain our ASC's avatar actor
	if (APawn* PawnBeingUnpossessed = GetPawn())
	{
		if (UScWAbilitySystemComponent* PlayerASC = UScWAbilitySystemComponent::TryGetFromActor(PlayerState))
		{
			if (PlayerASC->GetAvatarActor() == PawnBeingUnpossessed)
			{
				PlayerASC->SetAvatarActor(nullptr);
			}
		}
	}
	Super::OnUnPossess();
}

void AScWPlayerController::PawnPendingDestroy(APawn* InPawn) // AController
{


	Super::PawnPendingDestroy(InPawn);
}
//~ End Pawn

//~ Begin Team
void AScWPlayerController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	UE_LOG(LogScWGameCore, Error, TEXT("You can't set the team ID on a player controller (%s); it's driven by the associated player state"), *GetPathNameSafe(this));
}

FGenericTeamId AScWPlayerController::GetGenericTeamId() const
{
	if (const IScWTeamAgentInterface* PSWithTeamInterface = Cast<IScWTeamAgentInterface>(PlayerState))
	{
		return PSWithTeamInterface->GetGenericTeamId();
	}
	return FGenericTeamId::NoTeam;
}

FOnScWTeamIndexChangedDelegate* AScWPlayerController::GetOnTeamIndexChangedDelegate()
{
	return &OnTeamChangedDelegate;
}

void AScWPlayerController::OnPlayerStateChangedTeam(UObject* TeamAgent, int32 OldTeam, int32 NewTeam)
{
	ConditionalBroadcastTeamChanged(this, IntegerToGenericTeamId(OldTeam), IntegerToGenericTeamId(NewTeam));
}
//~ End Team

//~ Begin Input
bool AScWPlayerController::ShouldShowMouseCursor() const // APlayerController
{
	return Super::ShouldShowMouseCursor() || !ShowMouseCursorSourceSet.IsEmpty();
}

bool AScWPlayerController::IsMoveInputIgnored() const // AController
{
	return Super::IsMoveInputIgnored() || !MovementInputBlockSourceSet.IsEmpty();
}

bool AScWPlayerController::IsLookInputIgnored() const // AController
{
	return Super::IsLookInputIgnored() || !LookInputBlockSourceSet.IsEmpty();
}

void AScWPlayerController::SetupInputComponent() // APlayerController
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);
	if (!EnhancedInputComponent)
	{
		return;
	}
	//ensure(MouseLookAction);
	/*if (MouseLookAction)
	{
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AScWPlayerController::InputMouseLook);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Completed, this, &AScWPlayerController::InputMouseLook);
	}*/

}

void AScWPlayerController::PreProcessInput(const float DeltaTime, const bool bGamePaused) // APlayerController
{
	Super::PreProcessInput(DeltaTime, bGamePaused);


}

void AScWPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused) // APlayerController
{
	if (UScWAbilitySystemComponent* PlayerASC = UScWAbilitySystemComponent::TryGetFromActor(PlayerState))
	{
		PlayerASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
	Super::PostProcessInput(DeltaTime, bGamePaused);
}

bool AScWPlayerController::InputKey(const FInputKeyEventArgs& InEventArgs) // APlayerController
{
	bool bOutResult = Super::InputKey(InEventArgs);
	if (bOutResult)
	{
		/*bool bNewIsGamepad = InEventArgs.IsGamepad();
		if (bNewIsGamepad != bIsUsingGamepad)
		{
			bIsUsingGamepad = bNewIsGamepad;
			OnIsUsingGamepadChangedDelegate.Broadcast(bIsUsingGamepad);

			UScWGameInstance* GameInstance = GetGameInstance<UScWGameInstance>();
			ensureIf(GameInstance)
			{
				GameInstance->OnPlayerIsUsingGamepadChangedDelegate.Broadcast(this, bIsUsingGamepad);
			}
		}*/
	}
	return bOutResult;
}

/*void AScWPlayerController::InputMouseLook(const FInputActionInstance& InActionInstance)
{
	FVector2D InputValue = InActionInstance.GetValue().Get<FVector2D>();

	float ViewRoll = GetControlRotation().Roll;
	if (ViewRoll != 0.0f)
	{
		InputValue = InputValue.GetRotated(ViewRoll);
	}
	AddPitchInput(InputValue.Y * MouseInputScale);
	AddYawInput(InputValue.X * MouseInputScale);
}*/

void AScWPlayerController::UpdateForceFeedback(IInputInterface* InputInterface, const int32 ControllerId) // APlayerController
{
	if (bForceFeedbackEnabled)
	{
		if (const UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(GetLocalPlayer()))
		{
			const ECommonInputType CurrentInputType = CommonInputSubsystem->GetCurrentInputType();
			if (ScW::Input::ShouldAlwaysPlayForceFeedback || CurrentInputType == ECommonInputType::Gamepad || CurrentInputType == ECommonInputType::Touch)
			{
				InputInterface->SetForceFeedbackChannelValues(ControllerId, ForceFeedbackValues);
				return;
			}
		}
	}
	InputInterface->SetForceFeedbackChannelValues(ControllerId, FForceFeedbackValues());
}
//~ End Input

//~ Begin Cheats
void AScWPlayerController::AddCheats(bool bForce) // APlayerController
{
#if USING_CHEAT_MANAGER
	Super::AddCheats(true);
#else //#if USING_CHEAT_MANAGER
	Super::AddCheats(bForce);
#endif // #else //#if USING_CHEAT_MANAGER
}

void AScWPlayerController::Server_Cheat_Implementation(const FString& Msg)
{
#if USING_CHEAT_MANAGER
	if (CheatManager)
	{
		UE_LOG(LogScWGameCore, Warning, TEXT("Server_Cheat: %s"), *Msg);
		ClientMessage(ConsoleCommand(Msg));
	}
#endif // #if USING_CHEAT_MANAGER
}

bool AScWPlayerController::Server_Cheat_Validate(const FString& Msg)
{
	return true;
}

void AScWPlayerController::Server_CheatAll_Implementation(const FString& Msg)
{
#if USING_CHEAT_MANAGER
	if (CheatManager)
	{
		UE_LOG(LogScWGameCore, Warning, TEXT("Server_CheatAll: %s"), *Msg);
		for (TActorIterator<AScWPlayerController> It(GetWorld()); It; ++It)
		{
			AScWPlayerController* SamplePC = (*It);
			if (SamplePC)
			{
				SamplePC->ClientMessage(SamplePC->ConsoleCommand(Msg));
			}
		}
	}
#endif // #if USING_CHEAT_MANAGER
}

bool AScWPlayerController::Server_CheatAll_Validate(const FString& Msg)
{
	return true;
}
//~ End Cheats

//~ Begin Viewport
bool AScWPlayerController::GetHitResultUnderScreenCenter(ETraceTypeQuery InTraceChannel, bool bInTraceComplex, FHitResult& OutHitResult) const
{
	FVector2D ViewportSize = FVector2D::ZeroVector;

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UGameViewportClient* ViewportClient = LocalPlayer->ViewportClient)
		{
			ViewportClient->GetViewportSize(ViewportSize);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return GetHitResultAtScreenPosition(ViewportSize * 0.5f, InTraceChannel, bInTraceComplex, OutHitResult);
}
//~ End Viewport

//////////////////////////////////////////////////////////////////////
// AScWReplayPlayerController

/*void AScWReplayPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// The state may go invalid at any time due to scrubbing during a replay
	if (!IsValid(FollowedPlayerState))
	{
		UWorld* World = GetWorld();

		// Listen for changes for both recording and playback
		if (AScWGameState* GameState = Cast<AScWGameState>(World->GetGameState()))
		{
			if (!GameState->OnRecorderPlayerStateChangedEvent.IsBoundToObject(this))
			{
				GameState->OnRecorderPlayerStateChangedEvent.AddUObject(this, &ThisClass::RecorderPlayerStateUpdated);
			}
			if (APlayerState* RecorderState = GameState->GetRecorderPlayerState())
			{
				RecorderPlayerStateUpdated(RecorderState);
			}
		}
	}
}

void AScWReplayPlayerController::SmoothTargetViewRotation(APawn* TargetPawn, float DeltaSeconds)
{
	// Default behavior is to interpolate to TargetViewRotation which is set from APlayerController::TickActor but it's not very smooth

	Super::SmoothTargetViewRotation(TargetPawn, DeltaSeconds);
}

bool AScWReplayPlayerController::ShouldRecordClientReplay()
{
	return false;
}

void AScWReplayPlayerController::RecorderPlayerStateUpdated(APlayerState* NewRecorderPlayerState)
{
	if (NewRecorderPlayerState)
	{
		FollowedPlayerState = NewRecorderPlayerState;

		// Bind to when pawn changes and call now
		NewRecorderPlayerState->OnPawnSet.AddUniqueDynamic(this, &AScWReplayPlayerController::OnPlayerStatePawnSet);
		OnPlayerStatePawnSet(NewRecorderPlayerState, NewRecorderPlayerState->GetPawn(), nullptr);
	}
}

void AScWReplayPlayerController::OnPlayerStatePawnSet(APlayerState* ChangedPlayerState, APawn* NewPlayerPawn, APawn* OldPlayerPawn)
{
	if (ChangedPlayerState == FollowedPlayerState)
	{
		SetViewTarget(NewPlayerPawn);
	}
}*/

