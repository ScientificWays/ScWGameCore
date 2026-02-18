// Scientific Ways

#include "Player/ScWPlayerState.h"

#include "Player/ScWPlayerController.h"

#include "AbilitySystem/ScWAbilitySet.h"
#include "Tags/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"
//#include "AbilitySystem/Attributes/ScWCombatSet.h"
//#include "AbilitySystem/Attributes/ScWHealthSet.h"

#include "Character/ScWPawnData.h"
#include "Character/ScWPawnExtensionComponent.h"

#include "Experience/ScWExperienceManagerComponent.h"

//@TODO: Would like to isolate this a bit better to get the pawn data in here without this having to know about other stuff
#include "Game/ScWGameMode.h"
//#include "Messages/ScWVerbMessage.h"

#include "Team/ScWTeamSettings.h"

//#include "GameFramework/GameplayMessageSubsystem.h"
#include "Components/GameFrameworkComponentManager.h"

const FName AScWPlayerState::NAME_PlayerAbilitiesReady("PlayerAbilitiesReady");

AScWPlayerState::AScWPlayerState(const FObjectInitializer& InObjectInitializer)
{
	AbilitySystemComponent = InObjectInitializer.CreateDefaultSubobject<UScWAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// These attribute sets will be detected by AbilitySystemComponent::InitializeComponent. Keeping a reference so that the sets don't get garbage collected before that.
	//HealthSet = CreateDefaultSubobject<UScWHealthSet>(TEXT("HealthSet"));
	//CombatSet = CreateDefaultSubobject<UScWCombatSet>(TEXT("CombatSet"));

	// AbilitySystemComponent needs to be updated at a high frequency.
	SetNetUpdateFrequency(100.0f);

	TeamTag = FScWCoreTags::Team_Player;

	MySquadID = INDEX_NONE;
}

void AScWPlayerState::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	SetTeamTag(TeamTag);
}

void AScWPlayerState::Reset()
{
	Super::Reset();
}

void AScWPlayerState::ClientInitialize(AController* C)
{
	Super::ClientInitialize(C);

	if (UScWPawnExtensionComponent* PawnExtComp = UScWPawnExtensionComponent::GetPawnExtensionComponent(GetPawn()))
	{
		PawnExtComp->CheckDefaultInitialization();
	}
}

void AScWPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	//@TODO: Copy stats
}

void AScWPlayerState::OnDeactivated()
{
	bool bDestroyDeactivatedPlayerState = false;

	switch (GetPlayerConnectionType())
	{
		case EScWPlayerConnectionType::Player:
		case EScWPlayerConnectionType::InactivePlayer:
			//@TODO: Ask the experience if we should destroy disconnecting players immediately or leave them around
			// (e.g., for long running servers where they might build up if lots of players cycle through)
			bDestroyDeactivatedPlayerState = true;
			break;
		default:
			bDestroyDeactivatedPlayerState = true;
			break;
	}

	SetPlayerConnectionType(EScWPlayerConnectionType::InactivePlayer);

	if (bDestroyDeactivatedPlayerState)
	{
		Destroy();
	}
}

void AScWPlayerState::OnReactivated()
{
	if (GetPlayerConnectionType() == EScWPlayerConnectionType::InactivePlayer)
	{
		SetPlayerConnectionType(EScWPlayerConnectionType::Player);
	}
}

void AScWPlayerState::OnExperienceLoaded(const UScWExperience* /*CurrentExperience*/)
{
	if (AScWGameMode* ScWGameMode = GetWorld()->GetAuthGameMode<AScWGameMode>())
	{
		if (const UScWPawnData* NewPawnData = ScWGameMode->GetPawnDataForController(GetOwningController()))
		{
			SetPawnData(NewPawnData);
		}
		else
		{
			UE_LOG(LogScWGameCore, Error, TEXT("AScWPlayerState::OnExperienceLoaded(): Unable to find PawnData to initialize player state [%s]!"), *GetNameSafe(this));
		}
	}
}

void AScWPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, PawnData, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MyPlayerConnectionType, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, TeamTag, SharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MySquadID, SharedParams);

	SharedParams.Condition = ELifetimeCondition::COND_SkipOwner;
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, ReplicatedViewRotation, SharedParams);

	DOREPLIFETIME(ThisClass, StatTags);
}

FRotator AScWPlayerState::GetReplicatedViewRotation() const
{
	// Could replace this with custom replication
	return ReplicatedViewRotation;
}

