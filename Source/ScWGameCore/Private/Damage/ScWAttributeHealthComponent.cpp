// Scientific Ways

#include "Damage/ScWAttributeHealthComponent.h"

#include "AbilitySystem/ScWCoreTags.h"
#include "AbilitySystem/Attributes/ScWAS_Health.h"
#include "AbilitySystem/ScWAbilitySystemGlobals.h"

#include "Character/ScWPawnExtensionComponent.h"

#include "Damage/ScWDamageType.h"

#include "System/ScWGameData.h"
#include "System/ScWAssetManager.h"

#include "Perception/AISenseConfig_Damage.h"

UAbilitySystemComponent* FReceivedDamageData::TryGetAttackerASC() const
{
	UAbilitySystemComponent* OutASC = nullptr;

	if (UAbilitySystemComponent* SourceASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Source))
	{
		OutASC = SourceASC;
	}
	else if (Instigator)
	{
		if (UAbilitySystemComponent* InstigatorASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Instigator))
		{
			OutASC = InstigatorASC;
		}
		else if (UAbilitySystemComponent* InstigatorPawnASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Instigator->GetPawn()))
		{
			OutASC = InstigatorPawnASC;
		}
	}
	return OutASC;
}

FString FReceivedDamageData::ToAnalyticsString() const
{
	FString OutString;
	OutString += FString::Printf(TEXT("DamageType:%s;"), DamageType ? *DamageType->AnalyticsName : TEXT("None"));
	OutString += FString::Printf(TEXT("Source:%s;"), Source ? *Source->GetName() : TEXT("None"));
	OutString += FString::Printf(TEXT("Instigator:%s;"), Instigator ? *Instigator->GetName() : TEXT("None"));
	OutString += FString::Printf(TEXT("HitLocation:%s;"), *GET_ROUNDED_VECTOR_STRING(HitResult.ImpactPoint));
	OutString += FString::Printf(TEXT("HitBone:%s;"), *HitResult.BoneName.ToString());
	return OutString;
}

UScWAttributeHealthComponent::UScWAttributeHealthComponent()
{
	HealthAttribute = UScWAS_Health::GetHealthAttribute();
	MaxHealthAttribute = UScWAS_Health::GetMaxHealthAttribute();

	bEnableAccumulatedAppliedDamage = true;
	AccumulatedAppliedDamageResetTime = 1.5f;
	bShouldDieOnZeroHealth = true;

	bSendDiedDesignEvent = true;
}

//~ Begin Initialize
void UScWAttributeHealthComponent::OnRegister() // UActorComponent
{
	Super::OnRegister();

	AActor* OwnerActor = GetOwner();
	check(OwnerActor);

	UScWPawnExtensionComponent* OwnerPawnExtComponent = UScWPawnExtensionComponent::FindPawnExtensionComponent(OwnerActor);
	ensureReturn(OwnerPawnExtComponent);

	OwnerPawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::InitializeFromAbilitySystem));
	OwnerPawnExtComponent->OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::UninitializeFromAbilitySystem));

}

void UScWAttributeHealthComponent::OnUnregister() // UActorComponent
{
	UninitializeFromAbilitySystem();

	Super::OnUnregister();
}

void UScWAttributeHealthComponent::BeginPlay() // UActorComponent
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		AActor* OwnerActor = GetOwner();
		check(OwnerActor);

		OwnerActor->OnTakePointDamage.AddDynamic(this, &ThisClass::OnOwnerTakePointDamage);
		OwnerActor->OnTakeRadialDamage.AddDynamic(this, &ThisClass::OnOwnerTakeRadialDamage);
	}
}

void UScWAttributeHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) // UActorComponent
{
	Super::EndPlay(EndPlayReason);

	ResolveAccumulatedAppliedDamage();
}
//~ End Initialize

