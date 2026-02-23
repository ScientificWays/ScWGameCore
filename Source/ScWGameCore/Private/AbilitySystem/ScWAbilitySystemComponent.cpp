// Scientific Ways

#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "Tags/ScWCoreTags.h"
#include "AbilitySystem/ScWASC_InitInterface.h"
#include "AbilitySystem/ScWAbilitySystemGlobals.h"
#include "AbilitySystem/ScWAbilityWorldSubsystem.h"
#include "AbilitySystem/ScWAbilityTagRelationshipMapping.h"

#include "System/ScWGameData.h"
#include "System/ScWAssetManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWAbilitySystemComponent)

//~ Begin Statics
UScWAbilitySystemComponent* UScWAbilitySystemComponent::TryGetFromActor(const AActor* InActor, bool bInTryFindComponentIfNoInterface)
{
	return Cast<UScWAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(InActor, bInTryFindComponentIfNoInterface));
}
//~ End Statics

//~ Begin Initialize
UScWAbilitySystemComponent::UScWAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();

	FMemory::Memset(ActivationGroupCounts, 0, sizeof(ActivationGroupCounts));
}

void UScWAbilitySystemComponent::BeginPlay() // UActorComponent
{
	Super::BeginPlay();

	
}
void UScWAbilitySystemComponent::OnRegister() // UActorComponent
{
	Super::OnRegister();

	RegisterGameplayTagEvent(FScWCoreTags::Input_Block_Movement, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnInputBlockMovementTagNumChanged);
}

void UScWAbilitySystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UScWAbilityWorldSubsystem* GlobalAbilitySystem = UWorld::GetSubsystem<UScWAbilityWorldSubsystem>(GetWorld()))
	{
		GlobalAbilitySystem->UnregisterASC(this);
	}
	Super::EndPlay(EndPlayReason);
}

void UScWAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	FGameplayAbilityActorInfo* ActorInfo = AbilityActorInfo.Get();
	check(ActorInfo);
	check(InOwnerActor);

	const bool bHasNewPawnAvatar = Cast<APawn>(InAvatarActor) && (InAvatarActor != ActorInfo->AvatarActor);

	if (GetWorld()->IsGameWorld())
	{
		Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
		IScWASC_InitInterface::HandleInit(this, InOwnerActor, InAvatarActor);
	}
	else
	{
		Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	}
	if (bHasNewPawnAvatar)
	{
		// Notify all abilities that a new pawn avatar has been set
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			PRAGMA_DISABLE_DEPRECATION_WARNINGS
				ensureMsgf(AbilitySpec.Ability && AbilitySpec.Ability->GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced, TEXT("InitAbilityActorInfo: All Abilities should be Instanced (NonInstanced is being deprecated due to usability issues)."));
			PRAGMA_ENABLE_DEPRECATION_WARNINGS

				TArray<UGameplayAbility*> Instances = AbilitySpec.GetAbilityInstances();
			for (UGameplayAbility* AbilityInstance : Instances)
			{
				UScWGameplayAbility* ScWAbilityInstance = Cast<UScWGameplayAbility>(AbilityInstance);
				if (ScWAbilityInstance)
				{
					// Ability instances may be missing for replays
					ScWAbilityInstance->OnPawnAvatarSet();
				}
			}
		}

		// Register with the global system once we actually have a pawn avatar. We wait until this time since some globally-applied effects may require an avatar.
		if (UScWAbilityWorldSubsystem* GlobalAbilitySystem = UWorld::GetSubsystem<UScWAbilityWorldSubsystem>(GetWorld()))
		{
			GlobalAbilitySystem->RegisterASC(this);
		}
		TryActivateAbilitiesOnSpawn();
	}
	OnAbilityActorInfoInitialized.Broadcast();
}
//~ End Initialize

//~ Begin Abilities
void UScWAbilitySystemComponent::TryActivateAbilitiesOnSpawn()
{
	ABILITYLIST_SCOPE_LOCK();
	for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
	{
		if (const UScWGameplayAbility* ScWAbilityCDO = Cast<UScWGameplayAbility>(AbilitySpec.Ability))
		{
			ScWAbilityCDO->TryActivateAbilityOnSpawn(AbilityActorInfo.Get(), AbilitySpec);
		}
	}
}

