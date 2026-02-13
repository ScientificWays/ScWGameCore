// Scientific Ways

#include "Animation/ScWTypes_Animation.h"

const FScWFirstPersonStaticAnimationData FScWFirstPersonStaticAnimationData::None = FScWFirstPersonStaticAnimationData();
const FScWThirdPersonStaticAnimationData FScWThirdPersonStaticAnimationData::None = FScWThirdPersonStaticAnimationData();
const FScWEquipmentStaticAnimationData FScWEquipmentStaticAnimationData::None = FScWEquipmentStaticAnimationData();

UAnimMontage* FScWCharacterMontageData::GetRelevantTimingMontage() const
{
	switch (TimingMontageType)
	{
		case EScWTimingMontageType::FirstPerson:
		{
			return FirstPersonMontage;
		}
		case EScWTimingMontageType::ThirdPerson:
		{
			return ThirdPersonMontage;
		}
		case EScWTimingMontageType::ActiveEquipment:
		{
			return ActiveEquipmentMontage;
		}
	}
	ensureReturn(false, nullptr);
}
