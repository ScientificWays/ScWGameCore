// Scientific Ways

#include "Animation/ScWAnimInstance_Equipment.h"

UScWAnimInstance_Equipment::UScWAnimInstance_Equipment()
{

}

//~ Begin Static
void UScWAnimInstance_Equipment::SetCurrentStaticAnimationData(const FScWEquipmentStaticAnimationData& InStaticAnimationData)
{
	CurrentStaticAnimationData = InStaticAnimationData;
	BP_OnCurrentStaticAnimationDataChanged();
}
//~ End Static
