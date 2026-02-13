// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Abilities/Tasks/AbilityTask.h"

#include "ScWAT_WaitDelay.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *	Same as default AbilityTask_WaitDelay, but checks if provided time less or equals zero, and if it is, finishes immediately
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] AT_WaitDelay"))
class UScWAT_WaitDelay : public UAbilityTask
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FGenericGameplayTaskDelegate OnFinish;

//~ Begin Initialize
public:

	UFUNCTION(BlueprintCallable, Category = "Ability | Tasks", meta = (DisplayName = "[ScW] Wait delay or finish Immediately", HidePin = "InOwningAbility", DefaultToSelf = "InOwningAbility", BlueprintInternalUseOnly = "true"))
	static MODULE_API UScWAT_WaitDelay* WaitDelayOrFinishImmediately(UGameplayAbility* InOwningAbility, float InTime);

	UFUNCTION(BlueprintCallable, Category = "Ability | Tasks", meta = (DisplayName = "[ScW] Wait delay or finish NextTick", HidePin = "InOwningAbility", DefaultToSelf = "InOwningAbility", BlueprintInternalUseOnly = "true"))
	static MODULE_API UScWAT_WaitDelay* WaitDelayOrFinishNextTick(UGameplayAbility* InOwningAbility, float InTime);

protected:
	MODULE_API virtual void Activate() override; // UGameplayTask
	MODULE_API virtual void OnDestroy(bool bInAbilityIsEnding) override; // UGameplayTask
//~ End Initialize
	
//~ Begin Debug
public:
	MODULE_API virtual FString GetDebugString() const override; // UGameplayTask
//~ End Debug

//~ Begin Callbacks
protected:
	MODULE_API void OnTimeFinish();
//~ End Callbacks

//~ Begin Data
protected:
	bool bCanFinishImmediately;
	float Time;
	float TimeStarted;
	FTimerHandle TimerHandle;
//~ End Data
};

#undef MODULE_API
