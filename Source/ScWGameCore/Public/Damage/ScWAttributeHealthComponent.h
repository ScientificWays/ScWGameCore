// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Utils/ScWTypes_CommonDelegates.h"

#include "ScWAttributeHealthComponent.generated.h"

#define MODULE_API SCWGAMECORE_API

USTRUCT(BlueprintType)
struct FReceivedDamageData
{
	GENERATED_BODY()

	UPROPERTY(Category = "Data", BlueprintReadWrite, EditAnywhere)
	FHitResult HitResult = FHitResult();

	UPROPERTY(Category = "Data", BlueprintReadWrite, EditAnywhere)
	TObjectPtr<const class UScWDamageType> DamageType = nullptr;

	UPROPERTY(Category = "Data", BlueprintReadWrite, EditAnywhere)
	TObjectPtr<AActor> Source = nullptr;

	UPROPERTY(Category = "Data", BlueprintReadWrite, EditAnywhere)
	TObjectPtr<AController> Instigator = nullptr;

	FReceivedDamageData(const FHitResult& InHitResult = FHitResult(), const class UScWDamageType* InDamageType = nullptr, AActor* InSource = nullptr, AController* InInstigator = nullptr)
		: HitResult(InHitResult), DamageType(InDamageType), Source(InSource), Instigator(InInstigator) {}

	UAbilitySystemComponent* TryGetAttackerASC() const;
	FString ToAnalyticsString() const;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDamageEventSignature, float, InDamage, const FReceivedDamageData&, InData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAccumulatedDamageResolveEventSignature, float, InDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputEventSignature, int32, InInputID);

/**
 * 
 */
UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "[ScW] Attribute Health Component", BlueprintSpawnableComponent))
class UScWAttributeHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:

	UScWAttributeHealthComponent();
	
//~ Begin Initialize
protected:
	virtual void OnRegister() override; // UActorComponent
	virtual void OnUnregister() override; // UActorComponent
	virtual void BeginPlay() override; // UActorComponent
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; // UActorComponent
//~ End Initialize
	
//~ Begin Ability System
protected:
	virtual void InitializeFromAbilitySystem();
	virtual void UninitializeFromAbilitySystem();
	virtual void ClearGameplayTags();
//~ End Ability System

//~ Begin Attributes
public:

	UFUNCTION(Category = "Attributes", BlueprintCallable, meta = (KeyWords = "CurrentHealth"))
	MODULE_API FORCEINLINE float GetHealth() const;

	UFUNCTION(Category = "Attributes", BlueprintCallable)
	MODULE_API FORCEINLINE float GetMaxHealth() const;

	UFUNCTION(Category = "Attributes", BlueprintCallable)
	MODULE_API FORCEINLINE float GetHealthNormalized() const;

	UFUNCTION(Category = "Attributes", BlueprintCallable)
	MODULE_API FORCEINLINE bool IsFullHealth(const bool bInCheckHasHealth) const;

	UFUNCTION(Category = "Attributes", BlueprintCallable)
	MODULE_API void SetHealth(float InHealth);

	UFUNCTION(Category = "Attributes", BlueprintCallable)
	MODULE_API void AddHealth(float InHealth);

	UPROPERTY(Category = "Attributes", BlueprintAssignable)
	FAttributeChangedSignature OnHealthChanged;

	UPROPERTY(Category = "Attributes", BlueprintAssignable)
	FAttributeChangedSignature OnMaxHealthChanged;

protected:
	virtual void OnHealthAttributeChanged(const FOnAttributeChangeData& InData);
	virtual void OnMaxHealthAttributeChanged(const FOnAttributeChangeData& InData);
	virtual void OnZeroHealth();

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute HealthAttribute;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute MaxHealthAttribute;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
//~ End Attributes

