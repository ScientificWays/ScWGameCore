// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Animation/ScWAnimInstance_Base.h"

#include "ScWAnimInstance_ThirdPerson.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 * 
 */
UCLASS(MinimalAPI, Abstract, meta = (DisplayName = "[ScW] Anim Instance (Third Person)"))
class UScWAnimInstance_ThirdPerson : public UScWAnimInstance_Base
{
	GENERATED_BODY()
	
public:

	UScWAnimInstance_ThirdPerson();
	
//~ Begin Static
public:
	MODULE_API virtual void ResetToDefaultStaticAnimationData() override { SetCurrentStaticAnimationData(DefaultStaticAnimationData); }
	MODULE_API void SetCurrentStaticAnimationData(const FScWThirdPersonStaticAnimationData& InStaticAnimationData);
	MODULE_API void SetDefaultStaticAnimationData(const FScWThirdPersonStaticAnimationData& InStaticAnimationData);
	//void SetHideUpperBody(const bool bHide);
	
	//UFUNCTION(Category = "Static", BlueprintImplementableEvent, meta = (DisplayName = "OnUpdateHideUpperBody"))
	//void BP_OnUpdateHideUpperBody();
	
protected:

	UPROPERTY(Category = "Static", EditAnywhere, BlueprintReadOnly)
	FScWThirdPersonStaticAnimationData CurrentStaticAnimationData;

	UPROPERTY(Category = "Static", EditAnywhere, BlueprintReadOnly)
	FScWThirdPersonStaticAnimationData DefaultStaticAnimationData;
	
	//UPROPERTY(Category = "Static", EditAnywhere, BlueprintReadOnly)
	//bool bHideUpperBody;
//~ End Static
};

#undef MODULE_API
