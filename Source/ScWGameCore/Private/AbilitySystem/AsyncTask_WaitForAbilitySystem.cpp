// Scientific Ways

#include "AbilitySystem/AsyncTask_WaitForAbilitySystem.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AsyncTask_WaitForAbilitySystem)

UAsyncTask_WaitForAbilitySystem* UAsyncTask_WaitForAbilitySystem::WaitForAbilitySystem(AActor* InTargetActor, float InTimeoutSeconds, float InCheckIntervalSeconds)
{
	ensureReturn(InTargetActor, nullptr);
	ensureReturn(InTimeoutSeconds > 0.0f, nullptr);
	ensureReturn(InCheckIntervalSeconds > 0.0f, nullptr);

	ThisClass* Task = NewObject<ThisClass>();
	Task->WatchedActor = InTargetActor;
	Task->TimeoutSeconds = InTimeoutSeconds;
	Task->IntervalSeconds = InCheckIntervalSeconds;
	Task->bFinished = false;
	return Task;
}

void UAsyncTask_WaitForAbilitySystem::Activate() // UBlueprintAsyncActionBase
{
	Super::Activate();

	PollAbilitySystem();
}

void UAsyncTask_WaitForAbilitySystem::Cancel()
{
	if (bFinished)
	{
		return;
	}
	bFinished = true;

	if (WatchedActor.IsValid())
	{
		if (UWorld* World = WatchedActor->GetWorld())
		{
			World->GetTimerManager().ClearTimer(TimerHandle);
		}
	}
	OnCancelled.Broadcast(nullptr);
	SetReadyToDestroy();
}

void UAsyncTask_WaitForAbilitySystem::PollAbilitySystem()
{
	if (bFinished || !WatchedActor.IsValid())
	{
		Finish(nullptr);
		return;
	}
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(WatchedActor.Get()))
	{
		Finish(ASC);
		return;
	}
	ElapsedTime += IntervalSeconds;

	if (ElapsedTime >= TimeoutSeconds)
	{
		Finish(nullptr);
		return;
	}
	if (UWorld* World = WatchedActor->GetWorld())
	{
		World->GetTimerManager().SetTimer(TimerHandle, this, &UAsyncTask_WaitForAbilitySystem::PollAbilitySystem, IntervalSeconds, false);
	}
}

void UAsyncTask_WaitForAbilitySystem::Finish(UAbilitySystemComponent* InFoundASC)
{
	if (bFinished)
	{
		return;
	}
	bFinished = true;

	if (InFoundASC)
	{
		OnFound.Broadcast(InFoundASC);
	}
	else
	{
		OnCancelled.Broadcast(nullptr);
	}
	SetReadyToDestroy();
}