void AScWPlayerState::SetReplicatedViewRotation(const FRotator& NewRotation)
{
	if (NewRotation != ReplicatedViewRotation)
	{
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, ReplicatedViewRotation, this);
		ReplicatedViewRotation = NewRotation;
	}
}

AScWPlayerController* AScWPlayerState::GetScWPlayerController() const
{
	return Cast<AScWPlayerController>(GetOwner());
}

UAbilitySystemComponent* AScWPlayerState::GetAbilitySystemComponent() const
{
	return GetScWAbilitySystemComponent();
}

void AScWPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());

	UWorld* World = GetWorld();
	if (World && World->IsGameWorld() && World->GetNetMode() != NM_Client)
	{
		AGameStateBase* GameState = GetWorld()->GetGameState();
		check(GameState);
		UScWExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UScWExperienceManagerComponent>();
		check(ExperienceComponent);
		ExperienceComponent->CallOrRegister_OnExperienceLoaded(FOnScWExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
	}
}

void AScWPlayerState::SetPawnData(const UScWPawnData* InPawnData)
{
	check(InPawnData);

	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	if (PawnData)
	{
		UE_LOG(LogScWGameCore, Error, TEXT("Trying to set PawnData [%s] on player state [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(this), *GetNameSafe(PawnData));
		return;
	}
	MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, PawnData, this);
	PawnData = InPawnData;

	for (const UScWAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, NAME_PlayerAbilitiesReady);

	ForceNetUpdate();
}

void AScWPlayerState::OnRep_PawnData()
{

}

void AScWPlayerState::SetPlayerConnectionType(EScWPlayerConnectionType NewType)
{
	MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, MyPlayerConnectionType, this);
	MyPlayerConnectionType = NewType;
}

void AScWPlayerState::SetSquadID(int32 NewSquadId)
{
	if (HasAuthority())
	{
		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, MySquadID, this);

		MySquadID = NewSquadId;
	}
}

//~ Begin Team
FGenericTeamId AScWPlayerState::GetGenericTeamId() const // IGenericTeamAgentInterface
{
	return GetDefault<UScWTeamSettings>()->GetGenericTeamIdFromTag(TeamTag);
}

void AScWPlayerState::SetGenericTeamId(const FGenericTeamId& NewTeamID) // IGenericTeamAgentInterface
{
	if (HasAuthority())
	{
		const FGameplayTag OldTeamTag = GetTeamTag();

		MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, TeamTag, this);
		TeamTag = GetDefault<UScWTeamSettings>()->GetTagFromGenericTeamId(NewTeamID);
		ConditionalBroadcastTeamChanged(this, OldTeamTag, TeamTag);
	}
	else
	{
		UE_LOG(LogScWGameCore, Error, TEXT("Cannot set team for %s on non-authority"), *GetPathName(this));
	}
}

void AScWPlayerState::SetTeamTag(const FGameplayTag& InTeamTag)
{
	TeamTag = InTeamTag;
	SetGenericTeamId(GetDefault<UScWTeamSettings>()->GetGenericTeamIdFromTag(TeamTag));
}

FOnScWTeamIndexChangedDelegate* AScWPlayerState::GetOnTeamIndexChangedDelegate() // IScWTeamAgentInterface
{
	return &OnTeamChangedDelegate;
}

void AScWPlayerState::OnRep_TeamTag(FGameplayTag InPrevTeamTag)
{
	ConditionalBroadcastTeamChanged(this, InPrevTeamTag, TeamTag);
}
//~ End Team

void AScWPlayerState::OnRep_MySquadID()
{
	//@TODO: Let the squad subsystem know (once that exists)
}

void AScWPlayerState::AddStatTagStack(FGameplayTag Tag, int32 StackCount)
{
	StatTags.AddStack(Tag, StackCount);
}

void AScWPlayerState::RemoveStatTagStack(FGameplayTag Tag, int32 StackCount)
{
	StatTags.RemoveStack(Tag, StackCount);
}

int32 AScWPlayerState::GetStatTagStackCount(FGameplayTag Tag) const
{
	return StatTags.GetStackCount(Tag);
}

bool AScWPlayerState::HasStatTag(FGameplayTag Tag) const
{
	return StatTags.ContainsTag(Tag);
}

/*void AScWPlayerState::ClientBroadcastMessage_Implementation(const FScWVerbMessage Message)
{
	// This check is needed to prevent running the action when in standalone mode
	if (GetNetMode() == NM_Client)
	{
		UGameplayMessageSubsystem::Get(this).BroadcastMessage(Message.Verb, Message);
	}
}*/
