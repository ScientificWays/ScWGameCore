// Scientific Ways

#include "AbilitySystem/Attributes/ScWAS_CharacterMovement.h"

UScWAS_CharacterMovement::UScWAS_CharacterMovement()
{
	InitWalkSpeed(600.0f);
	InitWalkSpeedMax(3000.0f);
	InitWalkSpeedMulCrouched(0.5f);

	InitAcceleration(1800.0f);
	InitBrakingDecelerationWalking(2400.0f);

	InitGravityScale(1.0f);
	InitAirControl(0.2f);
	InitMass(80.0f);

	InitRotationRateYaw(720.0f);
}

//~ Begin Replication
void UScWAS_CharacterMovement::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const // UObject
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, WalkSpeed);
	DOREPLIFETIME(ThisClass, WalkSpeedMax);
	DOREPLIFETIME(ThisClass, WalkSpeedMulCrouched);

	DOREPLIFETIME(ThisClass, Acceleration);
	DOREPLIFETIME(ThisClass, BrakingDecelerationWalking);

	DOREPLIFETIME(ThisClass, GravityScale);
	DOREPLIFETIME(ThisClass, AirControl);
	DOREPLIFETIME(ThisClass, Mass);

	DOREPLIFETIME(ThisClass, RotationRateYaw);
}
//~ End Replication

//~ Begin Change
void UScWAS_CharacterMovement::PreAttributeChange(const FGameplayAttribute& InAttribute, float& InOutNewValue) // UAttributeSet
{
	if (InAttribute == GetAccelerationAttribute())
	{
		InOutNewValue = FMath::Max(InOutNewValue, 0.0f);
	}
	if (InAttribute == GetWalkSpeedAttribute() || InAttribute == GetWalkSpeedMulCrouchedAttribute())
	{
		InOutNewValue = FMath::Clamp(InOutNewValue, 0.0f, GetWalkSpeedMax());
	}
	else
	{
		Super::PreAttributeChange(InAttribute, InOutNewValue);
	}
}

void UScWAS_CharacterMovement::PostAttributeChange(const FGameplayAttribute& InAttribute, float InPrevValue, float InNewValue) // UAttributeSet
{
	Super::PostAttributeChange(InAttribute, InPrevValue, InNewValue);

	if (InAttribute == GetWalkSpeedMaxAttribute())
	{
		SetWalkSpeed(FMath::Min(GetWalkSpeed(), InNewValue));
		SetWalkSpeedMulCrouched(FMath::Min(GetWalkSpeedMulCrouched(), InNewValue));
	}
}
//~ End Change

//~ Begin Replication
void UScWAS_CharacterMovement::OnRep_WalkSpeed(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, WalkSpeed, InPrevValue);
}

void UScWAS_CharacterMovement::OnRep_WalkSpeedMax(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, WalkSpeedMax, InPrevValue);
}

void UScWAS_CharacterMovement::OnRep_WalkSpeedMulCrouched(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, WalkSpeedMulCrouched, InPrevValue);
}

void UScWAS_CharacterMovement::OnRep_Acceleration(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Acceleration, InPrevValue);
}

void UScWAS_CharacterMovement::OnRep_BrakingDecelerationWalking(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, BrakingDecelerationWalking, InPrevValue);
}

void UScWAS_CharacterMovement::OnRep_GravityScale(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, GravityScale, InPrevValue);
}

void UScWAS_CharacterMovement::OnRep_AirControl(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, AirControl, InPrevValue);
}

void UScWAS_CharacterMovement::OnRep_Mass(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mass, InPrevValue);
}

void UScWAS_CharacterMovement::OnRep_RotationRateYaw(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, RotationRateYaw, InPrevValue);
}
//~ End Replication