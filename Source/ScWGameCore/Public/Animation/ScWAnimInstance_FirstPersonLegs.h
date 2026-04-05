// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Animation/ScWAnimInstance_Base.h"

#include "ScWAnimInstance_FirstPersonLegs.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *	Animation instance for the first-person leg mesh. Tracks incapacitated state
 *	to drive leg-specific animations independently from the upper body.
 */
UCLASS(MinimalAPI, Abstract)
class UScWAnimInstance_FirstPersonLegs : public UScWAnimInstance_Base
{
	GENERATED_BODY()
	
public:

	UScWAnimInstance_FirstPersonLegs();

//~ Begin Static
public:

	UFUNCTION(Category = "Static", BlueprintCallable)
	void SetIncapped(const bool InValue);
	
	UFUNCTION(Category = "Static", BlueprintImplementableEvent, meta = (DisplayName = "OnUpdateIncapped"))
	void BP_OnUpdateIncapped();

protected:

	UPROPERTY(Category = "Static", EditAnywhere, BlueprintReadOnly)
	bool bIncapped;
//~ End Static
};

#undef MODULE_API
