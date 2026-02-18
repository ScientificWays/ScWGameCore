// Scientific Ways

#include "AbilitySystem/ScWAbilitySet.h"

#include "AbilitySystem/ScWGameplayAbility.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"

#include "Misc/DataValidation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWAbilitySet)

void FScWAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FScWAbilitySet_GrantedHandles::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{
		GameplayEffectHandles.Add(Handle);
	}
}

void FScWAbilitySet_GrantedHandles::AddAttributeSet(UAttributeSet* Set)
{
	GrantedAttributeSets.Add(Set);
}

void FScWAbilitySet_GrantedHandles::TakeFromAbilitySystem(UScWAbilitySystemComponent* InTargetASC)
{
	check(InTargetASC);

	if (!InTargetASC->IsOwnerActorAuthoritative())
	{
		// Must be authoritative to give or take ability sets.
		return;
	}
	// Tags
	InTargetASC->RemoveLooseGameplayTags(LooseGameplayTags);
	InTargetASC->RemoveMinimalReplicationGameplayTags(LooseGameplayTags);

	// Abilities
	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			InTargetASC->ClearAbility(Handle);
		}
	}
	// Effects
	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			InTargetASC->RemoveActiveGameplayEffect(Handle);
		}
	}
	// Attributes
	for (UAttributeSet* Set : GrantedAttributeSets)
	{
		InTargetASC->RemoveSpawnedAttribute(Set);
	}
	// Reset
	LooseGameplayTags.Reset();
	AbilitySpecHandles.Reset();
	GameplayEffectHandles.Reset();
	GrantedAttributeSets.Reset();
}

UScWAbilitySet::UScWAbilitySet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#if WITH_EDITOR
EDataValidationResult UScWAbilitySet::IsDataValid(FDataValidationContext& InContext) const // UObject
{
	auto OutResult = CombineDataValidationResults(Super::IsDataValid(InContext), EDataValidationResult::Valid);

	// Attribute Sets
	for (const auto& SampleEntry : GrantedAttributes)
	{
		// Invalid attribute set object
		if (!IsValid(SampleEntry.AttributeSet))
		{
			OutResult = CombineDataValidationResults(OutResult, EDataValidationResult::Invalid);
			InContext.AddError(FText::FromString("Invalid attribute set"));
			continue;
		}
		// Invalid attribute set data
		const auto AttributeSetResult = SampleEntry.AttributeSet->IsDataValid(InContext);
		OutResult = CombineDataValidationResults(OutResult, AttributeSetResult);

		// Invalid init data
		for (const auto& AttributeOverride : SampleEntry.InitData)
		{
			const auto AttributeKey = AttributeOverride.Key;
			if (!AttributeKey.IsValid())
			{
				OutResult = CombineDataValidationResults(OutResult, EDataValidationResult::Invalid);
				InContext.AddError(FText::FromString("Invalid selected attribute"));
				continue;
			}
			const auto IsValidAttributeData = SampleEntry.AttributeSet->HasProperty(AttributeKey.GetUProperty());
			if (!IsValidAttributeData)
			{
				OutResult = CombineDataValidationResults(OutResult, EDataValidationResult::Invalid);
				InContext.AddError(FText::FromString("Invalid selected attribute"));
			}
		}
	}
	return OutResult;
}
#endif

void UScWAbilitySet::GiveToAbilitySystem(UScWAbilitySystemComponent* InTargetASC, FScWAbilitySet_GrantedHandles* OutGrantedHandles, UObject* InSourceObject) const
{
	check(InTargetASC);

	if (!InTargetASC->IsOwnerActorAuthoritative())
	{
		// Must be authoritative to give or take ability sets
		return;
	}
	// Grant loose gameplay tags
	InTargetASC->AddLooseGameplayTags(GrantedLooseGameplayTags);
	InTargetASC->AddMinimalReplicationGameplayTags(GrantedLooseGameplayTags);

	// Grant the attribute sets
	for (int32 SetIndex = 0; SetIndex < GrantedAttributes.Num(); ++SetIndex)
	{
		const FScWAbilitySet_AttributeSet& SetToGrant = GrantedAttributes[SetIndex];

		if (!IsValid(SetToGrant.AttributeSet))
		{
			UE_LOG(LogScWGameCore, Error, TEXT("GrantedAttributes[%d] on ability set [%s] is not valid"), SetIndex, *GetNameSafe(this));
			continue;
		}
		UAttributeSet* NewSet = NewObject<UAttributeSet>(InTargetASC->GetOwner(), SetToGrant.AttributeSet);
		InTargetASC->AddAttributeSetSubobject(NewSet);

		for (const auto& Attribute : SetToGrant.InitData)
		{
			ensureContinue(Attribute.Key.IsValid());
			InTargetASC->SetNumericAttributeBase(Attribute.Key, Attribute.Value.GetValue());
		}
		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAttributeSet(NewSet);
		}
	}
	// Grant the gameplay abilities
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FScWAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogScWGameCore, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		UScWGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UScWGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = InSourceObject;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = InTargetASC->GiveAbility(AbilitySpec);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}
	// Grant the gameplay effects
	for (int32 EffectIndex = 0; EffectIndex < GrantedGameplayEffects.Num(); ++EffectIndex)
	{
		const FScWAbilitySet_GameplayEffect& EffectToGrant = GrantedGameplayEffects[EffectIndex];

		if (!IsValid(EffectToGrant.GameplayEffect))
		{
			UE_LOG(LogScWGameCore, Error, TEXT("GrantedGameplayEffects[%d] on ability set [%s] is not valid"), EffectIndex, *GetNameSafe(this));
			continue;
		}

		const UGameplayEffect* GameplayEffect = EffectToGrant.GameplayEffect->GetDefaultObject<UGameplayEffect>();
		const FActiveGameplayEffectHandle GameplayEffectHandle = InTargetASC->ApplyGameplayEffectToSelf(GameplayEffect, EffectToGrant.EffectLevel, InTargetASC->MakeEffectContext());

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddGameplayEffectHandle(GameplayEffectHandle);
		}
	}
}
