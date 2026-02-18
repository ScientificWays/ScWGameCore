// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Engine/DataAsset.h"

#include "AttributeSet.h"
#include "ScalableFloat.h"
#include "GameplayTagContainer.h"
#include "GameplayAbilitySpecHandle.h"
#include "ActiveGameplayEffectHandle.h"

#include "ScWAbilitySet.generated.h"

#define MODULE_API SCWGAMECORE_API

class UAttributeSet;
class UGameplayEffect;
class UScWAbilitySystemComponent;
class UScWGameplayAbility;
class UObject;


/**
 * FScWAbilitySet_GameplayAbility
 *
 *	Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FScWAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UScWGameplayAbility> Ability = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	// Tag used to process input for the ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};


/**
 * FScWAbilitySet_GameplayEffect
 *
 *	Data used by the ability set to grant gameplay effects.
 */
USTRUCT(BlueprintType)
struct FScWAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

/**
 * FScWAbilitySet_AttributeSet
 *
 *	Data used by the ability set to grant attribute sets.
 */
USTRUCT(BlueprintType)
struct FScWAbilitySet_AttributeSet
{
	GENERATED_BODY()

public:

	// Attribute set to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, meta = (ForceInlineRow))
	TMap<FGameplayAttribute, FScalableFloat> InitData;
};

/**
 * FScWAbilitySet_GrantedHandles
 *
 *	Data used to store handles to what has been granted by the ability set.
 */
USTRUCT(BlueprintType)
struct FScWAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	MODULE_API void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	MODULE_API void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	MODULE_API void AddAttributeSet(UAttributeSet* Set);

	MODULE_API void TakeFromAbilitySystem(UScWAbilitySystemComponent* InTargetASC);

protected:

	// Granted loose gameplay tags
	UPROPERTY()
	FGameplayTagContainer LooseGameplayTags;

	// Handles to the granted abilities.
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// Handles to the granted gameplay effects.
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	// Pointers to the granted attribute sets
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};


/**
 *	Non-mutable data asset used to grant gameplay abilities and gameplay effects.
 */
UCLASS(MinimalAPI, BlueprintType, Const, meta = (DisplayName = "[ScW] Ability Set"))
class UScWAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UScWAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& InContext) const override; // UObject
#endif

	// Grants the ability set to the specified ability system component.
	// The returned handles can be used later to take away anything that was granted.
	MODULE_API void GiveToAbilitySystem(UScWAbilitySystemComponent* InTargetASC, FScWAbilitySet_GrantedHandles* OutGrantedHandles, UObject* InSourceObject = nullptr) const;

protected:

	// Loose gameplay tags to grant when this ability set is given.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Tags")
	FGameplayTagContainer GrantedLooseGameplayTags;

	// Gameplay abilities to grant when this ability set is given.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta = (TitleProperty=Ability))
	TArray<FScWAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	// Gameplay effects to grant when this ability set is given.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta = (TitleProperty=GameplayEffect))
	TArray<FScWAbilitySet_GameplayEffect> GrantedGameplayEffects;

	// Attribute sets to grant when this ability set is given.
	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets", meta = (TitleProperty=AttributeSet))
	TArray<FScWAbilitySet_AttributeSet> GrantedAttributes;
};

#undef MODULE_API
