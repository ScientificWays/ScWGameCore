// Scientific Ways

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"

#include "ScWAA_ExperienceReady.generated.h"

#define MODULE_API SCWGAMECORE_API

class AGameStateBase;
class UScWExperience;
class UWorld;
struct FFrame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExperienceReadyAsyncDelegate);

/**
 * Asynchronously waits for the game state to be ready and valid and then calls the OnReady event.  Will call OnReady
 * immediately if the game state is valid already.
 */
UCLASS()
class UScWAA_ExperienceReady : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UScWAA_ExperienceReady(const FObjectInitializer& InObjectInitializer);

	// Waits for the experience to be determined and loaded
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "InWCO", BlueprintInternalUseOnly = "true"))
	static MODULE_API UScWAA_ExperienceReady* WaitForExperienceReady(UObject* InWCO);

	MODULE_API virtual void Activate() override;

public:

	// Called when the experience has been determined and is ready/loaded
	UPROPERTY(BlueprintAssignable)
	FExperienceReadyAsyncDelegate OnReady;

private:
	void Step1_HandleGameStateSet(AGameStateBase* GameState);
	void Step2_ListenToExperienceLoading(AGameStateBase* GameState);
	void Step3_HandleExperienceLoaded(const UScWExperience* CurrentExperience);
	void Step4_BroadcastReady();

	TWeakObjectPtr<UWorld> WorldPtr;
};

#undef MODULE_API