//~ Begin Ability System
void UScWAttributeHealthComponent::InitializeFromAbilitySystem()
{
	AActor* Owner = GetOwner();
	ensureReturn(Owner);

	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner);
	ensureReturn(OwnerASC);

	ensureReturn(OwnerASC->GetGameplayAttributeValueChangeDelegate(HealthAttribute).IsBoundToObject(this) == false);
	ensureReturn(OwnerASC->GetGameplayAttributeValueChangeDelegate(MaxHealthAttribute).IsBoundToObject(this) == false);

	HealthChangedDelegateHandle = OwnerASC->GetGameplayAttributeValueChangeDelegate(HealthAttribute).AddUObject(this, &ThisClass::OnHealthAttributeChanged);
	MaxHealthChangedDelegateHandle = OwnerASC->GetGameplayAttributeValueChangeDelegate(MaxHealthAttribute).AddUObject(this, &ThisClass::OnMaxHealthAttributeChanged);

	// TEMP: Reset attributes to default values. Eventually this will be driven by a spread sheet.
	OwnerASC->SetNumericAttributeBase(HealthAttribute, GetMaxHealth());

	ClearGameplayTags();

	OnHealthChanged.Broadcast(HealthAttribute, GetHealth(), GetHealth());
	OnMaxHealthChanged.Broadcast(MaxHealthAttribute, GetMaxHealth(), GetMaxHealth());
}

void UScWAttributeHealthComponent::UninitializeFromAbilitySystem()
{
	AActor* Owner = GetOwner();
	ensureReturn(Owner);

	if (UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Owner))
	{
		OwnerASC->GetGameplayAttributeValueChangeDelegate(HealthAttribute).RemoveAll(this);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(MaxHealthAttribute).RemoveAll(this);
	}
	ClearGameplayTags();
}

void UScWAttributeHealthComponent::ClearGameplayTags()
{
	if (UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		OwnerASC->SetLooseGameplayTagCount(FScWCoreTags::State_Dead_Started, 0);
		OwnerASC->SetLooseGameplayTagCount(FScWCoreTags::State_Dead_Finished, 0);
	}
}
//~ End Ability System

//~ Begin Attributes
float UScWAttributeHealthComponent::GetHealth() const
{
	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	ensureReturn(OwnerASC, 0.0f);
	bool bFound;
	return OwnerASC->GetGameplayAttributeValue(HealthAttribute, bFound);
}

float UScWAttributeHealthComponent::GetMaxHealth() const
{
	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	ensureReturn(OwnerASC, 0.0f);
	bool bFound;
	return OwnerASC->GetGameplayAttributeValue(MaxHealthAttribute, bFound);
}

float UScWAttributeHealthComponent::GetHealthNormalized() const
{
	return ((GetMaxHealth() > 0.0f) ? (GetHealth() / GetMaxHealth()) : 0.0f);
}

bool UScWAttributeHealthComponent::IsFullHealth(const bool bInCheckHasHealth) const
{
	return (!bInCheckHasHealth || GetMaxHealth() > 0.0f) && GetHealth() == GetMaxHealth();
}

void UScWAttributeHealthComponent::SetHealth(float InHealth)
{
	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	ensureReturn(OwnerASC);

	const TSubclassOf<UGameplayEffect> SetHealthGE = UScWAssetManager::GetSubclass(UScWGameData::Get().SetHealthGameplayEffect_SetByCaller);
	ensureReturn(SetHealthGE);
	UScWAbilitySystemGlobals::TryApplyGameplayEffectByClass(OwnerASC, SetHealthGE, -1.0f, InHealth);
}

void UScWAttributeHealthComponent::AddHealth(float InHealth)
{
	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	ensureReturn(OwnerASC);

	const TSubclassOf<UGameplayEffect> AddHealthGE = UScWAssetManager::GetSubclass(UScWGameData::Get().AddHealthGameplayEffect_SetByCaller);
	ensureReturn(AddHealthGE);
	UScWAbilitySystemGlobals::TryApplyGameplayEffectByClass(OwnerASC, AddHealthGE, -1.0f, InHealth);
}

void UScWAttributeHealthComponent::OnHealthAttributeChanged(const FOnAttributeChangeData& InData)
{
	OnHealthChanged.Broadcast(InData.Attribute, InData.OldValue, InData.NewValue);

	if (InData.NewValue == 0.0f)
	{
		OnZeroHealth();
	}
}

