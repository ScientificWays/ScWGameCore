// Scientific Ways

#include "AbilitySystem/ScWAbilitySystemGlobals.h"

#include "Tags/ScWCoreTags.h"
#include "AbilitySystem/ScWGameplayEffectContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWAbilitySystemGlobals)

struct FGameplayEffectContext;

UScWAbilitySystemGlobals::UScWAbilitySystemGlobals(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

//~ Begin Tags
FDelegateHandle_BlueprintWrapper UScWAbilitySystemGlobals::RegisterGameplayTagEvent(UAbilitySystemComponent* InASC, FGameplayTagNumChangedEvent InEvent, FGameplayTag InTag, EGameplayTagEventType::Type InType)
{
	return { InASC->RegisterGameplayTagEvent(InTag, InType).AddUFunction(InEvent.GetUObject(), InEvent.GetFunctionName()) };
}

void UScWAbilitySystemGlobals::UnRegisterGameplayTagEvent(UAbilitySystemComponent* InASC, FDelegateHandle_BlueprintWrapper InHandle, FGameplayTag InTag, EGameplayTagEventType::Type InType)
{
	InASC->UnregisterGameplayTagEvent(InHandle.Handle, InTag, InType);
}

void UScWAbilitySystemGlobals::GetOwnedGameplayTags(UObject* InTarget, FGameplayTagContainer& OutTagContainer)
{
	if (IGameplayTagAssetInterface* TargetInterface = Cast<IGameplayTagAssetInterface>(InTarget))
	{
		TargetInterface->GetOwnedGameplayTags(OutTagContainer);
	}
	else
	{
		//ensure(false);
		OutTagContainer.Reset();
	}
}

bool UScWAbilitySystemGlobals::TargetHasMatchingGameplayTag(UObject* InTarget, const FGameplayTag& InTag)
{
	if (IGameplayTagAssetInterface* TargetInterface = Cast<IGameplayTagAssetInterface>(InTarget))
	{
		return TargetInterface->HasMatchingGameplayTag(InTag);
	}
	//ensure(false);
	return false;
}

bool UScWAbilitySystemGlobals::TargetHasAllMatchingGameplayTags(UObject* InTarget, const FGameplayTagContainer& InTagContainer)
{
	if (IGameplayTagAssetInterface* TargetInterface = Cast<IGameplayTagAssetInterface>(InTarget))
	{
		return TargetInterface->HasAllMatchingGameplayTags(InTagContainer);
	}
	//ensure(false);
	return false;
}

bool UScWAbilitySystemGlobals::TargetHasAnyMatchingGameplayTags(UObject* InTarget, const FGameplayTagContainer& InTagContainer)
{
	if (IGameplayTagAssetInterface* TargetInterface = Cast<IGameplayTagAssetInterface>(InTarget))
	{
		return TargetInterface->HasAnyMatchingGameplayTags(InTagContainer);
	}
	//ensure(false);
	return false;
}

bool UScWAbilitySystemGlobals::IsPlayerPawnType(UObject* InTarget)
{
	ensureReturn(InTarget, false);
	return TargetHasMatchingGameplayTag(InTarget, FScWCoreTags::Character_Type_Player);
}

void UScWAbilitySystemGlobals::InitGlobalTags() // UAbilitySystemGlobals
{
	Super::InitGlobalTags();

	UWorld* World = GetWorld();
	if (World && World->IsGameWorld())
	{
		//ensure(ActivateFailIsDeadTag.IsValid());
		ensure(ActivateFailCooldownTag.IsValid());
		ensure(ActivateFailCostTag.IsValid());
		ensure(ActivateFailTagsBlockedTag.IsValid());
		ensure(ActivateFailTagsMissingTag.IsValid());
		ensure(ActivateFailNetworkingTag.IsValid());
	}
	IgnoreDamageTags = FGameplayTagContainer(FScWCoreTags::Character_State_IgnoreAnyDamage);
	IgnoreDamageTags.AddTag(FScWCoreTags::Cheat_Invulnerable);
}
//~ End Tags

//~ Begin Effects
FGameplayEffectContext* UScWAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FScWGameplayEffectContext();
}

FActiveGameplayEffectHandle UScWAbilitySystemGlobals::TryApplyGameplayEffectByClass(UAbilitySystemComponent* InTarget, TSubclassOf<UGameplayEffect> InClass, float InDuration, float InMagnitude, float InLevel)
{
	ensureReturn(InTarget, FActiveGameplayEffectHandle());
	ensureReturn(InClass, FActiveGameplayEffectHandle());

	FGameplayEffectSpecHandle EffectSpecHandle = InTarget->MakeOutgoingSpec(InClass, InLevel, InTarget->MakeEffectContext());

	if (InDuration > 0.0f)
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(FScWCoreTags::SetByCaller_Duration, InDuration);
	}
	EffectSpecHandle.Data->SetSetByCallerMagnitude(FScWCoreTags::SetByCaller_Magnitude, InMagnitude);
	return InTarget->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
}

int32 UScWAbilitySystemGlobals::TryRemoveGameplayEffectByClass(UAbilitySystemComponent* InTarget, TSubclassOf<UGameplayEffect> InClass, int32 InStacksToRemove)
{
	ensureReturn(InTarget, 0);
	ensureReturn(InClass, 0);

	FGameplayEffectQuery RemoveQuery = FGameplayEffectQuery();
	RemoveQuery.EffectDefinition = InClass;
	return InTarget->RemoveActiveEffects(RemoveQuery, InStacksToRemove);
}
//~ End Effects

//~ Begin Abilities
int32 UScWAbilitySystemGlobals::SendGameplayEventToComponent(UAbilitySystemComponent* InTargetASC, const FGameplayTag& InEventTag, const FGameplayEventData& InEventData)
{
	if (!InEventTag.IsValid() || !IsValid(InTargetASC))
	{
		return 0;
	}
	return InTargetASC->HandleGameplayEvent(InEventTag, &InEventData);
}
//~ End Abilities

//~ Begin Actor Info
APlayerController* UScWAbilitySystemGlobals::GetPlayerControllerFromASC(UAbilitySystemComponent* InTargetASC)
{
	ensureReturn(InTargetASC && InTargetASC->AbilityActorInfo, nullptr);
	return InTargetASC->AbilityActorInfo->PlayerController.Get();
}

AController* UScWAbilitySystemGlobals::GetControllerFromASC(UAbilitySystemComponent* InTargetASC)
{
	ensureReturn(InTargetASC && InTargetASC->AbilityActorInfo, nullptr);
	if (AController* PC = InTargetASC->AbilityActorInfo->PlayerController.Get())
	{
		return PC;
	}
	// Look for a player controller or pawn in the owner chain.
	AActor* TestActor = InTargetASC->AbilityActorInfo->OwnerActor.Get();
	while (TestActor)
	{
		if (AController* C = Cast<AController>(TestActor))
		{
			return C;
		}
		if (APawn* Pawn = Cast<APawn>(TestActor))
		{
			return Pawn->GetController();
		}
		TestActor = TestActor->GetOwner();
	}
	return nullptr;
}

ACharacter* UScWAbilitySystemGlobals::GetCharacterFromASC(UAbilitySystemComponent* InTargetASC)
{
	ensureReturn(InTargetASC && InTargetASC->AbilityActorInfo, nullptr);
	return Cast<ACharacter>(InTargetASC->AbilityActorInfo->AvatarActor.Get());
}
//~ End Actor Info
