// Scientific Ways

#include "AbilitySystem/Attributes/ScWAS_ThirdPersonCamera.h"

UScWAS_ThirdPersonCamera::UScWAS_ThirdPersonCamera()
{
	InitRotationPitch(-50.0f);
	InitRotationYaw(15.0f);
	InitRotationRoll(0.0f);

	InitSpringArmLength(2000.0f);

	InitFieldOfView(90.0f);
}

//~ Begin Replication
void UScWAS_ThirdPersonCamera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const // UObject
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, RotationPitch);
	DOREPLIFETIME(ThisClass, RotationYaw);
	DOREPLIFETIME(ThisClass, RotationRoll);

	DOREPLIFETIME(ThisClass, SpringArmLength);

	DOREPLIFETIME(ThisClass, FieldOfView);
}
//~ End Replication

//~ Begin Change
void UScWAS_ThirdPersonCamera::PreAttributeChange(const FGameplayAttribute& InAttribute, float& InOutNewValue) // UAttributeSet
{
	if (InAttribute == GetSpringArmLengthAttribute() || InAttribute == GetFieldOfViewAttribute())
	{
		InOutNewValue = FMath::Max(InOutNewValue, 0.0f);
	}
	else
	{
		
	}
}

void UScWAS_ThirdPersonCamera::PostAttributeChange(const FGameplayAttribute& InAttribute, float InPrevValue, float InNewValue) // UAttributeSet
{
	Super::PostAttributeChange(InAttribute, InPrevValue, InNewValue);

	
}
//~ End Change

//~ Begin Replication
void UScWAS_ThirdPersonCamera::OnRep_RotationPitch(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, RotationPitch, InPrevValue);
}

void UScWAS_ThirdPersonCamera::OnRep_RotationYaw(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, RotationYaw, InPrevValue);
}

void UScWAS_ThirdPersonCamera::OnRep_RotationRoll(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, RotationRoll, InPrevValue);
}

void UScWAS_ThirdPersonCamera::OnRep_SpringArmLength(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, SpringArmLength, InPrevValue);
}

void UScWAS_ThirdPersonCamera::OnRep_FieldOfView(const FGameplayAttributeData& InPrevValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, FieldOfView, InPrevValue);
}

//~ End Replication
