// Scientific Ways

#include "Character/Tasks/ScWAT_WaitForPawnReady.h"

#include "Character/ScWPawnExtensionComponent.h"

UScWAT_WaitForPawnReady* UScWAT_WaitForPawnReady::WaitForPawnReady(APawn* InTargetPawn)
{
	ensureReturn(InTargetPawn, nullptr);

	ThisClass* Task = NewObject<ThisClass>();
	Task->WatchedPawn = InTargetPawn;
	return Task;
}

void UScWAT_WaitForPawnReady::Activate() // UBlueprintAsyncActionBase
{
	Super::Activate();

	if ensure(WatchedPawn)
	{
		UScWPawnExtensionComponent* PawnExtComponent = UScWPawnExtensionComponent::GetPawnExtensionComponent(WatchedPawn);
		if ensure(PawnExtComponent)
		{
			WatchedPawn->OnEndPlay.AddDynamic(this, &ThisClass::OnWatchedPawnEndPlay);
			PawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnWatchedPawnAbilitySystemInitialized));
			return;
		}
	}
	Cancel();
}

void UScWAT_WaitForPawnReady::Cancel() // UCancellableAsyncAction
{
	OnCancelled.Broadcast(WatchedPawn);
	SetReadyToDestroy();
}

void UScWAT_WaitForPawnReady::BeginDestroy() // UObject
{
	if (WatchedPawn)
	{
		if (UScWPawnExtensionComponent* PawnExtComponent = UScWPawnExtensionComponent::GetPawnExtensionComponent(WatchedPawn))
		{
			PawnExtComponent->GetOnAbilitySystemInitialized().RemoveAll(this);
		}
		WatchedPawn->OnEndPlay.RemoveAll(this);
	}
	Super::BeginDestroy();
}

void UScWAT_WaitForPawnReady::OnWatchedPawnAbilitySystemInitialized()
{
	OnReady.Broadcast(WatchedPawn);
	SetReadyToDestroy();
}

void UScWAT_WaitForPawnReady::OnWatchedPawnEndPlay(AActor* InActor, EEndPlayReason::Type InEndPlayReason)
{
	Cancel();
}