void UScWAbilitySystemComponent::CancelAbilitiesByFunc(TShouldCancelAbilityFunc ShouldCancelFunc, bool bReplicateCancelAbility)
{
	ABILITYLIST_SCOPE_LOCK();
	for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
	{
		if (!AbilitySpec.IsActive())
		{
			continue;
		}

		UScWGameplayAbility* ScWAbilityCDO = Cast<UScWGameplayAbility>(AbilitySpec.Ability);
		if (!ScWAbilityCDO)
		{
			UE_LOG(LogScWGameCore, Error, TEXT("CancelAbilitiesByFunc: Non-ScWGameplayAbility %s was Granted to ASC. Skipping."), *AbilitySpec.Ability.GetName());
			continue;
		}

		PRAGMA_DISABLE_DEPRECATION_WARNINGS
			ensureMsgf(AbilitySpec.Ability->GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced, TEXT("CancelAbilitiesByFunc: All Abilities should be Instanced (NonInstanced is being deprecated due to usability issues)."));
		PRAGMA_ENABLE_DEPRECATION_WARNINGS

			// Cancel all the spawned instances.
			TArray<UGameplayAbility*> Instances = AbilitySpec.GetAbilityInstances();
		for (UGameplayAbility* AbilityInstance : Instances)
		{
			UScWGameplayAbility* ScWAbilityInstance = CastChecked<UScWGameplayAbility>(AbilityInstance);

			if (ShouldCancelFunc(ScWAbilityInstance, AbilitySpec.Handle))
			{
				if (ScWAbilityInstance->CanBeCanceled())
				{
					ScWAbilityInstance->CancelAbility(AbilitySpec.Handle, AbilityActorInfo.Get(), ScWAbilityInstance->GetCurrentActivationInfo(), bReplicateCancelAbility);
				}
				else
				{
					UE_LOG(LogScWGameCore, Error, TEXT("CancelAbilitiesByFunc: Can't cancel ability [%s] because CanBeCanceled is false."), *ScWAbilityInstance->GetName());
				}
			}
		}
	}
}

void UScWAbilitySystemComponent::CancelInputActivatedAbilities(bool bReplicateCancelAbility)
{
	auto ShouldCancelFunc = [this](const UScWGameplayAbility* ScWAbility, FGameplayAbilitySpecHandle Handle)
	{
		const EScWAbilityActivationPolicy ActivationPolicy = ScWAbility->GetActivationPolicy();
		return ((ActivationPolicy == EScWAbilityActivationPolicy::OnInputTriggered) || (ActivationPolicy == EScWAbilityActivationPolicy::WhileInputActive));
	};

	CancelAbilitiesByFunc(ShouldCancelFunc, bReplicateCancelAbility);
}

void UScWAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);

	// We don't support UGameplayAbility::bReplicateInputDirectly.
	// Use replicated events instead so that the WaitInputPress ability task works.
	if (Spec.IsActive())
	{
		PRAGMA_DISABLE_DEPRECATION_WARNINGS
			const UGameplayAbility* Instance = Spec.GetPrimaryInstance();
		FPredictionKey OriginalPredictionKey = Instance ? Instance->GetCurrentActivationInfo().GetActivationPredictionKey() : Spec.ActivationInfo.GetActivationPredictionKey();
		PRAGMA_ENABLE_DEPRECATION_WARNINGS

			// Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, OriginalPredictionKey);
	}
}

void UScWAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);

	// We don't support UGameplayAbility::bReplicateInputDirectly.
	// Use replicated events instead so that the WaitInputRelease ability task works.
	if (Spec.IsActive())
	{
		PRAGMA_DISABLE_DEPRECATION_WARNINGS
			const UGameplayAbility* Instance = Spec.GetPrimaryInstance();
		FPredictionKey OriginalPredictionKey = Instance ? Instance->GetCurrentActivationInfo().GetActivationPredictionKey() : Spec.ActivationInfo.GetActivationPredictionKey();
		PRAGMA_ENABLE_DEPRECATION_WARNINGS

			// Invoke the InputReleased event. This is not replicated here. If someone is listening, they may replicate the InputReleased event to the server.
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, OriginalPredictionKey);
	}
}

void UScWAbilitySystemComponent::AbilityTagPressed(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag)))
			{
				InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UScWAbilitySystemComponent::AbilityTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag)))
			{
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}

void UScWAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	if (HasMatchingGameplayTag(FScWCoreTags::Input_Block_Ability))
	{
		ClearAbilityInput();
		return;
	}
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	//@TODO: See if we can use FScopedServerAbilityRPCBatcher ScopedRPCBatcher in some of these loops

	//
	// Process all abilities that activate when the input is held.
	//
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability && !AbilitySpec->IsActive())
			{
				const UScWGameplayAbility* ScWAbilityCDO = Cast<UScWGameplayAbility>(AbilitySpec->Ability);
				if (ScWAbilityCDO && ScWAbilityCDO->GetActivationPolicy() == EScWAbilityActivationPolicy::WhileInputActive)
				{
					AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
				}
			}
		}
	}

	//
	// Process all abilities that had their input pressed this frame.
	//
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;

				if (AbilitySpec->IsActive())
				{
					// Ability is active so pass along the input event.
					AbilitySpecInputPressed(*AbilitySpec);
				}
				else
				{
					const UScWGameplayAbility* ScWAbilityCDO = Cast<UScWGameplayAbility>(AbilitySpec->Ability);

					if (ScWAbilityCDO && ScWAbilityCDO->GetActivationPolicy() == EScWAbilityActivationPolicy::OnInputTriggered)
					{
						AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
					}
				}
			}
		}
	}

	//
	// Try to activate all the abilities that are from presses and holds.
	// We do it all at once so that held inputs don't activate the ability
	// and then also send a input event to the ability because of the press.
	//
	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		TryActivateAbility(AbilitySpecHandle);
	}

	//
	// Process all abilities that had their input released this frame.
	//
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;

				if (AbilitySpec->IsActive())
				{
					// Ability is active so pass along the input event.
					AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}

	//
	// Clear the cached ability handles.
	//
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UScWAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void UScWAbilitySystemComponent::NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability)
{
	Super::NotifyAbilityActivated(Handle, Ability);

	if (UScWGameplayAbility* ScWAbility = Cast<UScWGameplayAbility>(Ability))
	{
		AddAbilityToActivationGroup(ScWAbility->GetActivationGroup(), ScWAbility);
	}
}

void UScWAbilitySystemComponent::NotifyAbilityFailed(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason)
{
	Super::NotifyAbilityFailed(Handle, Ability, FailureReason);

	if (APawn* Avatar = Cast<APawn>(GetAvatarActor()))
	{
		if (!Avatar->IsLocallyControlled() && Ability->IsSupportedForNetworking())
		{
			ClientNotifyAbilityFailed(Ability, FailureReason);
			return;
		}
	}
	HandleAbilityFailed(Ability, FailureReason);
}

void UScWAbilitySystemComponent::NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, bool bWasCancelled)
{
	Super::NotifyAbilityEnded(Handle, Ability, bWasCancelled);

	if (UScWGameplayAbility* ScWAbility = Cast<UScWGameplayAbility>(Ability))
	{
		RemoveAbilityFromActivationGroup(ScWAbility->GetActivationGroup(), ScWAbility);
	}
}

void UScWAbilitySystemComponent::ApplyAbilityBlockAndCancelTags(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bEnableBlockTags, const FGameplayTagContainer& BlockTags, bool bExecuteCancelTags, const FGameplayTagContainer& CancelTags)
{
	FGameplayTagContainer ModifiedBlockTags = BlockTags;
	FGameplayTagContainer ModifiedCancelTags = CancelTags;

	if (TagRelationshipMapping)
	{
		// Use the mapping to expand the ability tags into block and cancel tag
		TagRelationshipMapping->GetAbilityTagsToBlockAndCancel(AbilityTags, &ModifiedBlockTags, &ModifiedCancelTags);
	}
	Super::ApplyAbilityBlockAndCancelTags(AbilityTags, RequestingAbility, bEnableBlockTags, ModifiedBlockTags, bExecuteCancelTags, ModifiedCancelTags);

	//@TODO: Apply any special logic like blocking input or movement
}

void UScWAbilitySystemComponent::HandleChangeAbilityCanBeCanceled(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bCanBeCanceled)
{
	Super::HandleChangeAbilityCanBeCanceled(AbilityTags, RequestingAbility, bCanBeCanceled);

	//@TODO: Apply any special logic like blocking input or movement
}

