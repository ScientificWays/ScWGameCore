// Scientific Ways

#include "AbilitySystem/ScWGameplayAbility.h"

#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "AbilitySystemLog.h"

#include "AbilitySystem/ScWAbilityCost.h"
#include "Tags/ScWCoreTags.h"

#include "AbilitySystem/ScWAbilitySystemGlobals.h"
#include "AbilitySystem/ScWGameplayEffectContext.h"
//#include "AbilitySystem/ScWAbilitySourceInterface.h"

#include "GameFramework/GameplayMessageSubsystem.h"

#include "Utils/ScWUtils.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGameplayAbility)

#define ENSURE_ABILITY_IS_INSTANTIATED_OR_RETURN(FunctionName, ReturnValue)																				\
{																																						\
	if (!ensure(IsInstantiated()))																														\
	{																																					\
		ABILITY_LOG(Error, TEXT("%s: " #FunctionName " cannot be called on a non-instanced ability. Check the instancing policy."), *GetPathName());	\
		return ReturnValue;																																\
	}																																					\
}

UE_DEFINE_GAMEPLAY_TAG(TAG_ABILITY_SIMPLE_FAILURE_MESSAGE, "Ability.UserFacingSimpleActivateFail.Message");
UE_DEFINE_GAMEPLAY_TAG(TAG_ABILITY_PLAY_MONTAGE_FAILURE_MESSAGE, "Ability.PlayMontageOnActivateFail.Message");

UScWGameplayAbility::UScWGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;

	ActivationPolicy = EScWAbilityActivationPolicy::OnInputTriggered;
	ActivationGroup = EScWAbilityActivationGroup::Independent;

	bLogCancelation = false;

	//ActiveCameraMode = nullptr;
}

UScWAbilitySystemComponent* UScWGameplayAbility::GetScWAbilitySystemComponentFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<UScWAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo()) : nullptr);
}

APlayerController* UScWGameplayAbility::GetPlayerControllerFromActorInfo() const
{
	return UScWAbilitySystemGlobals::GetPlayerControllerFromASC(GetAbilitySystemComponentFromActorInfo());
}

AController* UScWGameplayAbility::GetControllerFromActorInfo() const
{
	return UScWAbilitySystemGlobals::GetControllerFromASC(GetAbilitySystemComponentFromActorInfo());
}

ACharacter* UScWGameplayAbility::GetCharacterFromActorInfo() const
{
	return UScWAbilitySystemGlobals::GetCharacterFromASC(GetAbilitySystemComponentFromActorInfo());
}

void UScWGameplayAbility::NativeOnAbilityFailedToActivate(const FGameplayTagContainer& FailedReason) const
{
	bool bSimpleFailureFound = false;

	for (FGameplayTag Reason : FailedReason)
	{
		if (!bSimpleFailureFound)
		{
			if (const FText* pUserFacingMessage = FailureTagToUserFacingMessages.Find(Reason))
			{
				FGameplayMessage_AbilityFailureSimple Message;
				Message.PlayerController = GetActorInfo().PlayerController.Get();
				Message.FailureTags = FailedReason;
				Message.UserFacingReason = *pUserFacingMessage;

				UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(this);
				MessageSystem.BroadcastMessage(TAG_ABILITY_SIMPLE_FAILURE_MESSAGE, Message);
				bSimpleFailureFound = true;
			}
		}
		if (UAnimMontage* pMontage = FailureTagToAnimMontage.FindRef(Reason))
		{
			FGameplayMessage_AbilityFailureMontage Message;
			Message.PlayerController = GetActorInfo().PlayerController.Get();
			Message.AvatarActor = GetActorInfo().AvatarActor.Get();
			Message.FailureTags = FailedReason;
			Message.FailureMontage = pMontage;

			UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(this);
			MessageSystem.BroadcastMessage(TAG_ABILITY_PLAY_MONTAGE_FAILURE_MESSAGE, Message);
		}
	}
	SendAbilityEvent(FScWCoreTags::Ability_Event_Failed);
}

bool UScWGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle InHandle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		return false;
	}
	if (!Super::CanActivateAbility(InHandle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	//@TODO Possibly remove after setting up tag relationships
	UScWAbilitySystemComponent* OwnerASC = CastChecked<UScWAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
	if (OwnerASC->IsActivationGroupBlocked(ActivationGroup))
	{
		if (OptionalRelevantTags)
		{
			OptionalRelevantTags->AddTag(FScWCoreTags::Ability_ActivateFail_ActivationGroup);
		}
		return false;
	}
	return true;
}

void UScWGameplayAbility::SetCanBeCanceled(bool bCanBeCanceled)
{
	// The ability can not block canceling if it's replaceable.
	if (!bCanBeCanceled && (ActivationGroup == EScWAbilityActivationGroup::Exclusive_Replaceable))
	{
		UE_LOG(LogScWGameCore, Error, TEXT("SetCanBeCanceled: Ability [%s] can not block canceling because its activation group is replaceable."), *GetName());
		return;
	}
	Super::SetCanBeCanceled(bCanBeCanceled);
}

void UScWGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	SendAbilityEvent(FScWCoreTags::Ability_Event_Added);
	BP_OnAbilityAdded();

	TryActivateAbilityOnSpawn(ActorInfo, Spec);
}

void UScWGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	SendAbilityEvent(FScWCoreTags::Ability_Event_Removed);
	BP_OnAbilityRemoved();
}

void UScWGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle InHandle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(InHandle, ActorInfo, ActivationInfo, TriggerEventData);

	SendAbilityEvent(FScWCoreTags::Ability_Event_Activated);
}

bool UScWGameplayAbility::CommitAbility(const FGameplayAbilitySpecHandle InHandle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags)
{
	if (Super::CommitAbility(InHandle, ActorInfo, ActivationInfo, OptionalRelevantTags))
	{
		SendAbilityEvent(FScWCoreTags::Ability_Event_Commited);
		return true;
	}
	return false;
}

void UScWGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle InHandle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	//ClearCameraMode();

	Super::EndAbility(InHandle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (bWasCancelled)
	{
		SendAbilityEvent(FScWCoreTags::Ability_Event_Ended_Cancelled);
	}
	else
	{
		SendAbilityEvent(FScWCoreTags::Ability_Event_Ended);
	}
}

bool UScWGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle InHandle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CheckCost(InHandle, ActorInfo, OptionalRelevantTags) || !ActorInfo)
	{
		return false;
	}
	// Verify we can afford any additional costs
	for (const TObjectPtr<UScWAbilityCost>& AdditionalCost : AdditionalCosts)
	{
		if (AdditionalCost != nullptr)
		{
			if (!AdditionalCost->CheckCost(this, InHandle, ActorInfo, /*inout*/ OptionalRelevantTags))
			{
				return false;
			}
		}
	}
	return true;
}

void UScWGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle InHandle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(InHandle, ActorInfo, ActivationInfo);

	check(ActorInfo);

	// Used to determine if the ability actually hit a target (as some costs are only spent on successful attempts)
	auto DetermineIfAbilityHitTarget = [&]()
	{
		if (ActorInfo->IsNetAuthority())
		{
			if (UScWAbilitySystemComponent* ASC = Cast<UScWAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get()))
			{
				FGameplayAbilityTargetDataHandle TargetData;
				ASC->GetAbilityTargetData(InHandle, ActivationInfo, TargetData);
				for (int32 TargetDataIdx = 0; TargetDataIdx < TargetData.Data.Num(); ++TargetDataIdx)
				{
					if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetData, TargetDataIdx))
					{
						return true;
					}
				}
			}
		}
		return false;
	};
	// Pay any additional costs
	bool bAbilityHitTarget = false;
	bool bHasDeterminedIfAbilityHitTarget = false;
	for (const TObjectPtr<UScWAbilityCost>& AdditionalCost : AdditionalCosts)
	{
		if (AdditionalCost != nullptr)
		{
			if (AdditionalCost->ShouldOnlyApplyCostOnHit())
			{
				if (!bHasDeterminedIfAbilityHitTarget)
				{
					bAbilityHitTarget = DetermineIfAbilityHitTarget();
					bHasDeterminedIfAbilityHitTarget = true;
				}

				if (!bAbilityHitTarget)
				{
					continue;
				}
			}
			AdditionalCost->ApplyCost(this, InHandle, ActorInfo, ActivationInfo);
		}
	}
}

FGameplayEffectContextHandle UScWGameplayAbility::MakeEffectContext(const FGameplayAbilitySpecHandle InHandle, const FGameplayAbilityActorInfo* ActorInfo) const
{
	FGameplayEffectContextHandle ContextHandle = Super::MakeEffectContext(InHandle, ActorInfo);

	FScWGameplayEffectContext* EffectContext = FScWGameplayEffectContext::ExtractEffectContext(ContextHandle);
	check(EffectContext);

	check(ActorInfo);

	AActor* EffectCauser = nullptr;
	//const IScWAbilitySourceInterface* AbilitySource = nullptr;
	//float SourceLevel = 0.0f;
	//GetAbilitySource(InHandle, ActorInfo, OUT SourceLevel, OUT AbilitySource, OUT EffectCauser);

	UObject* SourceObject = GetSourceObject(InHandle, ActorInfo);

	AActor* Instigator = ActorInfo ? ActorInfo->OwnerActor.Get() : nullptr;

	//EffectContext->SetAbilitySource(AbilitySource, SourceLevel);
	EffectContext->AddInstigator(Instigator, EffectCauser);
	EffectContext->AddSourceObject(SourceObject);

	return ContextHandle;
}

