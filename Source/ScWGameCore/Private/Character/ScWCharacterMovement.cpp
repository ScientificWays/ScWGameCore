// Scientific Ways

#include "Character/ScWCharacterMovement.h"

#include "Tags/ScWCoreTags.h"
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

	WalkSpeedChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetWalkSpeedAttribute()).AddUObject(this, &ThisClass::OnWalkSpeedAttributeChanged);
	WalkSpeedMulCrouchedChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetWalkSpeedMulCrouchedAttribute()).AddUObject(this, &ThisClass::OnWalkSpeedMulCrouchedAttributeChanged);
	AccelerationChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetAccelerationAttribute()).AddUObject(this, &ThisClass::OnAccelerationAttributeChanged);
	BrakingDecelerationWalkingChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetBrakingDecelerationWalkingAttribute()).AddUObject(this, &ThisClass::OnBrakingDecelerationWalkingAttributeChanged);
	GravityScaleChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetGravityScaleAttribute()).AddUObject(this, &ThisClass::OnGravityScaleAttributeChanged);
	AirControlChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetAirControlAttribute()).AddUObject(this, &ThisClass::OnAirControlAttributeChanged);
	MassChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetMassAttribute()).AddUObject(this, &ThisClass::OnMassAttributeChanged);
	RotationRateYawChangedDelegateHandle = InInitASC->GetGameplayAttributeValueChangeDelegate(UScWAS_CharacterMovement::GetRotationRateYawAttribute()).AddUObject(this, &ThisClass::OnRotationRateYawAttributeChanged);

	InInitASC->RegisterGameplayTagEvent(FScWCoreTags::Character_MovementMode, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnMovementModeTagNumChanged);
	UpdateCharacterMovementModeFromTags();

	InInitASC->RegisterGameplayTagEvent(FScWCoreTags::Character_MovementFlag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnMovementFlagTagNumChanged);
	UpdateCharacterMovementFlagsFromTags();
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
void UScWCharacterMovement::OnWalkSpeedAttributeChanged(const FOnAttributeChangeData& InData)
{
	MaxWalkSpeed = InData.NewValue;
	MaxWalkSpeedCrouched = MaxWalkSpeed * InData.NewValue; // Should be as in OnWalkSpeedMulCrouchedAttributeChanged
}

void UScWCharacterMovement::OnWalkSpeedMulCrouchedAttributeChanged(const FOnAttributeChangeData& InData)
{
	MaxWalkSpeedCrouched = MaxWalkSpeed * InData.NewValue;
}

void UScWCharacterMovement::OnAccelerationAttributeChanged(const FOnAttributeChangeData& InData)
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

void UScWCharacterMovement::OnRotationRateYawAttributeChanged(const FOnAttributeChangeData& InData)
{
	RotationRate.Yaw = InData.NewValue;
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

	if (InitASC->HasMatchingGameplayTag(FScWCoreTags::Character_MovementMode_None))
	{
		SetMovementMode(EMovementMode::MOVE_None);
	}
	else if (InitASC->HasMatchingGameplayTag(FScWCoreTags::Character_MovementMode_Walking))
	{
		if (InitASC->HasMatchingGameplayTag(FScWCoreTags::Character_MovementMode_Walking_Nav))
		{
			SetMovementMode(EMovementMode::MOVE_NavWalking);
		}
		else
		{
			SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}
	else if (InitASC->HasMatchingGameplayTag(FScWCoreTags::Character_MovementMode_Falling))
	{
		SetMovementMode(EMovementMode::MOVE_Falling);
	}
	else if (InitASC->HasMatchingGameplayTag(FScWCoreTags::Character_MovementMode_Swimming))
	{
		SetMovementMode(EMovementMode::MOVE_Swimming);
	}
	else if (InitASC->HasMatchingGameplayTag(FScWCoreTags::Character_MovementMode_Flying))
	{
		SetMovementMode(EMovementMode::MOVE_Flying);
	}
	else
	{
		SetDefaultMovementMode();
	}
}

void UScWCharacterMovement::OnMovementFlagTagNumChanged(const FGameplayTag InCallbackTag, int32 InNewNum)
{
	UpdateCharacterMovementFlagsFromTags();
}

void UScWCharacterMovement::UpdateCharacterMovementFlagsFromTags()
{
	UScWAbilitySystemComponent* InitASC = GetInitASC();
	ensureReturn(InitASC);

	bOrientRotationToMovement = (InitASC->HasMatchingGameplayTag(FScWCoreTags::Character_MovementFlag_OrientRotationToMovement)
			&& !InitASC->HasMatchingGameplayTag(FScWCoreTags::Character_MovementFlag_BlockOrientRotationToMovement));
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
