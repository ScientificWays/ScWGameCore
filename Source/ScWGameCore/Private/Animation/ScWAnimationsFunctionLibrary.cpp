// Scientific Ways

#include "Animation/ScWAnimationsFunctionLibrary.h"

#include "Animation/ScWTypes_Animation.h"
//#include "Animation/ScWAnimInstance_Equipment.h"
#include "Animation/ScWAnimInstance_FirstPerson.h"
#include "Animation/ScWAnimInstance_ThirdPerson.h"

//#include "Character/ScWCharacter.h"
#include "Character/ScWCharacterMesh_FirstPerson.h"
#include "Character/ScWCharacterMesh_ThirdPerson.h"

const FName UScWAnimationsFunctionLibrary::MontageDefaultGroupName = FName(TEXT("DefaultGroup"));

//~ Begin Anim Instances
UScWAnimInstance_FirstPerson* UScWAnimationsFunctionLibrary::GetCharacterFirstPersonAnimInstance(ACharacter* InCharacter, const bool bInChecked)
{
	if (UScWCharacterMesh_FirstPerson* FirstPersonMesh = InCharacter->FindComponentByClass<UScWCharacterMesh_FirstPerson>())
	{
		if (UScWAnimInstance_FirstPerson* AnimInstance = Cast<UScWAnimInstance_FirstPerson>(FirstPersonMesh->GetAnimInstance()))
		{
			return AnimInstance;
		}
	}
	ensure(!bInChecked);
	return nullptr;
}

UScWAnimInstance_ThirdPerson* UScWAnimationsFunctionLibrary::GetCharacterThirdPersonAnimInstance(ACharacter* InCharacter, const bool bInChecked)
{
	if (UScWCharacterMesh_ThirdPerson* ThirdPersonMesh = InCharacter->FindComponentByClass<UScWCharacterMesh_ThirdPerson>())
	{
		if (UScWAnimInstance_ThirdPerson* AnimInstance = Cast<UScWAnimInstance_ThirdPerson>(ThirdPersonMesh->GetAnimInstance()))
		{
			return AnimInstance;
		}
	}
	ensure(!bInChecked);
	return nullptr;
}
//~ End Anim Instances

//~ Begin Montages
float UScWAnimationsFunctionLibrary::GetMontagePlayLength(const UAnimMontage* InMontage, float InTimeMul, float InFallbackValue)
{
	ensureReturn(InMontage, FMath::Max(0.0f, InFallbackValue));
	return FMath::Max(InMontage->GetPlayLength() * InTimeMul, InFallbackValue);
}

float UScWAnimationsFunctionLibrary::GetMontageSectionLengthByIndex(const UAnimMontage* InMontage, int32 InIndex, float InTimeMul, float InFallbackValue)
{
	ensureReturn(InMontage, FMath::Max(0.0f, InFallbackValue));
	return (!InMontage->IsValidSectionIndex(InIndex) && InFallbackValue >= 0.0f)
		? (InFallbackValue)
		: (InMontage->GetSectionLength(InIndex) * InTimeMul);
}

float UScWAnimationsFunctionLibrary::GetMontageSectionLengthByName(const UAnimMontage* InMontage, const FName& InName, float InTimeMul, float InFallbackValue)
{
	ensureReturn(InMontage, FMath::Max(0.0f, InFallbackValue));
	return UScWAnimationsFunctionLibrary::GetMontageSectionLengthByIndex(InMontage, InMontage->GetSectionIndex(InName));
}

float UScWAnimationsFunctionLibrary::GetMontagePlayLengthFromData(const FScWCharacterMontageData& InCharacterMontageData, float InFallbackValue)
{
	return GetMontagePlayLength(InCharacterMontageData.GetRelevantTimingMontage(), InCharacterMontageData.TimeMul, InFallbackValue);
}

