// Scientific Ways

#include "Game/ScWGamePauseSubsystem.h"

#include "Components/TimelineComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWGamePauseSubsystem)

//~ Begin Initialize
UScWGamePauseSubsystem::UScWGamePauseSubsystem()
{
	SlowdownPropertyName = TEXT("SlowdownAlpha");
	SlowdownTrackName = TEXT("SlowdownTrack");
}

void UScWGamePauseSubsystem::OnWorldBeginPlay(UWorld& InWorld) // UWorldSubsystem
{
	Super::OnWorldBeginPlay(InWorld);

	AGameStateBase* GameStateBase = InWorld.GetGameState();
	ensureReturn(GameStateBase);

	SlowdownTimeline = NewObject<UTimelineComponent>(GameStateBase);
	ensureReturn(SlowdownTimeline);

	SlowdownAlphaCurve = NewObject<UCurveFloat>();
	SlowdownAlphaCurve->FloatCurve.AddKey(0.0f, 0.0f);
	SlowdownAlphaCurve->FloatCurve.AddKey(1.0f, 1.0f);

	FOnTimelineFloat SlowdownUpdateFunction;
	SlowdownUpdateFunction.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ThisClass, OnSlowdownTimelineUpdate));
	SlowdownTimeline->AddInterpFloat(SlowdownAlphaCurve, SlowdownUpdateFunction, SlowdownPropertyName, SlowdownTrackName);

	FOnTimelineEvent SlowdownFinishedFunction;
	SlowdownFinishedFunction.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ThisClass, OnSlowdownTimelineFinished));
	SlowdownTimeline->SetTimelineFinishedFunc(SlowdownFinishedFunction);

	SlowdownTimeline->SetLooping(false);
	SlowdownTimeline->SetPlayRate(0.5f);

	SlowdownTimeline->RegisterComponent();
}
//~ End Initialize

//~ Begin State
void UScWGamePauseSubsystem::UpdatePauseState()
{
	ensureReturn(SlowdownTimeline);

	if (PauseSourceObjectsSet.IsEmpty())
	{
		SlowdownTargetTimeDilation = 1.0f;
		SlowdownTimeline->Reverse();
	}
	else
	{
		SlowdownTargetTimeDilation = 0.0f;
		SlowdownTimeline->Play();
	}
}
//~ End State

//~ Begin Source Objects
void UScWGamePauseSubsystem::AddPauseSourceObject(UObject* InSourceObject)
{
	PauseSourceObjectsSet.Add(InSourceObject);
	UpdatePauseState();
}

void UScWGamePauseSubsystem::RemovePauseSourceObject(UObject* InSourceObject)
{
	PauseSourceObjectsSet.Remove(InSourceObject);
	UpdatePauseState();
}

void UScWGamePauseSubsystem::SetSlowdownRate(float InRate)
{
	ensureReturn(SlowdownTimeline);
	SlowdownTimeline->SetPlayRate(InRate);
}

void UScWGamePauseSubsystem::SetSlowdownAlphaCurve(UCurveFloat* InCurve)
{
	SlowdownAlphaCurve = InCurve;
	SlowdownTimeline->SetFloatCurve(SlowdownAlphaCurve, SlowdownTrackName);
}
//~ End Source Objects

//~ Begin Slowdown
void UScWGamePauseSubsystem::OnSlowdownTimelineUpdate(float InValue)
{
	UWorld* World = GetWorld();
	ensureReturn(World);

	AWorldSettings* WorldSettings = World->GetWorldSettings();
	ensureReturn(WorldSettings);
	WorldSettings->SetTimeDilation(FMath::Lerp(WorldSettings->TimeDilation, SlowdownTargetTimeDilation, InValue));
}

void UScWGamePauseSubsystem::OnSlowdownTimelineFinished()
{
	UWorld* World = GetWorld();
	ensureReturn(World);

	AWorldSettings* WorldSettings = World->GetWorldSettings();
	ensureReturn(WorldSettings);
	WorldSettings->SetTimeDilation(SlowdownTargetTimeDilation);

	UGameInstance* GameInstance = World->GetGameInstance();
	ensureReturn(GameInstance);

	APlayerController* FirstPlayerController = GameInstance->GetFirstLocalPlayerController();
	ensureReturn(FirstPlayerController);

	FirstPlayerController->SetPause(SlowdownTargetTimeDilation < KINDA_SMALL_NUMBER);
}
//~ End Slowdown
