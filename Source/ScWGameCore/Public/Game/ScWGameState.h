// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ModularGameState.h"
#include "AbilitySystemInterface.h"

#include "ScWGameState.generated.h"

#define MODULE_API SCWGAMECORE_API

struct FScWVerbMessage;

class APlayerState;
class UAbilitySystemComponent;
class UScWAbilitySystemComponent;
class UObject;
struct FFrame;

/**
 * 
 */
UCLASS(MinimalAPI, Config = Game, meta = (DisplayName = "[ScW] Game State"))
class AScWGameState : public AModularGameStateBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	MODULE_API AScWGameState(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());

	MODULE_API virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; // UObject
	MODULE_API virtual void PreInitializeComponents() override; // AActor
	MODULE_API virtual void PostInitializeComponents() override; // AActor
	MODULE_API virtual void BeginPlay() override; // AActor
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; // AActor
	MODULE_API virtual void Tick(float InDeltaSeconds) override; // AActor
	
	MODULE_API virtual void AddPlayerState(APlayerState* InPlayerState) override; // AGameStateBase
	MODULE_API virtual void RemovePlayerState(APlayerState* InPlayerState) override; // AGameStateBase
	MODULE_API virtual void SeamlessTravelTransitionCheckpoint(bool bToTransitionMap) override; // AGameStateBase
	
	MODULE_API virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; // IAbilitySystemInterface

	// Send a message that all clients will (probably) get
	// (use only for client notifications like eliminations, server join messages, etc... that can handle being lost)
	//UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category = "ScW | GameState")
	//MODULE_API void MulticastMessageToClients(const FScWVerbMessage Message);

	// Send a message that all clients will be guaranteed to get
	// (use only for client notifications that cannot handle being lost)
	//UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "ScW | GameState")
	//MODULE_API void MulticastReliableMessageToClients(const FScWVerbMessage Message);

	// Gets the server's FPS, replicated to clients
	MODULE_API float GetServerFPS() const;

	// Indicate the local player state is recording a replay
	MODULE_API void SetRecorderPlayerState(APlayerState* NewPlayerState);

	// Gets the player state that recorded the replay, if valid
	MODULE_API APlayerState* GetRecorderPlayerState() const;

	// Delegate called when the replay player state changes
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecorderPlayerStateChanged, APlayerState*);
	FOnRecorderPlayerStateChanged OnRecorderPlayerStateChangedEvent;

private:
	// Handles loading and managing the current gameplay experience
	UPROPERTY()
	TObjectPtr<class UScWExperienceManagerComponent> ExperienceManagerComponent;

	// The ability system component subobject for game-wide things (primarily gameplay cues)
	UPROPERTY(VisibleAnywhere, Category = "ScW | GameState")
	TObjectPtr<class UScWAbilitySystemComponent> AbilitySystemComponent;

protected:

	UPROPERTY(Replicated)
	float ServerFPS;

	// The player state that recorded a replay, it is used to select the right pawn to follow
	// This is only set in replay streams and is not replicated normally
	UPROPERTY(Transient, ReplicatedUsing = OnRep_RecorderPlayerState)
	TObjectPtr<APlayerState> RecorderPlayerState;

	UFUNCTION()
	MODULE_API void OnRep_RecorderPlayerState();
};

#undef MODULE_API
