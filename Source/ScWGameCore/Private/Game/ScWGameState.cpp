// Scientific Ways

#include "Game/ScWGameState.h"

#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "Experience/ScWExperienceManagerComponent.h"

//#include "World/ScWLevelScriptActor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameState)

class APlayerState;
class FLifetimeProperty;

extern ENGINE_API float GAverageFPS;

AScWGameState::AScWGameState(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AbilitySystemComponent = InObjectInitializer.CreateDefaultSubobject<UScWAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	ExperienceManagerComponent = CreateDefaultSubobject<UScWExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));

	ServerFPS = 0.0f;
}

void AScWGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const // UObject
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ServerFPS);
	DOREPLIFETIME_CONDITION(ThisClass, RecorderPlayerState, COND_ReplayOnly);
}

void AScWGameState::PreInitializeComponents() // AActor
{
	Super::PreInitializeComponents();


}

void AScWGameState::PostInitializeComponents() // AActor
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(/*Owner=*/ this, /*Avatar=*/ this);
}

void AScWGameState::BeginPlay() // AActor
{
	Super::BeginPlay();


}
void AScWGameState::EndPlay(const EEndPlayReason::Type EndPlayReason) // AActor
{
	Super::EndPlay(EndPlayReason);


}

void AScWGameState::Tick(float InDeltaSeconds) // AActor
{
	Super::Tick(InDeltaSeconds);

	if (GetLocalRole() == ROLE_Authority)
	{
		ServerFPS = GAverageFPS;
	}
}

void AScWGameState::AddPlayerState(APlayerState* InPlayerState) // AGameStateBase
{
	Super::AddPlayerState(InPlayerState);
}

void AScWGameState::RemovePlayerState(APlayerState* InPlayerState) // AGameStateBase
{
	//@TODO: This isn't getting called right now (only the 'rich' AGameMode uses it, not AGameModeBase)
	// Need to at least comment the engine code, and possibly move things around
	Super::RemovePlayerState(InPlayerState);
}

void AScWGameState::SeamlessTravelTransitionCheckpoint(bool bToTransitionMap) // AGameStateBase
{
	// Remove inactive and bots
	for (int32 i = PlayerArray.Num() - 1; i >= 0; i--)
	{
		APlayerState* PlayerState = PlayerArray[i];
		if (PlayerState && (PlayerState->IsABot() || PlayerState->IsInactive()))
		{
			RemovePlayerState(PlayerState);
		}
	}
}

UAbilitySystemComponent* AScWGameState::GetAbilitySystemComponent() const // IAbilitySystemInterface
{
	return AbilitySystemComponent;
}

/*void AScWGameState::MulticastMessageToClients_Implementation(const FScWVerbMessage Message)
{
	if (GetNetMode() == NM_Client)
	{
		UGameplayMessageSubsystem::Get(this).BroadcastMessage(Message.Verb, Message);
	}
}

void AScWGameState::MulticastReliableMessageToClients_Implementation(const FScWVerbMessage Message)
{
	MulticastMessageToClients_Implementation(Message);
}*/

float AScWGameState::GetServerFPS() const
{
	return ServerFPS;
}

void AScWGameState::SetRecorderPlayerState(APlayerState* NewPlayerState)
{
	if (RecorderPlayerState == nullptr)
	{
		// Set it and call the rep callback so it can do any record-time setup
		RecorderPlayerState = NewPlayerState;
		OnRep_RecorderPlayerState();
	}
	else
	{
		UE_LOG(LogScWGameCore, Warning, TEXT("SetRecorderPlayerState was called on %s but should only be called once per game on the primary user"), *GetName());
	}
}

APlayerState* AScWGameState::GetRecorderPlayerState() const
{
	// TODO: Maybe auto select it if null?

	return RecorderPlayerState;
}

void AScWGameState::OnRep_RecorderPlayerState()
{
	OnRecorderPlayerStateChangedEvent.Broadcast(RecorderPlayerState);
}
