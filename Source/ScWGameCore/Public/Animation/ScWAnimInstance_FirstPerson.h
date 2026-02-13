// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Animation/ScWAnimInstance_Base.h"

#include "ScWAnimInstance_FirstPerson.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI, Abstract, meta = (DisplayName = "[ScW] Anim Instance (First Person)"))
class UScWAnimInstance_FirstPerson : public UScWAnimInstance_Base
{
	GENERATED_BODY()
	
public:

	UScWAnimInstance_FirstPerson();
	
//~ Begin Static
public:
	MODULE_API virtual void ResetToDefaultStaticAnimationData() override { SetCurrentStaticAnimationData(DefaultStaticAnimationData); }
	MODULE_API void SetCurrentStaticAnimationData(const FScWFirstPersonStaticAnimationData& InStaticAnimationData);
	MODULE_API void SetDefaultStaticAnimationData(const FScWFirstPersonStaticAnimationData& InStaticAnimationData);
protected:

	UPROPERTY(Category = "Static", EditAnywhere, BlueprintReadOnly)
	FScWFirstPersonStaticAnimationData CurrentStaticAnimationData;

	UPROPERTY(Category = "Static", EditAnywhere, BlueprintReadOnly)
	FScWFirstPersonStaticAnimationData DefaultStaticAnimationData;
//~ End Static
};

#undef MODULE_API