void UScWAbilitySystemComponent::GetAdditionalActivationTagRequirements(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer& OutActivationRequired, FGameplayTagContainer& OutActivationBlocked) const
{
	if (TagRelationshipMapping)
	{
		TagRelationshipMapping->GetRequiredAndBlockedActivationTags(AbilityTags, &OutActivationRequired, &OutActivationBlocked);
	}
}

void UScWAbilitySystemComponent::SetTagRelationshipMapping(UScWAbilityTagRelationshipMapping* NewMapping)
{
	TagRelationshipMapping = NewMapping;
}

void UScWAbilitySystemComponent::ClientNotifyAbilityFailed_Implementation(const UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason)
{
	HandleAbilityFailed(Ability, FailureReason);
}

void UScWAbilitySystemComponent::HandleAbilityFailed(const UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason)
{
	//UE_LOG(LogScWGameCore, Warning, TEXT("Ability %s failed to activate (tags: %s)"), *GetPathNameSafe(Ability), *FailureReason.ToString());

	if (const UScWGameplayAbility* ScWAbility = Cast<const UScWGameplayAbility>(Ability))
	{
		ScWAbility->OnAbilityFailedToActivate(FailureReason);
	}
}

bool UScWAbilitySystemComponent::IsActivationGroupBlocked(EScWAbilityActivationGroup Group) const
{
	bool bBlocked = false;

	switch (Group)
	{
		case EScWAbilityActivationGroup::Independent:
			// Independent abilities are never blocked.
			bBlocked = false;
			break;

		case EScWAbilityActivationGroup::Exclusive_Replaceable:
		case EScWAbilityActivationGroup::Exclusive_Blocking:
			// Exclusive abilities can activate if nothing is blocking.
			bBlocked = (ActivationGroupCounts[(uint8)EScWAbilityActivationGroup::Exclusive_Blocking] > 0);
			break;

		default:
			checkf(false, TEXT("IsActivationGroupBlocked: Invalid ActivationGroup [%d]\n"), (uint8)Group);
			break;
	}

	return bBlocked;
}

void UScWAbilitySystemComponent::AddAbilityToActivationGroup(EScWAbilityActivationGroup Group, UScWGameplayAbility* ScWAbility)
{
	check(ScWAbility);
	check(ActivationGroupCounts[(uint8)Group] < INT32_MAX);

	ActivationGroupCounts[(uint8)Group]++;

	const bool bReplicateCancelAbility = false;

	switch (Group)
	{
		case EScWAbilityActivationGroup::Independent:
			// Independent abilities do not cancel any other abilities.
			break;

		case EScWAbilityActivationGroup::Exclusive_Replaceable:
		case EScWAbilityActivationGroup::Exclusive_Blocking:
			CancelActivationGroupAbilities(EScWAbilityActivationGroup::Exclusive_Replaceable, ScWAbility, bReplicateCancelAbility);
			break;

		default:
			checkf(false, TEXT("AddAbilityToActivationGroup: Invalid ActivationGroup [%d]\n"), (uint8)Group);
			break;
	}

	const int32 ExclusiveCount = ActivationGroupCounts[(uint8)EScWAbilityActivationGroup::Exclusive_Replaceable] + ActivationGroupCounts[(uint8)EScWAbilityActivationGroup::Exclusive_Blocking];
	if (!ensure(ExclusiveCount <= 1))
	{
		UE_LOG(LogScWGameCore, Error, TEXT("AddAbilityToActivationGroup: Multiple exclusive abilities are running."));
	}
}

void UScWAbilitySystemComponent::RemoveAbilityFromActivationGroup(EScWAbilityActivationGroup Group, UScWGameplayAbility* ScWAbility)
{
	check(ScWAbility);
	check(ActivationGroupCounts[(uint8)Group] > 0);

	ActivationGroupCounts[(uint8)Group]--;
}

void UScWAbilitySystemComponent::CancelActivationGroupAbilities(EScWAbilityActivationGroup Group, UScWGameplayAbility* IgnoreScWAbility, bool bReplicateCancelAbility)
{
	auto ShouldCancelFunc = [this, Group, IgnoreScWAbility](const UScWGameplayAbility* ScWAbility, FGameplayAbilitySpecHandle Handle)
	{
		return ((ScWAbility->GetActivationGroup() == Group) && (ScWAbility != IgnoreScWAbility));
	};

	CancelAbilitiesByFunc(ShouldCancelFunc, bReplicateCancelAbility);
}