float UScWAnimationsFunctionLibrary::GetMontageSectionLengthByIndexFromData(const FScWCharacterMontageData& InCharacterMontageData, int32 InIndex, float InFallbackValue)
{
	return GetMontageSectionLengthByIndex(InCharacterMontageData.GetRelevantTimingMontage(), InIndex, InCharacterMontageData.TimeMul, InFallbackValue);
}

float UScWAnimationsFunctionLibrary::GetMontageSectionLengthByNameFromData(const FScWCharacterMontageData& InCharacterMontageData, const FName& InName, float InFallbackValue)
{
	return GetMontageSectionLengthByName(InCharacterMontageData.GetRelevantTimingMontage(), InName, InCharacterMontageData.TimeMul, InFallbackValue);
}

float UScWAnimationsFunctionLibrary::PlayCharacterMontagesFromData(ACharacter* InCharacter, const FScWCharacterMontageData& InCharacterMontageData, const bool bInStopAllMontages)
{
	ensureReturn(InCharacter, 0.0f);

	float PlayRateInv = 1.0f / FMath::Max(InCharacterMontageData.TimeMul, FLT_EPSILON);
	float OutMaxDuration = 0.0f;

	if (InCharacterMontageData.FirstPersonMontage)
	{
		if (UScWAnimInstance_FirstPerson* FirstPersonAnimInstance = GetCharacterFirstPersonAnimInstance(InCharacter))
		{
			OutMaxDuration = FMath::Max(FirstPersonAnimInstance->Montage_Play(InCharacterMontageData.FirstPersonMontage, PlayRateInv, EMontagePlayReturnType::Duration, 0.0f, bInStopAllMontages), 0.0f);
		}
	}
	if (InCharacterMontageData.ThirdPersonMontage)
	{
		if (UScWAnimInstance_ThirdPerson* ThirdPersonAnimInstance = GetCharacterThirdPersonAnimInstance(InCharacter))
		{
			OutMaxDuration = FMath::Max(ThirdPersonAnimInstance->Montage_Play(InCharacterMontageData.ThirdPersonMontage, PlayRateInv, EMontagePlayReturnType::Duration, 0.0f, bInStopAllMontages), 0.0f);
		}
	}
	if (InCharacterMontageData.ActiveEquipmentMontage)
	{
		/*if (UScWAnimInstance_Equipment* EquipmentAnimInstance = InCharacter->GetScWEquipmentAnimInstance())
		{
			OutMaxDuration = FMath::Max(EquipmentAnimInstance->Montage_Play(InCharacterMontageData.ActiveEquipmentMontage, PlayRateInv, EMontagePlayReturnType::Duration, 0.0f, bInStopAllMontages), 0.0f);
		}*/
	}
	return OutMaxDuration;
}
//~ End Montages

//~ Begin StaticData
void UScWAnimationsFunctionLibrary::SetCharacterDefaultStaticAnimationData(ACharacter* InCharacter, const FScWFirstPersonStaticAnimationData& InFirstPersonStaticAnimationData, const FScWThirdPersonStaticAnimationData& InThirdPersonStaticAnimationData, const bool bInApplyDefaultStaticAnimationData)
{
	if (UScWAnimInstance_FirstPerson* FistPersonAnimInstance = GetCharacterFirstPersonAnimInstance(InCharacter))
	{
		FistPersonAnimInstance->Montage_StopGroupByName(0.2f, MontageDefaultGroupName);
		FistPersonAnimInstance->SetDefaultStaticAnimationData(InFirstPersonStaticAnimationData);

		if (bInApplyDefaultStaticAnimationData)
		{
			FistPersonAnimInstance->ResetToDefaultStaticAnimationData();
		}
	}
	if (UScWAnimInstance_ThirdPerson* ThirdPersonAnimInstance = GetCharacterThirdPersonAnimInstance(InCharacter))
	{
		ThirdPersonAnimInstance->Montage_StopGroupByName(0.2f, MontageDefaultGroupName);
		ThirdPersonAnimInstance->SetDefaultStaticAnimationData(InThirdPersonStaticAnimationData);

		if (bInApplyDefaultStaticAnimationData)
		{
			ThirdPersonAnimInstance->ResetToDefaultStaticAnimationData();
		}
	}
}

