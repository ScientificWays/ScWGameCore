// Scientific Ways

#include "AbilitySystem/Tasks/ScWAT_WaitForAbilitySystem.h"

UScWAT_WaitForAbilitySystem* UScWAT_WaitForAbilitySystem::WaitForAbilitySystem(AActor* InTargetActor, float InTimeoutSeconds, float InCheckIntervalSeconds)
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

void UScWAT_WaitForAbilitySystem::Activate() // UBlueprintAsyncActionBase
{
	Super::Activate();

	PollAbilitySystem();
}

void UScWAT_WaitForAbilitySystem::Cancel() // UCancellableAsyncAction
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

void UScWAT_WaitForAbilitySystem::PollAbilitySystem()
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
		World->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::PollAbilitySystem, IntervalSeconds, false);
	}
}

void UScWAT_WaitForAbilitySystem::Finish(UAbilitySystemComponent* InFoundASC)
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