void UScWGameplayAbility::ApplyAbilityTagsToGameplayEffectSpec(FGameplayEffectSpec& Spec, FGameplayAbilitySpec* AbilitySpec) const
{
	Super::ApplyAbilityTagsToGameplayEffectSpec(Spec, AbilitySpec);

	if (const FHitResult* HitResult = Spec.GetContext().GetHitResult())
	{
		/*if (const UPhysicalMaterialWithTags* PhysMatWithTags = Cast<const UPhysicalMaterialWithTags>(HitResult->PhysMaterial.Get()))
		{
			Spec.CapturedTargetTags.GetSpecTags().AppendTags(PhysMatWithTags->Tags);
		}*/
	}
}

bool UScWGameplayAbility::DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	// Specialized version to handle death exclusion and AbilityTags expansion via ASC

	bool bBlocked = false;
	bool bMissing = false;

	UAbilitySystemGlobals& AbilitySystemGlobals = UAbilitySystemGlobals::Get();
	const FGameplayTag& BlockedTag = AbilitySystemGlobals.ActivateFailTagsBlockedTag;
	const FGameplayTag& MissingTag = AbilitySystemGlobals.ActivateFailTagsMissingTag;

	// Check if any of this ability's tags are currently blocked
	if (AbilitySystemComponent.AreAbilityTagsBlocked(GetAssetTags()))
	{
		bBlocked = true;
	}
	const UScWAbilitySystemComponent* OwnerASC = Cast<UScWAbilitySystemComponent>(&AbilitySystemComponent);
	static FGameplayTagContainer AllRequiredTags;
	static FGameplayTagContainer AllBlockedTags;

	AllRequiredTags = ActivationRequiredTags;
	AllBlockedTags = ActivationBlockedTags;

	// Expand our ability tags to add additional required/blocked tags
	if (OwnerASC)
	{
		OwnerASC->GetAdditionalActivationTagRequirements(GetAssetTags(), AllRequiredTags, AllBlockedTags);
	}
	// Check to see the required/blocked tags for this ability
	if (AllBlockedTags.Num() || AllRequiredTags.Num())
	{
		static FGameplayTagContainer AbilitySystemComponentTags;

		AbilitySystemComponentTags.Reset();
		AbilitySystemComponent.GetOwnedGameplayTags(AbilitySystemComponentTags);

		if (AbilitySystemComponentTags.HasAny(AllBlockedTags))
		{
			if (OptionalRelevantTags && AbilitySystemComponentTags.HasTag(FScWCoreTags::Character_State_Dead))
			{
				// If player is dead and was rejected due to blocking tags, give that feedback
				OptionalRelevantTags->AddTag(FScWCoreTags::Ability_ActivateFail_OwnerDead);
			}
			bBlocked = true;
		}
		if (!AbilitySystemComponentTags.HasAll(AllRequiredTags))
		{
			bMissing = true;
		}
	}
	if (SourceTags != nullptr)
	{
		if (SourceBlockedTags.Num() || SourceRequiredTags.Num())
		{
			if (SourceTags->HasAny(SourceBlockedTags))
			{
				bBlocked = true;
			}

			if (!SourceTags->HasAll(SourceRequiredTags))
			{
				bMissing = true;
			}
		}
	}
	if (TargetTags != nullptr)
	{
		if (TargetBlockedTags.Num() || TargetRequiredTags.Num())
		{
			if (TargetTags->HasAny(TargetBlockedTags))
			{
				bBlocked = true;
			}

			if (!TargetTags->HasAll(TargetRequiredTags))
			{
				bMissing = true;
			}
		}
	}
	if (bBlocked)
	{
		if (OptionalRelevantTags && BlockedTag.IsValid())
		{
			OptionalRelevantTags->AddTag(BlockedTag);
		}
		return false;
	}
	if (bMissing)
	{
		if (OptionalRelevantTags && MissingTag.IsValid())
		{
			OptionalRelevantTags->AddTag(MissingTag);
		}
		return false;
	}
	return true;
}

void UScWGameplayAbility::OnPawnAvatarSet()
{
	BP_OnPawnAvatarSet();
}

