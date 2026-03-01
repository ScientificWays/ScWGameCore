// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "AbilitySystem/ScWGameplayAbility.h"

#include "Utils/ScWTypes_CommonDelegates.h"

#include "ScWAbilitySystemComponent.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "[ScW] ASC Base", BlueprintSpawnableComponent))
class UScWAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
//~ Begin Statics
public:

	UFUNCTION(Category = "Statics", BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get ScW Ability System Component from Actor"))
	static MODULE_API UScWAbilitySystemComponent* TryGetFromActor(const AActor* InActor, bool bInTryFindComponentIfNoInterface = true);
//~ End Statics

//~ Begin Initialize
public:
	MODULE_API UScWAbilitySystemComponent(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());
protected:
	MODULE_API virtual void OnRegister() override; // UActorComponent
	MODULE_API virtual void BeginPlay() override; // UActorComponent
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; // UActorComponent
public:
	MODULE_API virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override; // UAbilitySystemComponent

	UPROPERTY(Category = "Initialize", BlueprintAssignable)
	FDefaultEventSignature OnAbilityActorInfoInitialized;
//~ End Initialize

//~ Begin Abilities
public:

	typedef TFunctionRef<bool(const class UScWGameplayAbility* ScWAbility, FGameplayAbilitySpecHandle Handle)> TShouldCancelAbilityFunc;
	MODULE_API void CancelAbilitiesByFunc(TShouldCancelAbilityFunc ShouldCancelFunc, bool bReplicateCancelAbility);

	MODULE_API void CancelInputActivatedAbilities(bool bReplicateCancelAbility);

	MODULE_API void AbilityTagPressed(const FGameplayTag& InputTag);
	MODULE_API void AbilityTagReleased(const FGameplayTag& InputTag);

	MODULE_API void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	MODULE_API void ClearAbilityInput();

	MODULE_API bool IsActivationGroupBlocked(EScWAbilityActivationGroup Group) const;
	MODULE_API void AddAbilityToActivationGroup(EScWAbilityActivationGroup Group, class UScWGameplayAbility* ScWAbility);
	MODULE_API void RemoveAbilityFromActivationGroup(EScWAbilityActivationGroup Group, class UScWGameplayAbility* ScWAbility);
	MODULE_API void CancelActivationGroupAbilities(EScWAbilityActivationGroup Group, class UScWGameplayAbility* IgnoreScWAbility, bool bReplicateCancelAbility);

	/** Gets the ability target data associated with the given ability handle and activation info */
	MODULE_API void GetAbilityTargetData(const FGameplayAbilitySpecHandle AbilityHandle, FGameplayAbilityActivationInfo ActivationInfo, FGameplayAbilityTargetDataHandle& OutTargetDataHandle);

	/** Sets the current tag relationship mapping, if null it will clear it out */
	MODULE_API void SetTagRelationshipMapping(class UScWAbilityTagRelationshipMapping* NewMapping);

	/** Looks at ability tags and gathers additional required and blocking tags */
	MODULE_API void GetAdditionalActivationTagRequirements(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer& OutActivationRequired, FGameplayTagContainer& OutActivationBlocked) const;

	MODULE_API void TryActivateAbilitiesOnSpawn();

protected:

	MODULE_API virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	MODULE_API virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

	MODULE_API virtual void NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability) override;
	MODULE_API virtual void NotifyAbilityFailed(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason) override;
	MODULE_API virtual void NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, bool bWasCancelled) override;
	MODULE_API virtual void ApplyAbilityBlockAndCancelTags(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bEnableBlockTags, const FGameplayTagContainer& BlockTags, bool bExecuteCancelTags, const FGameplayTagContainer& CancelTags) override;
	MODULE_API virtual void HandleChangeAbilityCanBeCanceled(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bCanBeCanceled) override;

	/** Notify client that an ability failed to activate */
	UFUNCTION(Client, Unreliable)
	MODULE_API void ClientNotifyAbilityFailed(const UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason);

	MODULE_API void HandleAbilityFailed(const UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason);
protected:

	// If set, this table is used to look up tag relationships for activate and cancel
	UPROPERTY()
	TObjectPtr<class UScWAbilityTagRelationshipMapping> TagRelationshipMapping;

	// Handles to abilities that had their input pressed this frame.
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	// Handles to abilities that had their input released this frame.
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	// Handles to abilities that have their input held.
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;

	// Number of abilities running in each activation group.
	int32 ActivationGroupCounts[(uint8)EScWAbilityActivationGroup::MAX];

public:

	UFUNCTION(Category = "Abilities", BlueprintCallable)
	void ClearAbilities(UPARAM(Ref) TArray<FGameplayAbilitySpecHandle>& InHandleArray, const bool bInResetArray);

protected:

	template<class T>
	void AppendAbilityInstancesOrCDO(const FGameplayAbilitySpec& InSpec, TArray<T*>& OutArray) const;
//~ End Abilities

//~ Begin Effects
public:
	// Uses a gameplay effect to add the specified dynamic granted tag.
	UFUNCTION(Category = "Effects", BlueprintCallable)
	MODULE_API void AddDynamicTagGameplayEffect(const FGameplayTag& Tag);

	// Removes all active instances of the gameplay effect that was used to add the specified dynamic granted tag.
	UFUNCTION(Category = "Effects", BlueprintCallable)
	MODULE_API void RemoveDynamicTagGameplayEffect(const FGameplayTag& Tag);
//~ End Effects

//~ Begin Tags
protected:
	virtual void OnInputBlockMovementTagNumChanged(const FGameplayTag InCallbackTag, int32 InNewCount);
//~ End Tags
};

#undef MODULE_API
