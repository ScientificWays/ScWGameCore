// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Abilities/GameplayAbility.h"

#include "ScWGameplayAbility.generated.h"

#define MODULE_API SCWGAMECORE_API

#define ensureCancelAbilityReturn(InCondition, ...) ensure(InCondition); if (!(InCondition)) { K2_CancelAbility(); return __VA_ARGS__; };

#define COMMON_WAIT_DELAY_OR_FINISH_NEXT_TICK_TASK(InVariableName, InTime, InMethodName) \
	UScWAT_WaitDelay* InVariableName = UScWAT_WaitDelay::WaitDelayOrFinishNextTick(this, InTime); \
	InVariableName->OnFinish.AddDynamic(this, &ThisClass::InMethodName); \
	InVariableName->ReadyForActivation();

struct FGameplayAbilityActivationInfo;
struct FGameplayAbilitySpec;
struct FGameplayAbilitySpecHandle;

class AActor;
class AController;
class AScWPlayerController;
class APlayerController;
class FText;
//class IScWAbilitySourceInterface;
class UAnimMontage;
class UScWAbilityCost;
class UScWAbilitySystemComponent;
//class UScWCameraMode;
class UScWHeroComponent;
class UObject;
struct FFrame;
struct FGameplayAbilityActorInfo;
struct FGameplayEffectSpec;
struct FGameplayEventData;

/**
 *	Defines how an ability is meant to activate.
 */
UENUM(BlueprintType)
enum class EScWAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn
};

/**
 *	Defines how an ability activates in relation to other abilities.
 */
UENUM(BlueprintType)
enum class EScWAbilityActivationGroup : uint8
{
	// Ability runs independently of all other abilities.
	Independent,

	// Ability is canceled and replaced by other exclusive abilities.
	Exclusive_Replaceable,

	// Ability blocks all other exclusive abilities from activating.
	Exclusive_Blocking,

	MAX	UMETA(Hidden)
};

/** Failure reason that can be used to play an animation montage when a failure occurs */
USTRUCT(BlueprintType)
struct FScWAbilityMontageFailureMessage
{
	GENERATED_BODY()

public:
	// Player controller that failed to activate the ability, if the AbilitySystemComponent was player owned
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	// Avatar actor that failed to activate the ability
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> AvatarActor = nullptr;

	// All the reasons why this ability has failed
	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer FailureTags;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAnimMontage> FailureMontage = nullptr;
};

/**
 *	The base gameplay ability class used in ScW framework.
 */
UCLASS(MinimalAPI, Abstract, meta = (DisplayName = "[ScW] Gameplay Ability", ShortTooltip = "The base gameplay ability class used in ScW framework."))
class UScWGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	friend class UScWAbilitySystemComponent;
public:

	MODULE_API UScWGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Actor Info")
	MODULE_API UScWAbilitySystemComponent* GetScWAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Actor Info")
	MODULE_API APlayerController* GetPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Actor Info")
	MODULE_API AController* GetControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Actor Info")
	MODULE_API ACharacter* GetCharacterFromActorInfo() const;

	EScWAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }
	EScWAbilityActivationGroup GetActivationGroup() const { return ActivationGroup; }

	MODULE_API void TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const;

	// Returns true if the requested activation group is a valid transition.
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Ability Activation", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	MODULE_API bool CanChangeActivationGroup(EScWAbilityActivationGroup NewGroup) const;

	// Tries to change the activation group.  Returns true if it successfully changed.
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Ability Activation", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	MODULE_API bool ChangeActivationGroup(EScWAbilityActivationGroup NewGroup);

	void OnAbilityFailedToActivate(const FGameplayTagContainer& FailedReason) const
	{
		NativeOnAbilityFailedToActivate(FailedReason);
		ScriptOnAbilityFailedToActivate(FailedReason);
	}

protected:

	// Called when the ability fails to activate
	MODULE_API virtual void NativeOnAbilityFailedToActivate(const FGameplayTagContainer& FailedReason) const;

	// Called when the ability fails to activate
	UFUNCTION(BlueprintImplementableEvent)
	MODULE_API void ScriptOnAbilityFailedToActivate(const FGameplayTagContainer& FailedReason) const;

	//~UGameplayAbility interface
	MODULE_API virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	MODULE_API virtual void SetCanBeCanceled(bool bCanBeCanceled) override;
	MODULE_API virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	MODULE_API virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	MODULE_API virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	MODULE_API virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	MODULE_API virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	MODULE_API virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	MODULE_API virtual FGameplayEffectContextHandle MakeEffectContext(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const override;
	MODULE_API virtual void ApplyAbilityTagsToGameplayEffectSpec(FGameplayEffectSpec& Spec, FGameplayAbilitySpec* AbilitySpec) const override;
	MODULE_API virtual bool DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	//~End of UGameplayAbility interface

	MODULE_API virtual void OnPawnAvatarSet();

	//MODULE_API virtual void GetAbilitySource(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, float& OutSourceLevel, const IScWAbilitySourceInterface*& OutAbilitySource, AActor*& OutEffectCauser) const;

	/** Called when this ability is granted to the ability system component. */
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnAbilityAdded")
	MODULE_API void K2_OnAbilityAdded();

	/** Called when this ability is removed from the ability system component. */
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnAbilityRemoved")
	MODULE_API void K2_OnAbilityRemoved();

	/** Called when the ability system is initialized with a pawn avatar. */
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnPawnAvatarSet")
	MODULE_API void K2_OnPawnAvatarSet();
	
	UFUNCTION(Category = "Input", BlueprintCallable, meta = (KeyWords = "IsInputPressed"))
	MODULE_API bool IsAbilityInputPressed() const;
	
protected:

	// Defines how this ability is meant to activate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Activation")
	EScWAbilityActivationPolicy ActivationPolicy;

	// Defines the relationship between this ability activating and other abilities activating.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Activation")
	EScWAbilityActivationGroup ActivationGroup;

	// Additional costs that must be paid to activate this ability
	UPROPERTY(EditDefaultsOnly, Instanced, Category = Costs)
	TArray<TObjectPtr<UScWAbilityCost>> AdditionalCosts;

	// Map of failure tags to simple error messages
	UPROPERTY(EditDefaultsOnly, Category = "Advanced")
	TMap<FGameplayTag, FText> FailureTagToUserFacingMessages;

	// Map of failure tags to anim montages that should be played with them
	UPROPERTY(EditDefaultsOnly, Category = "Advanced")
	TMap<FGameplayTag, TObjectPtr<UAnimMontage>> FailureTagToAnimMontage;

	// If true, extra information should be logged when this ability is canceled. This is temporary, used for tracking a bug.
	UPROPERTY(EditDefaultsOnly, Category = "Advanced")
	bool bLogCancelation;
};

#undef MODULE_API