void UScWAttributeHealthComponent::OnMaxHealthAttributeChanged(const FOnAttributeChangeData& InData)
{
	OnMaxHealthChanged.Broadcast(InData.Attribute, InData.OldValue, InData.NewValue);
}

void UScWAttributeHealthComponent::OnZeroHealth()
{
	if (bShouldDieOnZeroHealth)
	{
		HandleDied();
	}
}
//~ End Attributes

//~ Begin Damage
#define ACCUMULATED_DAMAGE_DECLARE_METHODS(InRoute) \
void UScWAttributeHealthComponent::Accumulate##InRoute##Damage(float InDamage, bool bInAutoResolveNextTick) \
{ \
	if (bEnableAccumulated##InRoute##Damage) \
	{ \
		Accumulated##InRoute##Damage += InDamage; \
		RequestResolveAccumulated##InRoute##DamageNextTick(); \
	} \
} \
void UScWAttributeHealthComponent::RequestResolveAccumulated##InRoute##DamageNextTick() \
{ \
	if (!Accumulated##InRoute##DamageTimerHandle.IsValid()) \
	{ \
		if (UWorld* World = GetWorld()) \
		{ \
			FTimerManager& WorldTimerManager = World->GetTimerManager(); \
			check(!WorldTimerManager.TimerExists(Accumulated##InRoute##DamageTimerHandle)); \
			Accumulated##InRoute##DamageTimerHandle = WorldTimerManager.SetTimerForNextTick(this, &UScWAttributeHealthComponent::ResolveAccumulated##InRoute##DamageFromNextTickTimer); \
			if (Accumulated##InRoute##DamageResetTime > 0.0f) \
				WorldTimerManager.SetTimer(Accumulated##InRoute##DamageResetTimerHandle, this, &UScWAttributeHealthComponent::ResetAccumulated##InRoute##Damage, Accumulated##InRoute##DamageResetTime); \
		} \
	} \
} \
void UScWAttributeHealthComponent::ResolveAccumulated##InRoute##DamageFromNextTickTimer() \
{ \
	ResolveAccumulated##InRoute##Damage(); \
	if (Accumulated##InRoute##DamageResetTime <= 0.0f) \
		ResetAccumulated##InRoute##Damage(); \
} \
void UScWAttributeHealthComponent::ResolveAccumulated##InRoute##Damage() \
{ \
	if (UWorld* World = GetWorld()) \
		World->GetTimerManager().ClearTimer(Accumulated##InRoute##DamageTimerHandle); \
	if (Accumulated##InRoute##Damage != 0.0f) \
		OnAccumulated##InRoute##DamageResolved.Broadcast(Accumulated##InRoute##Damage); \
} \
void UScWAttributeHealthComponent::ResetAccumulated##InRoute##Damage() \
{ \
	Accumulated##InRoute##Damage = 0.0f; \
}

//ACCUMULATED_DAMAGE_DECLARE_METHODS(Ignored)
//ACCUMULATED_DAMAGE_DECLARE_METHODS(Blocked)
//ACCUMULATED_DAMAGE_DECLARE_METHODS(Evaded)
ACCUMULATED_DAMAGE_DECLARE_METHODS(Applied)

#undef ACCUMULATED_DAMAGE_DECLARE_METHODS

void UScWAttributeHealthComponent::OnOwnerTakePointDamage(AActor* InDamagedActor, float InDamage, AController* InInstigator, FVector InHitLocation, UPrimitiveComponent* InHitComponent, FName InBoneName, FVector InHitDirection, const UDamageType* InDamageType, AActor* InDamageCauser)
{
	const UScWDamageType* ScWDamageType = Cast<UScWDamageType>(InDamageType);
	ensure(ScWDamageType);
	
	FHitResult MinimalInfoHitResult;
	UScWDamageType::MakeMinimalInfoDamageImpactHitResult(InDamageCauser, nullptr, (InInstigator ? InInstigator->GetPawn() : nullptr), InDamagedActor, InHitComponent, MinimalInfoHitResult);
	HandleTryReceiveDamage(InDamage, { MinimalInfoHitResult, ScWDamageType, InDamageCauser, InInstigator });
}

void UScWAttributeHealthComponent::OnOwnerTakeRadialDamage(AActor* InDamagedActor, float InDamage, const UDamageType* InDamageType, FVector InOrigin, const FHitResult& InHitResult, AController* InInstigator, AActor* InDamageCauser)
{
	const UScWDamageType* ScWDamageType = Cast<UScWDamageType>(InDamageType);
	ensure(ScWDamageType);
	HandleTryReceiveDamage(InDamage, { InHitResult, ScWDamageType, InDamageCauser, InInstigator });
}

bool UScWAttributeHealthComponent::HandleTryReceiveDamage(float InDamage, const FReceivedDamageData& InData)
{
	check(GetOwnerRole() == ROLE_Authority);

	AActor* OwnerActor = GetOwner();
	check(OwnerActor);

	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwnerActor);
	check(OwnerASC);

	FVector SourceLocation = FVector::ZeroVector;

	if (InData.Source)
	{
		SourceLocation = InData.Source->GetActorLocation();
	}
	else if (InData.Instigator && InData.Instigator->GetPawn())
	{
		SourceLocation = InData.Instigator->GetPawn()->GetActorLocation();
	}
	else
	{
		SourceLocation = OwnerActor->GetActorLocation();
	}
	UAISense_Damage::ReportDamageEvent(this, OwnerActor, InData.Instigator, InDamage, SourceLocation, InData.HitResult.Location);

	if (OwnerASC->HasMatchingGameplayTag(FScWCoreTags::Cheat_Invulnerable))
	{
		return false;
	}
	else if (TryIgnoreDamage(InDamage, InData))
	{
		OnDamageIgnored.Broadcast(InDamage, InData);
		return false;
	}
	else if (TryBlockDamage(InDamage, InData))
	{
		OnDamageBlocked.Broadcast(InDamage, InData);
		return false;
	}
	else if (TryEvadeDamage(InDamage, InData))
	{
		OnDamageEvaded.Broadcast(InDamage, InData);
		return false;
	}
	else if (TryApplyDamage(InDamage, InData))
	{
		OnDamageApplied.Broadcast(InDamage, InData);
		return true;
	}
	else
	{
		return false;
	}
}

bool UScWAttributeHealthComponent::ShouldIgnoreAnyAttackFrom(AController* InInstigator) const
{
	check(GetOwner());
	if (InInstigator == nullptr || InInstigator == GetOwner()->GetInstigatorController())
	{
		return false;
	}
	/*if (IDGameState->ShouldIgnoreDamageFromFriendlyBots() && !InInstigator->IsPlayerController())
	{
		if (ITeamInterface* PawnTeamInterface = Cast<ITeamInterface>(OwnerPawn))
		{
			if (ITeamInterface* InstigatorTeamInterface = Cast<ITeamInterface>(InInstigator))
			{
				if (PawnTeamInterface->GetTeamName() == InstigatorTeamInterface->GetTeamName())
				{
					return true;
				}
			}
		}
	}
	if (HasMatchingGameplayTag(FIDGameplayTags::State_Captured))
	{
		if (ITeamInterface* PawnTeamInterface = Cast<ITeamInterface>(OwnerPawn))
		{
			if (ITeamInterface* InstigatorTeamInterface = Cast<ITeamInterface>(InInstigator))
			{
				if (PawnTeamInterface->GetTeamName() == InstigatorTeamInterface->GetTeamName())
				{
					return true;
				}
			}
		}
	}*/
	return false;
}

bool UScWAttributeHealthComponent::TryIgnoreDamage(float& InOutAdjustedDamage, const FReceivedDamageData& InData)
{
	check(GetOwnerRole() == ROLE_Authority);

	bool bIsIgnored = false;

	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	check(OwnerASC);

	if (OwnerASC->HasMatchingGameplayTag(FScWCoreTags::State_IgnoreAnyDamage))
	{
		bIsIgnored = true;
	}
	else
	{
		/*if (HasMatchingGameplayTag(FIDGameplayTags::Effect_IgnoreAttack_Bullet) && InData.DamageTypeClass->IsChildOf(UIDDamageType_Bullet::StaticClass()))
		{
			bIsIgnored = true;
		}
		else if (HasMatchingGameplayTag(FIDGameplayTags::Effect_IgnoreAttack_Melee) && InData.DamageTypeClass->IsChildOf(UIDDamageType_Melee::StaticClass()))
		{
			bIsIgnored = true;
		}
		else */if (ShouldIgnoreAnyAttackFrom(InData.Instigator))
		{
			bIsIgnored = true;
		}
	}
	if (bIsIgnored)
	{
		//AccumulateIgnoredDamage(InOutAdjustedDamage);
		return true;
	}
	else
	{
		return false;
	}
}

bool UScWAttributeHealthComponent::TryBlockDamage(float& InOutAdjustedDamage, const FReceivedDamageData& InData)
{
	check(GetOwnerRole() == ROLE_Authority);

	bool bIsBlocked = false;

	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	check(OwnerASC);

	if (OwnerASC->HasMatchingGameplayTag(FScWCoreTags::State_BlockAnyDamage))
	{
		bIsBlocked = true;
	}
	else
	{
		// TODO: Move this to respective DamageType classes
		/*if (HasMatchingGameplayTag(FIDGameplayTags::Effect_BlockAttack_Bullet) && InData.DamageTypeClass->IsChildOf(UIDDamageType_Bullet::StaticClass()))
		{
			bIsBlocked = true;
		}
		else if (HasMatchingGameplayTag(FIDGameplayTags::Effect_BlockAttack_Melee) && InData.DamageTypeClass->IsChildOf(UIDDamageType_Melee::StaticClass()))
		{
			bIsBlocked = true;
		}*/
	}
	if (bIsBlocked)
	{
		//AccumulateBlockedDamage(InOutAdjustedDamage);
		return true;
	}
	else
	{
		return false;
	}
}

bool UScWAttributeHealthComponent::TryEvadeDamage(float& InOutAdjustedDamage, const FReceivedDamageData& InData)
{
	check(GetOwnerRole() == ROLE_Authority);

	bool bIsEvaded = false;

	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	check(OwnerASC);

	if (OwnerASC->HasMatchingGameplayTag(FScWCoreTags::State_EvadeAnyDamage))
	{
		bIsEvaded = true;
	}
	else
	{
		//const UScWAS_Health* AttributeSet = GetAttributeSet<UScWAS_Health>();
		//check(AttributeSet);

		float EvasionChance = 0.0f;

		/*if (InData.DamageType->IsA(UScWDT_Ranged::StaticClass()))
		{
			EvasionChance = AttributeSet->GetRangedDamageEvasionChance();
		}
		else if (InData.DamageType->IsA(UScWDT_Melee::StaticClass()))
		{
			EvasionChance = AttributeSet->GetMeleeDamageEvasionChance();
		}*/
		if (FMath::FRand() <= EvasionChance)
		{
			bIsEvaded = true;
		}
	}
	if (bIsEvaded)
	{
		//AccumulateEvadedDamage(InOutAdjustedDamage);
		return true;
	}
	else
	{
		return false;
	}
}

bool UScWAttributeHealthComponent::TryApplyDamage(float InDamage, const FReceivedDamageData& InData)
{
	check(GetOwnerRole() == ROLE_Authority);

	if (InDamage <= 0.0f)
	{
		return false;
	}
	AActor* OwnerActor = GetOwner();
	check(OwnerActor);

	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwnerActor);
	check(OwnerASC);

	LastAppliedDamage = InDamage;
	LastAppliedDamageData = InData;
	LastAppliedDamagePrevHealth = GetHealth();

	TSubclassOf<UGameplayEffect> ApplyDamageGameplayEffectClass = nullptr;

	if (InData.DamageType && InData.DamageType->ApplyDamageGameplayEffectClass)
	{
		ApplyDamageGameplayEffectClass = InData.DamageType->ApplyDamageGameplayEffectClass;
	}
	else
	{
		ApplyDamageGameplayEffectClass = UScWAssetManager::GetSubclass(UScWGameData::Get().DamageGameplayEffect_SetByCaller);
	}
	ensureReturn(ApplyDamageGameplayEffectClass, false);

	AccumulateAppliedDamage(LastAppliedDamage);

	FGameplayEffectContextHandle DamageEffectContext = OwnerASC->MakeEffectContext();
	DamageEffectContext.AddSourceObject(this);
	DamageEffectContext.AddInstigator(InData.Instigator, InData.Source);

	FGameplayEffectSpecHandle DamageEffectHandle = OwnerASC->MakeOutgoingSpec(ApplyDamageGameplayEffectClass, 1.0f, DamageEffectContext);
	DamageEffectHandle.Data->SetSetByCallerMagnitude(FScWCoreTags::SetByCaller_Magnitude, -LastAppliedDamage);

	if (InData.DamageType)
	{
		DamageEffectHandle.Data->SetSetByCallerMagnitude(FScWCoreTags::SetByCaller_Duration, InData.DamageType->ApplyDamageGameplayEffectDuration);
	}
	FActiveGameplayEffectHandle EffectHandle = OwnerASC->ApplyGameplayEffectSpecToSelf(*DamageEffectHandle.Data.Get());
	ensureReturn(EffectHandle.WasSuccessfullyApplied(), false);

	// Damage impact GameplayCue
	{
		FGameplayCueParameters ImpactCueParams = FGameplayCueParameters(OwnerASC->MakeEffectContext());
		ImpactCueParams.Instigator = InData.Instigator ? InData.Instigator->GetPawn() : nullptr;
		ImpactCueParams.EffectCauser = InData.Source;
		ImpactCueParams.Location = InData.HitResult.ImpactPoint;
		ImpactCueParams.Normal = InData.HitResult.ImpactNormal;
		ImpactCueParams.RawMagnitude = InDamage;
		ImpactCueParams.NormalizedMagnitude = FMath::Min(InDamage / GetMaxHealth(), 1.0f);
		OwnerASC->ExecuteGameplayCue(FScWCoreTags::GameplayCue_Damage_Impact, ImpactCueParams);
	}
	return true;
}
//~ End Damage

// TODO: Implement Analytics component and move this logic there
//#include "Character/ScWCharacter.h"

//~ Begin Death
void UScWAttributeHealthComponent::HandleDied()
{
	/*if (bSendDiedDesignEvent)
	{
		AScWCharacter* OwnerCharacter = GetOwner<AScWCharacter>();
		ensureIf(OwnerCharacter)
		{
			auto AdditionalFields = FGACustomFields();
			AdditionalFields.Set(TEXT("LastAppliedDamageData"), LastAppliedDamageData.ToAnalyticsString());
			OwnerCharacter->BP_SendDefaultDesignAnalyticsEvent(TEXT("Died"), AdditionalFields);
		}
	}*/
	if (APawn* OwnerPawn = GetOwner<APawn>())
	{
		OwnerPawn->DetachFromControllerPendingDestroy();
	}
	UAbilitySystemComponent* OwnerASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	const TSubclassOf<UGameplayEffect> DeadStateGE = UScWAssetManager::GetSubclass(UScWGameData::Get().DeadStateGameplayEffect);

	if (OwnerASC && DeadStateGE)
	{
		UScWAbilitySystemGlobals::TryApplyGameplayEffectByClass(OwnerASC, DeadStateGE);
	}
	else
	{
		ensure(false);
	}
	OnDied.Broadcast();

	if (bDestroyOwnerNextTickOnDeath)
	{
		AActor* Owner = GetOwner();
		ensureReturn(Owner);
		Owner->GetWorldTimerManager().SetTimerForNextTick(Owner, &AActor::K2_DestroyActor);
	}
	BP_HandlePostDeathBehavior();
}

void UScWAttributeHealthComponent::BP_HandlePostDeathBehavior_Implementation()
{

}
//~ End Death
