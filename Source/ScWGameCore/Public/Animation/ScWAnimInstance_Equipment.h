// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Animation/ScWAnimInstance_Base.h"

#include "ScWAnimInstance_Equipment.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI, Abstract, meta = (DisplayName = "[ScW] Anim Instance (Equipment)"))
class UScWAnimInstance_Equipment : public UScWAnimInstance_Base
{
	GENERATED_BODY()
	
public:

	UScWAnimInstance_Equipment();
	
//~ Begin Static
public:
	MODULE_API virtual void ResetToDefaultStaticAnimationData() override { SetCurrentStaticAnimationData(DefaultStaticAnimationData); }
	MODULE_API void SetCurrentStaticAnimationData(const FScWEquipmentStaticAnimationData& InStaticAnimationData);
protected:

	UPROPERTY(Category = "Static", BlueprintReadOnly, EditDefaultsOnly)
	FScWEquipmentStaticAnimationData CurrentStaticAnimationData;

	UPROPERTY(Category = "Static", BlueprintReadOnly, EditDefaultsOnly)
	FScWEquipmentStaticAnimationData DefaultStaticAnimationData;
//~ End Static
};

#undef MODULE_API
