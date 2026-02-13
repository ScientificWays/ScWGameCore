// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "CommonPlayerController.h"
#include "Team/ScWTeamAgentInterface.h"

#include "ScWPlayerController.generated.h"

#define MODULE_API SCWGAMECORE_API

struct FGenericTeamId;

//class AScWHUD;
class AScWPlayerState;
class APawn;
class APlayerState;
class FPrimitiveComponentId;
class IInputInterface;
class UScWAbilitySystemComponent;
class UScWSettingsShared;
class UObject;
class UPlayer;
struct FFrame;

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Player Controller"))
class AScWPlayerController : public ACommonPlayerController, public IAbilitySystemInterface, public IScWTeamAgentInterface
{
	GENERATED_BODY()

public:

	AScWPlayerController(const FObjectInitializer& InObjectInitializer);

//~ Begin Initialize
protected:
	virtual void PostInitializeComponents() override; // AActor
	virtual void SetPlayer(UPlayer* InPlayer) override; // APlayerController
	virtual void BeginPlay() override; // AActor
	virtual void EndPlay(const EEndPlayReason::Type InReason) override; // AActor
//~ End Initialize

//~ Begin Player State
protected:
	virtual void InitPlayerState() override; // AController
	virtual void CleanupPlayerState() override; // AController
	virtual void OnRep_PlayerState() override; // AController
	virtual void OnPlayerStateChanged(); // Called when the player state is set or cleared
private:
	void BroadcastOnPlayerStateChanged();
//~ End Player State

//~ Begin Settings
protected:
	void OnSettingsChanged(UScWSettingsShared* Settings);
//~ End Settings

//~ Begin Ability System
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // IAbilitySystemInterface
//~ End Ability System

//~ Begin Pawn
protected:
	virtual void OnPossess(APawn* InPawn) override; // AController
	virtual void OnUnPossess() override; // AController
	virtual void PawnPendingDestroy(APawn* InPawn) override; // AController
//~ End Pawn
	
//~ Begin Team
public:
	MODULE_API virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override; // IGenericTeamAgentInterface
	MODULE_API virtual FGenericTeamId GetGenericTeamId() const override; // IGenericTeamAgentInterface
	MODULE_API virtual FOnScWTeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() override; // IScWTeamAgentInterface
private:

	UFUNCTION()
	void OnPlayerStateChangedTeam(UObject* TeamAgent, int32 OldTeam, int32 NewTeam);

	UPROPERTY()
	TObjectPtr<APlayerState> LastSeenPlayerState;

	UPROPERTY()
	FOnScWTeamIndexChangedDelegate OnTeamChangedDelegate;
//~ End Team

//~ Begin Camera
protected:
	virtual void CalcCamera(float InDeltaSeconds, FMinimalViewInfo& InOutResult) override; // AActor

	UPROPERTY(Category = "Camera", EditAnywhere, BlueprintReadOnly)
	bool bTryFindCalcCameraComponentOnPostInitializeComponents;

	UPROPERTY(Category = "Camera", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UCameraComponent> CalcCameraComponent;
//~ End Camera

//~ Begin Input
public:

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "InSource", KeyWords = "HasMouse, HasCursor"))
	MODULE_API bool HasShowMouseCursorSource(UObject* InSource) const { return ShowMouseCursorSourceSet.Contains(InSource); }

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "InSource", KeyWords = "AddMouse, AddCursor"))
	MODULE_API void AddShowMouseCursorSource(UObject* InSource) { ShowMouseCursorSourceSet.Add(InSource); }
	
	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "InSource", KeyWords = "RemoveMouse, RemoveCursor"))
	MODULE_API void RemoveShowMouseCursorSource(UObject* InSource) { ShowMouseCursorSourceSet.Remove(InSource); }

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "InSource", KeyWords = "HasBlock, HasIgnore"))
	MODULE_API bool HasMovementInputBlockSource(UObject* InSource) const { return MovementInputBlockSourceSet.Contains(InSource); }

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "InSource", KeyWords = "AddBlock, AddIgnore"))
	MODULE_API void AddMovementInputBlockSource(UObject* InSource) { MovementInputBlockSourceSet.Add(InSource); }

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "InSource", KeyWords = "RemoveBlock, RemoveIgnore"))
	MODULE_API void RemoveMovementInputBlockSource(UObject* InSource) { MovementInputBlockSourceSet.Remove(InSource); }

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "InSource", KeyWords = "HasBlock, HasIgnore"))
	MODULE_API bool HasLookInputBlockSource(UObject* InSource) const { return LookInputBlockSourceSet.Contains(InSource); }

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "InSource", KeyWords = "AddBlock, AddIgnore"))
	MODULE_API void AddLookInputBlockSource(UObject* InSource) { LookInputBlockSourceSet.Add(InSource); }

	UFUNCTION(Category = "Input", BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "InSource", KeyWords = "RemoveBlock, RemoveIgnore"))
	MODULE_API void RemoveLookInputBlockSource(UObject* InSource) { LookInputBlockSourceSet.Remove(InSource); }

	UPROPERTY(Category = "Input", BlueprintReadWrite)
	float MouseInputScale;