void UScWAbilitySystemComponent::GetAbilityTargetData(const FGameplayAbilitySpecHandle AbilityHandle, FGameplayAbilityActivationInfo ActivationInfo, FGameplayAbilityTargetDataHandle& OutTargetDataHandle)
{
	TSharedPtr<FAbilityReplicatedDataCache> ReplicatedData = AbilityTargetDataMap.Find(FGameplayAbilitySpecHandleAndPredictionKey(AbilityHandle, ActivationInfo.GetActivationPredictionKey()));
	if (ReplicatedData.IsValid())
	{
		OutTargetDataHandle = ReplicatedData->TargetData;
	}
}

void UScWAbilitySystemComponent::ClearAbilities(TArray<FGameplayAbilitySpecHandle>& InHandleArray, const bool bInResetArray)
{
	for (auto SampleHandle : InHandleArray)
	{
		ClearAbility(SampleHandle);
	}
	if (bInResetArray)
	{
		InHandleArray.Empty();
	}
}

template<class T>
void UScWAbilitySystemComponent::AppendAbilityInstancesOrCDO(const FGameplayAbilitySpec& InSpec, TArray<T*>& OutArray) const
{
	TArray<UGameplayAbility*> SampleInstanceArray = InSpec.GetAbilityInstances();

	if (SampleInstanceArray.Num())
	{
		for (UGameplayAbility* SampleInstance : SampleInstanceArray)
		{
			if (T* SampleAbility = Cast<T>(SampleInstance))
			{
				OutArray.Add(SampleAbility);
			}
		}
	}
	else
	{
		if (T* SampleAbilityCDO = Cast<T>(InSpec.Ability))
		{
			OutArray.Add(SampleAbilityCDO);
		}
	}
}
//~ End Abilities

//~ Begin Effects
void UScWAbilitySystemComponent::AddDynamicTagGameplayEffect(const FGameplayTag& Tag)
{
	const TSubclassOf<UGameplayEffect> DynamicTagGE = UScWAssetManager::GetSubclass(UScWGameData::Get().DynamicTagGameplayEffect);
	if (!DynamicTagGE)
	{
		UE_LOG(LogScWGameCore, Warning, TEXT("AddDynamicTagGameplayEffect: Unable to find DynamicTagGameplayEffect [%s]."), *UScWGameData::Get().DynamicTagGameplayEffect.GetAssetName());
		return;
	}
	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(DynamicTagGE, 1.0f, MakeEffectContext());
	FGameplayEffectSpec* Spec = SpecHandle.Data.Get();

	if (!Spec)
	{
		UE_LOG(LogScWGameCore, Warning, TEXT("AddDynamicTagGameplayEffect: Unable to make outgoing spec for [%s]."), *GetNameSafe(DynamicTagGE));
		return;
	}
	Spec->DynamicGrantedTags.AddTag(Tag);
	ApplyGameplayEffectSpecToSelf(*Spec);
}

void UScWAbilitySystemComponent::RemoveDynamicTagGameplayEffect(const FGameplayTag& Tag)
{
	const TSubclassOf<UGameplayEffect> DynamicTagGE = UScWAssetManager::GetSubclass(UScWGameData::Get().DynamicTagGameplayEffect);
	if (!DynamicTagGE)
	{
		UE_LOG(LogScWGameCore, Warning, TEXT("RemoveDynamicTagGameplayEffect: Unable to find gameplay effect [%s]."), *UScWGameData::Get().DynamicTagGameplayEffect.GetAssetName());
		return;
	}
	FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FGameplayTagContainer(Tag));
	Query.EffectDefinition = DynamicTagGE;

	RemoveActiveEffects(Query);
}
//~ End Effects

//~ Begin Tags
void UScWAbilitySystemComponent::OnInputBlockMovementTagNumChanged(const FGameplayTag InCallbackTag, int32 InNewNum)
{
	if (AController* OwnerController = UScWAbilitySystemGlobals::GetControllerFromASC(this))
	{
		if (InNewNum > 0) // HasMatchingGameplayTag(FScWCoreTags::Input_Block_Movement)
		{
			OwnerController->SetIgnoreMoveInput(true); // Should be enough to use native stacked state storage feature
		}
		else
		{
			OwnerController->SetIgnoreMoveInput(false); // As long as EGameplayTagEventType::NewOrRemoved is used
		}
	}
	else
	{
		//ensure(false);
	}
}
//~ End Tags
