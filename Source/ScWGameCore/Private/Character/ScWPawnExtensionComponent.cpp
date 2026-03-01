// Scientific Ways

#include "Character/ScWPawnExtensionComponent.h"

#include "Tags/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "Character/ScWPawnData.h"

#include "Components/GameFrameworkComponentManager.h"
#include "Components/GameFrameworkComponentDelegates.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWPawnExtensionComponent)

class FLifetimeProperty;
class UActorComponent;

const FName UScWPawnExtensionComponent::NAME_ActorFeatureName("PawnExtension");

UScWPawnExtensionComponent::UScWPawnExtensionComponent(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	PawnData = nullptr;
	AbilitySystemComponent = nullptr;
}

void UScWPawnExtensionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UScWPawnExtensionComponent, PawnData);
}

void UScWPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	const APawn* Pawn = GetPawn<APawn>();
	ensureAlwaysMsgf((Pawn != nullptr), TEXT("ScWPawnExtensionComponent on [%s] can only be added to Pawn actors."), *GetNameSafe(GetOwner()));

	TArray<UActorComponent*> PawnExtensionComponents;
	Pawn->GetComponents(UScWPawnExtensionComponent::StaticClass(), PawnExtensionComponents);
	ensureAlwaysMsgf((PawnExtensionComponents.Num() == 1), TEXT("Only one ScWPawnExtensionComponent should exist on [%s]."), *GetNameSafe(GetOwner()));

	// Register with the init state system early, this will only work if this is a game world
	RegisterInitStateFeature();
}

void UScWPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Listen for changes to all features
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);
	
	// Notifies state manager that we have spawned, then try rest of default initialization
	ensure(TryToChangeInitState(FScWCoreTags::InitState_Spawned));
	CheckDefaultInitialization();
}

void UScWPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UninitializeAbilitySystem();
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void UScWPawnExtensionComponent::SetPawnData(const UScWPawnData* InPawnData)
{
	check(InPawnData);

	APawn* Pawn = GetPawnChecked<APawn>();
	if (Pawn->GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	if (HasBegunPlay() && PawnData)
	{
		UE_LOG(LogScWGameCore, Error, TEXT("Trying to set PawnData [%s] on pawn [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(Pawn), *GetNameSafe(PawnData));
		return;
	}
	PawnData = InPawnData;
	Pawn->ForceNetUpdate();

	CheckDefaultInitialization();
}

void UScWPawnExtensionComponent::OnRep_PawnData()
{
	CheckDefaultInitialization();
}

void UScWPawnExtensionComponent::InitializeAbilitySystem(UScWAbilitySystemComponent* InASC, AActor* InOwnerActor)
{
	check(InASC);
	check(InOwnerActor);

	if (AbilitySystemComponent == InASC)
	{
		// The ability system component hasn't changed.
		return;
	}
	if (AbilitySystemComponent)
	{
		// Clean up the old ability system component.
		UninitializeAbilitySystem();
	}
	APawn* Pawn = GetPawnChecked<APawn>();
	AActor* ExistingAvatar = InASC->GetAvatarActor();

	UE_LOG(LogScWGameCore, Verbose, TEXT("Setting up ASC [%s] on pawn [%s] owner [%s], existing [%s] "), *GetNameSafe(InASC), *GetNameSafe(Pawn), *GetNameSafe(InOwnerActor), *GetNameSafe(ExistingAvatar));

	if ((ExistingAvatar != nullptr) && (ExistingAvatar != Pawn))
	{
		UE_LOG(LogScWGameCore, Log, TEXT("Existing avatar (authority=%d)"), ExistingAvatar->HasAuthority() ? 1 : 0);

		// There is already a pawn acting as the ASC's avatar, so we need to kick it out
		// This can happen on clients if they're lagged: their new pawn is spawned + possessed before the dead one is removed
		ensure(!ExistingAvatar->HasAuthority());

		if (UScWPawnExtensionComponent* OtherExtensionComponent = GetPawnExtensionComponent(ExistingAvatar))
		{
			OtherExtensionComponent->UninitializeAbilitySystem();
		}
	}
	AbilitySystemComponent = InASC;
	AbilitySystemComponent->InitAbilityActorInfo(InOwnerActor, Pawn);

	if (ensure(PawnData))
	{
		PawnData->InitializePawn(this);
	}
	OnAbilitySystemInitialized.Broadcast();
}

void UScWPawnExtensionComponent::UninitializeAbilitySystem()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
	// Uninitialize the ASC if we're still the avatar actor (otherwise another pawn already did it when they became the avatar actor)
	if (AbilitySystemComponent->GetAvatarActor() == GetOwner())
	{
		if (ensure(PawnData))
		{
			PawnData->UninitializePawn(this);
		}
		FGameplayTagContainer AbilityTypesToIgnore;
		AbilityTypesToIgnore.AddTag(FScWCoreTags::Ability_Behavior_IgnoreDeath);

		AbilitySystemComponent->CancelAbilities(nullptr, &AbilityTypesToIgnore);
		AbilitySystemComponent->ClearAbilityInput();
		AbilitySystemComponent->RemoveAllGameplayCues();

		if (AbilitySystemComponent->GetOwnerActor() != nullptr)
		{
			AbilitySystemComponent->SetAvatarActor(nullptr);
		}
		else
		{
			// If the ASC doesn't have a valid owner, we need to clear *all* actor info, not just the avatar pairing
			AbilitySystemComponent->ClearActorInfo();
		}
		OnAbilitySystemUninitialized.Broadcast();
	}
	AbilitySystemComponent = nullptr;
}

void UScWPawnExtensionComponent::HandleControllerChanged()
{
	if (AbilitySystemComponent && (AbilitySystemComponent->GetAvatarActor() == GetPawnChecked<APawn>()))
	{
		ensure(AbilitySystemComponent->AbilityActorInfo->OwnerActor == AbilitySystemComponent->GetOwnerActor());
		if (AbilitySystemComponent->GetOwnerActor() == nullptr)
		{
			UninitializeAbilitySystem();
		}
		else
		{
			AbilitySystemComponent->RefreshAbilityActorInfo();
		}
	}
	CheckDefaultInitialization();
}

void UScWPawnExtensionComponent::HandlePlayerStateReplicated()
{
	CheckDefaultInitialization();
}

void UScWPawnExtensionComponent::SetupPlayerInputComponent()
{
	CheckDefaultInitialization();
}

void UScWPawnExtensionComponent::CheckDefaultInitialization()
{
	// Before checking our progress, try progressing any other features we might depend on
	CheckDefaultInitializationForImplementers();

	static const TArray<FGameplayTag> StateChain = { FScWCoreTags::InitState_Spawned, FScWCoreTags::InitState_DataAvailable, FScWCoreTags::InitState_DataInitialized, FScWCoreTags::InitState_GameplayReady };

	// This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
	ContinueInitStateChain(StateChain);
}

bool UScWPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();
	if (!CurrentState.IsValid() && DesiredState == FScWCoreTags::InitState_Spawned)
	{
		// As long as we are on a valid pawn, we count as spawned
		if (Pawn)
		{
			return true;
		}
	}
	if (CurrentState == FScWCoreTags::InitState_Spawned && DesiredState == FScWCoreTags::InitState_DataAvailable)
	{
		// Pawn data is required.
		if (!PawnData)
		{
			return false;
		}
		const bool bHasAuthority = Pawn->HasAuthority();
		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();

		if (bHasAuthority || bIsLocallyControlled)
		{
			// Check for being possessed by a controller.
			if (!GetController<AController>())
			{
				return false;
			}
		}
		return true;
	}
	else if (CurrentState == FScWCoreTags::InitState_DataAvailable && DesiredState == FScWCoreTags::InitState_DataInitialized)
	{
		// Transition to initialize if all features have their data available
		return Manager->HaveAllFeaturesReachedInitState(Pawn, FScWCoreTags::InitState_DataAvailable);
	}
	else if (CurrentState == FScWCoreTags::InitState_DataInitialized && DesiredState == FScWCoreTags::InitState_GameplayReady)
	{
		return true;
	}
	return false;
}

void UScWPawnExtensionComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	if (DesiredState == FScWCoreTags::InitState_DataInitialized)
	{
		// This is currently all handled by other components listening to this state change
	}
}

void UScWPawnExtensionComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	// If another feature is now in DataAvailable, see if we should transition to DataInitialized
	if (Params.FeatureName != NAME_ActorFeatureName)
	{
		if (Params.FeatureState == FScWCoreTags::InitState_DataAvailable)
		{
			CheckDefaultInitialization();
		}
	}
}

void UScWPawnExtensionComponent::OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate)
{
	if (!OnAbilitySystemInitialized.IsBoundToObject(Delegate.GetUObject()))
	{
		OnAbilitySystemInitialized.Add(Delegate);
	}
	if (AbilitySystemComponent)
	{
		Delegate.Execute();
	}
}

void UScWPawnExtensionComponent::OnAbilitySystemInitialized_UnregisterObject(const UObject* InObject)
{
	OnAbilitySystemInitialized.RemoveAll(InObject);
}

void UScWPawnExtensionComponent::OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate Delegate)
{
	if (!OnAbilitySystemUninitialized.IsBoundToObject(Delegate.GetUObject()))
	{
		OnAbilitySystemUninitialized.Add(Delegate);
	}
}

void UScWPawnExtensionComponent::OnAbilitySystemUninitialized_UnregisterObject(const UObject* InObject)
{
	OnAbilitySystemUninitialized.RemoveAll(InObject);
}
