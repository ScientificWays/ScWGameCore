// Scientific Ways

#include "Character/ScWCharacterMovement.h"

#include "AbilitySystem/ScWCoreTags.h"
#include "AbilitySystem/ScWAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/ScWAS_CharacterMovement.h"

#include "Damage/ScWDamageType.h"
#include "Damage/ScWAttributeHealthComponent.h"

UScWCharacterMovement::UScWCharacterMovement()
{
	//bOrientRotationToMovement = true;
	//RotationRate = FRotator(0.0, 720.0, 0.0);
}

//~ Begin Initialize
void UScWCharacterMovement::BeginPlay()
{
	Super::BeginPlay();

	AActor* OwnerActor = GetOwner();
	ensureReturn(OwnerActor);

	if (UScWAttributeHealthComponent* HealthComponent = OwnerActor->GetComponentByClass<UScWAttributeHealthComponent>())
	{
		HealthComponent->OnDamageApplied.AddDynamic(this, &ThisClass::HandleDamageApplied);
		HealthComponent->OnDied.AddDynamic(this, &ThisClass::HandleDied);
	}
}

void UScWCharacterMovement::InitFromASC(UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) // IScWASC_InitInterface
{
	ensureReturn(InInitASC);
	//ensureReturn(InOwnerActor);
	//ensureReturn(InAvatarActor);

	MaxWalkSpeedChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetMaxWalkSpeedAttribute()).AddUObject(this, &ThisClass::OnMaxWalkSpeedAttributeChanged);
	MaxWalkSpeedCrouchedChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetMaxWalkSpeedCrouchedAttribute()).AddUObject(this, &ThisClass::OnMaxWalkSpeedCrouchedAttributeChanged);
	MaxAccelerationChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetMaxAccelerationAttribute()).AddUObject(this, &ThisClass::OnMaxAccelerationAttributeChanged);
	BrakingDecelerationWalkingChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetBrakingDecelerationWalkingAttribute()).AddUObject(this, &ThisClass::OnBrakingDecelerationWalkingAttributeChanged);
	GravityScaleChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetGravityScaleAttribute()).AddUObject(this, &ThisClass::OnGravityScaleAttributeChanged);
	AirControlChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetAirControlAttribute()).AddUObject(this, &ThisClass::OnAirControlAttributeChanged);
	MassChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetMassAttribute()).AddUObject(this, &ThisClass::OnMassAttributeChanged);

	InInitASC->RegisterGameplayTagEvent(FScWCoreTags::MovementMode, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnMovementModeTagNumChanged);
	UpdateCharacterMovementModeFromTags();
}
//~ End Initialize

//~ Begin Rotation
void UScWCharacterMovement::ApplyRootMotionToVelocity(float InDeltaTime) // UCharacterMovementComponent
{
	//FVector OldVelocity = Velocity;

	Super::ApplyRootMotionToVelocity(InDeltaTime);

	LastRootMotionVelocity = Velocity/*- OldVelocity*/;
}

void UScWCharacterMovement::PhysicsRotation(float InDeltaTime) // UCharacterMovementComponent
{
	/*if (PhysicsRotationBlockSourceSet.IsEmpty())
	{
		Super::PhysicsRotation(InDeltaTime);
	}
	else
	{
		return;
	}*/
	Super::PhysicsRotation(InDeltaTime);
}

FRotator UScWCharacterMovement::ComputeOrientToMovementRotation(const FRotator& InCurrentRotation, float InDeltaTime, FRotator& InDeltaRotation) const
{
	if (bOrientRotationToRootMotionMovement && CurrentRootMotion.HasVelocity())
	{
		if (LastRootMotionVelocity.SizeSquared() > UE_KINDA_SMALL_NUMBER)
		{
			return LastRootMotionVelocity.GetSafeNormal().Rotation();
		}
	}
	// Default behavior if there is no root motion velocity.
	return Super::ComputeOrientToMovementRotation(InCurrentRotation, InDeltaTime, InDeltaRotation);
}
//~ End Rotation

//~ Begin Attributes
void UScWCharacterMovement::OnMaxWalkSpeedAttributeChanged(const FOnAttributeChangeData& InData)
{
	MaxWalkSpeed = InData.NewValue;
}

void UScWCharacterMovement::OnMaxWalkSpeedCrouchedAttributeChanged(const FOnAttributeChangeData& InData)
{
	MaxWalkSpeedCrouched = InData.NewValue;
}

void UScWCharacterMovement::OnMaxAccelerationAttributeChanged(const FOnAttributeChangeData& InData)
{
	MaxAcceleration = InData.NewValue;
}

void UScWCharacterMovement::OnBrakingDecelerationWalkingAttributeChanged(const FOnAttributeChangeData& InData)
{
	BrakingDecelerationWalking = InData.NewValue;
}

void UScWCharacterMovement::OnGravityScaleAttributeChanged(const FOnAttributeChangeData& InData)
{
	GravityScale = InData.NewValue;
}

void UScWCharacterMovement::OnAirControlAttributeChanged(const FOnAttributeChangeData& InData)
{
	AirControl = InData.NewValue;
}

void UScWCharacterMovement::OnMassAttributeChanged(const FOnAttributeChangeData& InData)
{
	Mass = InData.NewValue;
}
//~ End Attributes

//~ Begin Tags
void UScWCharacterMovement::OnMovementModeTagNumChanged(const FGameplayTag InCallbackTag, int32 InNewNum)
{
	UpdateCharacterMovementModeFromTags();
}

void UScWCharacterMovement::UpdateCharacterMovementModeFromTags()
{
	UScWAbilitySystemComponent* InitASC = GetInitASC();
	ensureReturn(InitASC);

	if (InitASC->HasMatchingGameplayTag(FScWCoreTags::MovementMode_None))
	{
		SetMovementMode(EMovementMode::MOVE_None);
	}
	else if (InitASC->HasMatchingGameplayTag(FScWCoreTags::MovementMode_Walking))
	{
		SetMovementMode(EMovementMode::MOVE_Walking);
	}
	else if (InitASC->HasMatchingGameplayTag(FScWCoreTags::MovementMode_NavWalking))
	{
		SetMovementMode(EMovementMode::MOVE_NavWalking);
	}
	else if (InitASC->HasMatchingGameplayTag(FScWCoreTags::MovementMode_Falling))
	{
		SetMovementMode(EMovementMode::MOVE_Falling);
	}
	else if (InitASC->HasMatchingGameplayTag(FScWCoreTags::MovementMode_Swimming))
	{
		SetMovementMode(EMovementMode::MOVE_Swimming);
	}
	else if (InitASC->HasMatchingGameplayTag(FScWCoreTags::MovementMode_Flying))
	{
		SetMovementMode(EMovementMode::MOVE_Flying);
	}
	else
	{
		SetDefaultMovementMode();
	}
}
//~ End Tags

//~ Begin Damage
void UScWCharacterMovement::HandleDamageApplied(float InDamage, const FReceivedDamageData& InData)
{
	ensureReturn(InData.DamageType);
	InData.DamageType->ApplyImpactImpulseToCharacterMovement(this, InData.HitResult);
}

void UScWCharacterMovement::HandleDied()
{
	DisableMovement();
}
//~ End Damage