protected:
	virtual bool ShouldShowMouseCursor() const override; // APlayerController
	virtual bool IsMoveInputIgnored() const override; // AController
	virtual bool IsLookInputIgnored() const override; // AController
	virtual void SetupInputComponent() override; // APlayerController
	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused) override; // APlayerController
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override; // APlayerController
	virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override; // APlayerController
	//void InputMouseLook(const FInputActionInstance& InActionInstance);

	virtual void UpdateForceFeedback(IInputInterface* InputInterface, const int32 ControllerId) override; // APlayerController

	/*UPROPERTY(Category = "Input", BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	int32 DefaultInputMappingContextPriority;

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	FModifyContextOptions DefaultInputMappingContextOptions;

	UPROPERTY(Category = "Input", EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> MouseLookAction;

	UPROPERTY(Category = "Input", BlueprintAssignable)
	FBoolSignature OnIsUsingGamepadChangedDelegate;

	UPROPERTY(Category = "Input", BlueprintReadOnly, Transient)
	bool bIsUsingGamepad;*/

	UPROPERTY(Transient)
	TSet<TObjectPtr<UObject>> ShowMouseCursorSourceSet;

	UPROPERTY(Transient)
	TSet<TObjectPtr<UObject>> MovementInputBlockSourceSet;

	UPROPERTY(Transient)
	TSet<TObjectPtr<UObject>> LookInputBlockSourceSet;
//~ End Input
	
//~ Begin Cheats
public:
	MODULE_API virtual void AddCheats(bool bForce) override; // APlayerController

	// Run a cheat command on the server.
	UFUNCTION(Reliable, Server, WithValidation)
	MODULE_API void Server_Cheat(const FString& Msg);

	// Run a cheat command on the server for all players.
	UFUNCTION(Reliable, Server, WithValidation)
	MODULE_API void Server_CheatAll(const FString& Msg);
//~ End Cheats

//~ Begin Viewport
public:

	UFUNCTION(BlueprintCallable, Category = "Viewport")
	MODULE_API bool GetHitResultUnderScreenCenter(ETraceTypeQuery InTraceChannel, bool bInTraceComplex, FHitResult& OutHitResult) const;
//~ End Viewport
};

// A player controller used for replay capture and playback
/*UCLASS()
class AScWReplayPlayerController : public AScWPlayerController
{
	GENERATED_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual void SmoothTargetViewRotation(APawn* TargetPawn, float DeltaSeconds) override;
	virtual bool ShouldRecordClientReplay() override;

	// Callback for when the game state's RecorderPlayerState gets replicated during replay playback
	void RecorderPlayerStateUpdated(APlayerState* NewRecorderPlayerState);

	// Callback for when the followed player state changes pawn
	UFUNCTION()
	void OnPlayerStatePawnSet(APlayerState* ChangedPlayerState, APawn* NewPlayerPawn, APawn* OldPlayerPawn);

	// The player state we are currently following
	UPROPERTY(Transient)
	TObjectPtr<APlayerState> FollowedPlayerState;
};*/

#undef MODULE_API
