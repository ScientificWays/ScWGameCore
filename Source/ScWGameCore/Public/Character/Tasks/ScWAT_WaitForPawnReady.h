// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Engine/CancellableAsyncAction.h"

#include "Utils/ScWTypes_CommonDelegates.h"

#include "ScWAT_WaitForPawnReady.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *	Listents for Pawn's PawnExtensionComponent ready state
 */
UCLASS(MinimalAPI)
class UScWAT_WaitForPawnReady : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FPawnSignature OnReady;

	UPROPERTY(BlueprintAssignable)
	FPawnSignature OnFailed;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static MODULE_API UScWAT_WaitForPawnReady* WaitForPawnReady(APawn* InTargetPawn);

	virtual void Activate() override; // UBlueprintAsyncActionBase
	virtual void Cancel() override; // UCancellableAsyncAction
	virtual void BeginDestroy() override; // UObject
protected:

	UPROPERTY()
	TObjectPtr<APawn> WatchedPawn;

	UFUNCTION()
	void OnWatchedPawnAbilitySystemInitialized();

	UFUNCTION()
	void OnWatchedPawnEndPlay(AActor* InActor, EEndPlayReason::Type InEndPlayReason);
};

#undef MODULE_API
