// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Subsystems/WorldSubsystem.h"

#include "ScWGamePauseSubsystem.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Game Pause Subsystem"))
class UScWGamePauseSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

//~ Begin Initialize
public:
	UScWGamePauseSubsystem();
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override; // UWorldSubsystem
//~ End Initialize

//~ Begin State
protected:
	void UpdatePauseState();
//~ End State

//~ Begin Source Objects
public:

	UFUNCTION(Category = "Source Objects", BlueprintCallable, meta = (DefaultToSelf = "InSourceObject"))
	MODULE_API void AddPauseSourceObject(UObject* InSourceObject);

	UFUNCTION(Category = "Source Objects", BlueprintCallable, meta = (DefaultToSelf = "InSourceObject"))
	MODULE_API void RemovePauseSourceObject(UObject* InSourceObject);

protected:

	UPROPERTY(Category = "Source Objects", BlueprintReadOnly)
	TSet<TObjectPtr<UObject>> PauseSourceObjectsSet;
//~ End Source Objects

//~ Begin Slowdown
public:

	UFUNCTION(Category = "Slowdown", BlueprintCallable)
	MODULE_API void SetSlowdownRate(float InRate = 0.5f);

	UFUNCTION(Category = "Slowdown", BlueprintCallable)
	MODULE_API void SetSlowdownAlphaCurve(UCurveFloat* InCurve);

protected:

	UPROPERTY()
	float SlowdownTargetTimeDilation;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> SlowdownTimeline;

	UPROPERTY(Category = "Slowdown", BlueprintReadOnly)
	TObjectPtr<UCurveFloat> SlowdownAlphaCurve;

	UPROPERTY()
	FName SlowdownPropertyName;

	UPROPERTY()
	FName SlowdownTrackName;

	UFUNCTION()
	void OnSlowdownTimelineUpdate(float InValue);

	UFUNCTION()
	void OnSlowdownTimelineFinished();
//~ End Slowdown
};

#undef MODULE_API