/*void UScWGameplayAbility::GetAbilitySource(FGameplayAbilitySpecHandle InHandle, const FGameplayAbilityActorInfo* ActorInfo, float& OutSourceLevel, const IScWAbilitySourceInterface*& OutAbilitySource, AActor*& OutEffectCauser) const
{
	OutSourceLevel = 0.0f;
	OutAbilitySource = nullptr;
	OutEffectCauser = nullptr;

	OutEffectCauser = ActorInfo->AvatarActor.Get();

	// If we were added by something that's an ability info source, use it
	UObject* SourceObject = GetSourceObject(InHandle, ActorInfo);

	OutAbilitySource = Cast<IScWAbilitySourceInterface>(SourceObject);
}*/

void UScWGameplayAbility::TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const
{
	// Try to activate if activation policy is on spawn.
	if (ActorInfo && !Spec.IsActive() && (ActivationPolicy == EScWAbilityActivationPolicy::OnSpawn))
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		const AActor* AvatarActor = ActorInfo->AvatarActor.Get();

		// If avatar actor is torn off or about to die, don't try to activate until we get the new one.
		if (ASC && AvatarActor && !AvatarActor->GetTearOff() && (AvatarActor->GetLifeSpan() <= 0.0f))
		{
			const bool bIsLocalExecution = (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::LocalPredicted) || (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::LocalOnly);
			const bool bIsServerExecution = (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::ServerOnly) || (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::ServerInitiated);

			const bool bClientShouldActivate = ActorInfo->IsLocallyControlled() && bIsLocalExecution;
			const bool bServerShouldActivate = ActorInfo->IsNetAuthority() && bIsServerExecution;

			if (bClientShouldActivate || bServerShouldActivate)
			{
				ASC->TryActivateAbility(Spec.Handle);
			}
		}
	}
}

bool UScWGameplayAbility::CanChangeActivationGroup(EScWAbilityActivationGroup NewGroup) const
{
	if (!IsInstantiated() || !IsActive())
	{
		return false;
	}
	if (ActivationGroup == NewGroup)
	{
		return true;
	}
	UScWAbilitySystemComponent* OwnerASC = GetScWAbilitySystemComponentFromActorInfo();
	check(OwnerASC);

	if ((ActivationGroup != EScWAbilityActivationGroup::Exclusive_Blocking) && OwnerASC->IsActivationGroupBlocked(NewGroup))
	{
		// This ability can't change groups if it's blocked (unless it is the one doing the blocking).
		return false;
	}
	if ((NewGroup == EScWAbilityActivationGroup::Exclusive_Replaceable) && !CanBeCanceled())
	{
		// This ability can't become replaceable if it can't be canceled.
		return false;
	}
	return true;
}

bool UScWGameplayAbility::ChangeActivationGroup(EScWAbilityActivationGroup NewGroup)
{
	ENSURE_ABILITY_IS_INSTANTIATED_OR_RETURN(ChangeActivationGroup, false);

	if (!CanChangeActivationGroup(NewGroup))
	{
		return false;
	}
	if (ActivationGroup != NewGroup)
	{
		UScWAbilitySystemComponent* OwnerASC = GetScWAbilitySystemComponentFromActorInfo();
		check(OwnerASC);

		OwnerASC->RemoveAbilityFromActivationGroup(ActivationGroup, this);
		OwnerASC->AddAbilityToActivationGroup(NewGroup, this);

		ActivationGroup = NewGroup;
	}
	return true;
}

bool UScWGameplayAbility::IsAbilityInputPressed() const
{
	FGameplayAbilitySpec* AbilitySpec = GetCurrentAbilitySpec();
	ensureReturn(AbilitySpec, false);
	return AbilitySpec->InputPressed;
}

//~ Begin Events
void UScWGameplayAbility::SendAbilityEvent(const FGameplayTag& InEventTag) const
{
	ensureReturn(CurrentActorInfo);
	UScWAbilitySystemComponent* OwnerASC = CastChecked<UScWAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent.Get());

	FGameplayEventData EventData = BP_MakeAbilityEventData(InEventTag);

	ensureReturn(OwnerASC);
	OwnerASC->HandleGameplayEvent(InEventTag, &EventData);
}

FGameplayEventData UScWGameplayAbility::BP_MakeAbilityEventData_Implementation(const FGameplayTag& InEventTag) const
{
	FGameplayEventData OutData;
	OutData.EventTag = InEventTag;

	ensureReturn(CurrentActorInfo, OutData);

	OutData.Instigator = CurrentActorInfo->OwnerActor.Get();
	OutData.Target = CurrentActorInfo->AvatarActor.Get();
	OutData.TargetTags = GetAssetTags();
	OutData.OptionalObject = this;
	OutData.ContextHandle = MakeEffectContext(CurrentSpecHandle, CurrentActorInfo);
	return OutData;
}
//~ End Events