void UScWAnimationsFunctionLibrary::ToggleCharacterHolsterStaticAnimationData(ACharacter* InCharacter, const bool bInUseHolster, const float InBlendTime, const bool bInFirstPerson, const bool bInThirdPerson)
{
	if (InCharacter == nullptr)
	{
		return;
	}
	if (bInFirstPerson)
	{
		if (UScWAnimInstance_FirstPerson* FirstPersonAnimInstance = GetCharacterFirstPersonAnimInstance(InCharacter))
		{
			FirstPersonAnimInstance->SetUseHolsterStaticAnimationData(bInUseHolster, InBlendTime);
		}
	}
	if (bInThirdPerson)
	{
		if (UScWAnimInstance_ThirdPerson* ThirdPersonAnimInstance = GetCharacterThirdPersonAnimInstance(InCharacter))
		{
			ThirdPersonAnimInstance->SetUseHolsterStaticAnimationData(bInUseHolster, InBlendTime);
		}
	}
	/*if (UScWAnimInstance_Equipment* EquipmentAnimInstance = InCharacter->GetScWEquipmentAnimInstance())
	{
		EquipmentAnimInstance->SetUseHolsterStaticAnimationData(bInUseHolster, InBlendTime);
	}*/
}

void UScWAnimationsFunctionLibrary::ToggleCharacterAlternativeBasePose(ACharacter* InCharacter, const bool bInUseAlternative, const float InBlendTime, const bool bInFirstPerson, const bool bInThirdPerson)
{
	if (InCharacter == nullptr)
	{
		return;
	}
	if (bInFirstPerson)
	{
		if (UScWAnimInstance_FirstPerson* FirstPersonAnimInstance = GetCharacterFirstPersonAnimInstance(InCharacter))
		{
			FirstPersonAnimInstance->SetUseAlternativeBasePose(bInUseAlternative, InBlendTime);
		}
	}
	if (bInThirdPerson)
	{
		if (UScWAnimInstance_ThirdPerson* ThirdPersonAnimInstance = GetCharacterThirdPersonAnimInstance(InCharacter))
		{
			ThirdPersonAnimInstance->SetUseAlternativeBasePose(bInUseAlternative, InBlendTime);
		}
	}
	/*if (UScWAnimInstance_Equipment* EquipmentAnimInstance = InCharacter->GetScWEquipmentAnimInstance())
	{
		EquipmentAnimInstance->SetUseAlternativeBasePose(bInUseAlternative, InBlendTime);
	}*/
}

void UScWAnimationsFunctionLibrary::ToggleCharacterEnableIdleAnimation(ACharacter* InCharacter, const bool bInEnable, const bool bInFirstPerson, const bool bInThirdPerson)
{
	if (InCharacter == nullptr)
	{
		return;
	}
	if (bInFirstPerson)
	{
		if (UScWAnimInstance_FirstPerson* FirstPersonAnimInstance = GetCharacterFirstPersonAnimInstance(InCharacter))
		{
			FirstPersonAnimInstance->SetEnableIdleAnimation(bInEnable);
		}
	}
	if (bInThirdPerson)
	{
		if (UScWAnimInstance_ThirdPerson* ThirdPersonAnimInstance = GetCharacterThirdPersonAnimInstance(InCharacter))
		{
			ThirdPersonAnimInstance->SetEnableIdleAnimation(bInEnable);
		}
	}
	/*if (UScWAnimInstance_Equipment* EquipmentAnimInstance = InCharacter->GetScWEquipmentAnimInstance())
	{
		EquipmentAnimInstance->SetEnableIdleAnimation(bInEnable);
	}*/
}
//~ End StaticData
