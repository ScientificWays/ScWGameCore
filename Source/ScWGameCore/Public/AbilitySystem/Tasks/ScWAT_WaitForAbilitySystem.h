// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Engine/CancellableAsyncAction.h"

#include "ScWAT_WaitForAbilitySystem.generated.h"

#define MODULE_API SCWGAMECORE_API

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilitySystemFoundDelegate, class UAbilitySystemComponent*, AbilitySystem);

/**
 *	Polls Ability System Component on target actor
 */
UCLASS(MinimalAPI)
class UScWAT_WaitForAbilitySystem : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FAbilitySystemFoundDelegate OnFound;

	UPROPERTY(BlueprintAssignable)
	FAbilitySystemFoundDelegate OnCancelled;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static MODULE_API UScWAT_WaitForAbilitySystem* WaitForAbilitySystem(class AActor* InTargetActor, float InTimeoutSeconds = 5.0f, float InCheckIntervalSeconds = 0.1f);

	virtual void Activate() override; // UBlueprintAsyncActionBase
	virtual void Cancel() override; // UCancellableAsyncAction
protected:

	UPROPERTY()
	TWeakObjectPtr<class AActor> WatchedActor;

	FTimerHandle TimerHandle;
	float ElapsedTime;
	float TimeoutSeconds;
	float IntervalSeconds;
	bool bFinished;

	void PollAbilitySystem();
	void Finish(class UAbilitySystemComponent* InFoundASC);
};

#undef MODULE_API