//~ Begin Damage
public:
	MODULE_API float GetLastAppliedDamage() const { return LastAppliedDamage; }
	MODULE_API const FReceivedDamageData& GetLastAppliedDamageData() const { return LastAppliedDamageData; }
	MODULE_API float GetLastAppliedDamagePrevHealth() const { return LastAppliedDamagePrevHealth; }

	UPROPERTY(Category = "Damage", BlueprintAssignable)
	FDamageEventSignature OnDamageIgnored;

	UPROPERTY(Category = "Damage", BlueprintAssignable)
	FDamageEventSignature OnDamageBlocked;

	UPROPERTY(Category = "Damage", BlueprintAssignable)
	FDamageEventSignature OnDamageEvaded;

	UPROPERTY(Category = "Damage", BlueprintAssignable)
	FDamageEventSignature OnDamageApplied;

	UPROPERTY(Category = "Damage | Accumulated | Applied", BlueprintReadOnly)
	bool bEnableAccumulatedAppliedDamage;

	UFUNCTION(Category = "Damage | Accumulated | Applied", BlueprintCallable)
	MODULE_API void AccumulateAppliedDamage(float InDamage, bool bInAutoResolveNextTick = true);

	UPROPERTY(Category = "Damage | Accumulated | Applied", BlueprintReadOnly)
	float AccumulatedAppliedDamage;

	UFUNCTION(Category = "Damage | Accumulated | Applied", BlueprintCallable)
	MODULE_API void RequestResolveAccumulatedAppliedDamageNextTick();
	MODULE_API void ResolveAccumulatedAppliedDamageFromNextTickTimer();
	FTimerHandle AccumulatedAppliedDamageTimerHandle;

	UFUNCTION(Category = "Damage | Accumulated | Applied", BlueprintCallable)
	MODULE_API void ResolveAccumulatedAppliedDamage();

	UPROPERTY(Category = "Damage | Accumulated | Applied", BlueprintAssignable)
	FAccumulatedDamageResolveEventSignature OnAccumulatedAppliedDamageResolved;

	UPROPERTY(Category = "Damage | Accumulated | Applied", BlueprintReadWrite, EditAnywhere)
	float AccumulatedAppliedDamageResetTime;

	UFUNCTION(Category = "Damage | Accumulated | Applied", BlueprintCallable)
	MODULE_API void ResetAccumulatedAppliedDamage();
	FTimerHandle AccumulatedAppliedDamageResetTimerHandle;

protected:

	UFUNCTION()
	void OnOwnerTakePointDamage(AActor* InDamagedActor, float InDamage, AController* InInstigator, FVector InHitLocation, UPrimitiveComponent* InHitComponent, FName InBoneName, FVector InHitDirection, const UDamageType* InDamageType, AActor* InDamageCauser);

	UFUNCTION()
	void OnOwnerTakeRadialDamage(AActor* InDamagedActor, float InDamage, const UDamageType* InDamageType, FVector InOrigin, const FHitResult& InHitResult, AController* InInstigator, AActor* InDamageCauser);

	bool HandleTryReceiveDamage(float InDamage, const FReceivedDamageData& InData);

	bool ShouldIgnoreAnyAttackFrom(AController* InInstigator) const;
	bool TryIgnoreDamage(float& InOutAdjustedDamage, const FReceivedDamageData& InData);
	bool TryBlockDamage(float& InOutAdjustedDamage, const FReceivedDamageData& InData);
	bool TryEvadeDamage(float& InOutAdjustedDamage, const FReceivedDamageData& InData);
	bool TryApplyDamage(float InDamage, const FReceivedDamageData& InData);

	UPROPERTY(Category = "Damage", BlueprintReadOnly)
	float LastAppliedDamage;

	UPROPERTY(Category = "Damage", BlueprintReadOnly)
	FReceivedDamageData LastAppliedDamageData;

	UPROPERTY(Category = "Damage", BlueprintReadOnly)
	float LastAppliedDamagePrevHealth;

	UPROPERTY(Category = "Damage", BlueprintReadOnly, EditAnywhere)
	float ExplosionStumbleMinDuration;
//~ End Damage

//~ Begin Death
public:

	UPROPERTY(Category = "Death", EditDefaultsOnly, BlueprintReadOnly)
	bool bShouldDieOnZeroHealth;

	UPROPERTY(Category = "Death", EditDefaultsOnly, BlueprintReadWrite)
	bool bDestroyOwnerNextTickOnDeath;

	UPROPERTY(Category = "Death", BlueprintAssignable)
	FDefaultEventSignature OnDied;

protected:
	virtual void HandleDied();

	UFUNCTION(Category = "Death", BlueprintNativeEvent, meta = (DisplayName = "Post Death Behavior"))
	MODULE_API void BP_HandlePostDeathBehavior();
//~ End Death

//~ Begin Analytics
public:

	UPROPERTY(Category = "Analytics", EditAnywhere, BlueprintReadWrite)
	bool bSendDiedDesignEvent;
//~ End Analytics
};

#undef MODULE_API
