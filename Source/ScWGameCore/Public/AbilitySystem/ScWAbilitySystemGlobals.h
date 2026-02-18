// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Utils/ScWTypes_CommonDelegates.h"

#include "ScWAbilitySystemGlobals.generated.h"

#define MODULE_API SCWGAMECORE_API

class UObject;
struct FGameplayEffectContext;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FGameplayTagNumChangedEvent, const FGameplayTag, InTag, int32, InNewNum);

UCLASS(Config = Game, meta = (DisplayName = "[ScW] Ability System Globals"))
class UScWAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_UCLASS_BODY()

	/** Gets the single instance of the globals object, will create it as necessary */
	static ThisClass& Get() { return *Cast<ThisClass>(IGameplayAbilitiesModule::Get().GetAbilitySystemGlobals()); }

//~ Begin Tags
public:

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API void AddLooseGameplayTag(UAbilitySystemComponent* InASC, FGameplayTag InGameplayTag, int32 InCount = 1)
	{ InASC->AddLooseGameplayTag(InGameplayTag, InCount); }

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API void AddLooseGameplayTags(UAbilitySystemComponent* InASC, FGameplayTagContainer InGameplayTags, int32 InCount = 1)
	{ InASC->AddLooseGameplayTags(InGameplayTags, InCount); }

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API void RemoveLooseGameplayTag(UAbilitySystemComponent* InASC, FGameplayTag InGameplayTag, int32 InCount = 1)
	{ InASC->RemoveLooseGameplayTag(InGameplayTag, InCount); }

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API void RemoveLooseGameplayTags(UAbilitySystemComponent* InASC, FGameplayTagContainer InGameplayTags, int32 InCount = 1)
	{ InASC->RemoveLooseGameplayTags(InGameplayTags, InCount); }

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API void SetLooseGameplayTagCount(UAbilitySystemComponent* InASC, FGameplayTag InGameplayTag, int32 InNewCount)
	{ InASC->SetLooseGameplayTagCount(InGameplayTag, InNewCount); }

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API FDelegateHandle_BlueprintWrapper RegisterGameplayTagEvent(UAbilitySystemComponent* InASC, FGameplayTagNumChangedEvent InEvent, FGameplayTag InTag, EGameplayTagEventType::Type InType = EGameplayTagEventType::NewOrRemoved);

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API void UnRegisterGameplayTagEvent(UAbilitySystemComponent* InASC, FDelegateHandle_BlueprintWrapper InHandle, FGameplayTag InTag, EGameplayTagEventType::Type InType = EGameplayTagEventType::NewOrRemoved);

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API void GetOwnedGameplayTags(UObject* InTarget, FGameplayTagContainer& OutTagContainer);

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API bool TargetHasMatchingGameplayTag(UObject* InTarget, const FGameplayTag& InTag);

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API bool TargetHasAllMatchingGameplayTags(UObject* InTarget, const FGameplayTagContainer& InTagContainer);

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API bool TargetHasAnyMatchingGameplayTags(UObject* InTarget, const FGameplayTagContainer& InTagContainer);

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext, KeyWords = "IsPlayerCharacter", ExpandBoolAsExecs = "ReturnValue"))
	static MODULE_API bool IsPlayerPawnType(UObject* InTarget);

	UFUNCTION(Category = "Tags", BlueprintCallable, meta = (CallableWithoutWorldContext))
	static MODULE_API const FGameplayTagContainer& GetIgnoreDamageTags() { return ThisClass::Get().IgnoreDamageTags; }

protected:
	virtual void InitGlobalTags() override; // UAbilitySystemGlobals

	UPROPERTY()
	FGameplayTagContainer IgnoreDamageTags;
//~ End Tags

//~ Begin Effects
protected:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override; // UAbilitySystemGlobals
public:

	UFUNCTION(Category = "Effects", BlueprintCallable)
	static MODULE_API FActiveGameplayEffectHandle TryApplyGameplayEffectByClass(UAbilitySystemComponent* InTarget, TSubclassOf<UGameplayEffect> InClass, float InDuration = -1.0f, float InMagnitude = 0.0f, float InLevel = 1.0f);

	UFUNCTION(Category = "Effects", BlueprintCallable)
	static MODULE_API int32 TryRemoveGameplayEffectByClass(UAbilitySystemComponent* InTarget, TSubclassOf<UGameplayEffect> InClass, int32 InStacksToRemove = -1);

	UFUNCTION(Category = "Effects", BlueprintCallable, BlueprintPure)
	static MODULE_API bool IsValidEffectHandle(UPARAM(Ref) const FActiveGameplayEffectHandle& InHandle) { return InHandle.IsValid(); }

	UFUNCTION(Category = "Effects", BlueprintCallable)
	static MODULE_API FActiveGameplayEffectHandle& InvalidateEffectHandle(UPARAM(Ref) FActiveGameplayEffectHandle& InHandle) { InHandle.Invalidate(); return InHandle; }

	UFUNCTION(Category = "Effects", BlueprintCallable, BlueprintPure)
	static MODULE_API bool WasSuccessfullyAppliedEffectHandle(UPARAM(Ref) const FActiveGameplayEffectHandle& InHandle) { return InHandle.WasSuccessfullyApplied(); }
//~ End Effects

//~ Begin Abilities
public:
	
	UFUNCTION(Category = "Abilities", BlueprintCallable, BlueprintPure)
	static MODULE_API bool IsValidAbilitySpecHandle(UPARAM(Ref) const FGameplayAbilitySpecHandle& InHandle) { return InHandle.IsValid(); }

	UFUNCTION(Category = "Abilities", BlueprintCallable)
	static MODULE_API FGameplayAbilitySpecHandle& InvalidateAbilitySpecHandle(UPARAM(Ref) FGameplayAbilitySpecHandle& InHandle) { InHandle = FGameplayAbilitySpecHandle(); return InHandle; }


	/**
	 * Sends a Gameplay Event to the Ability System Component.
	 *
	 * @param InTargetASC		Ability Component receiving the event.
	 * @param InEventTag		Gameplay Tag identifying the Gameplay Event.
	 * @param InEventData		Payload for the Gameplay Event.
	 * @return					The number of successful ability activations triggered by the event.
	 */
	UFUNCTION(Category = "Abilities", BlueprintCallable, meta = (ReturnDisplayName = "Out Activations"))
	static MODULE_API int32 SendGameplayEventToComponent(UAbilitySystemComponent* InTargetASC, const FGameplayTag& InEventTag, const FGameplayEventData& InEventData);
//~ End Abilities
	
//~ Begin Actor Info
public:

	UFUNCTION(Category = "Actor Info", BlueprintCallable, BlueprintPure)
	static MODULE_API APlayerController* GetPlayerControllerFromASC(UAbilitySystemComponent* InTargetASC);

	UFUNCTION(Category = "Actor Info", BlueprintCallable, BlueprintPure)
	static MODULE_API AController* GetControllerFromASC(UAbilitySystemComponent* InTargetASC);

	UFUNCTION(Category = "Actor Info", BlueprintCallable, BlueprintPure)
	static MODULE_API ACharacter* GetCharacterFromASC(UAbilitySystemComponent* InTargetASC);
//~ End Actor Info
};

#undef MODULE_API
