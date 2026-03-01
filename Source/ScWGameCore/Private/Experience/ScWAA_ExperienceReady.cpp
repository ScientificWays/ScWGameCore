// Scientific Ways

#include "Experience/ScWAA_ExperienceReady.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Experience/ScWExperienceManagerComponent.h"
#include "TimerManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWAA_ExperienceReady)

UScWAA_ExperienceReady::UScWAA_ExperienceReady(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
}

UScWAA_ExperienceReady* UScWAA_ExperienceReady::WaitForExperienceReady(UObject* InWorldContextObject)
{
	UScWAA_ExperienceReady* Action = nullptr;

	if (UWorld* World = GEngine->GetWorldFromContextObject(InWorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		Action = NewObject<UScWAA_ExperienceReady>();
		Action->WorldPtr = World;
		Action->RegisterWithGameInstance(World);
	}
	return Action;
}

void UScWAA_ExperienceReady::Activate()
{
	if (UWorld* World = WorldPtr.Get())
	{
		if (AGameStateBase* GameState = World->GetGameState())
		{
			Step2_ListenToExperienceLoading(GameState);
		}
		else
		{
			World->GameStateSetEvent.AddUObject(this, &ThisClass::Step1_HandleGameStateSet);
		}
	}
	else
	{
		// No world so we'll never finish naturally
		SetReadyToDestroy();
	}
}

void UScWAA_ExperienceReady::Step1_HandleGameStateSet(AGameStateBase* GameState)
{
	if (UWorld* World = WorldPtr.Get())
	{
		World->GameStateSetEvent.RemoveAll(this);
	}
	Step2_ListenToExperienceLoading(GameState);
}

void UScWAA_ExperienceReady::Step2_ListenToExperienceLoading(AGameStateBase* GameState)
{
	check(GameState);
	UScWExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UScWExperienceManagerComponent>();
	check(ExperienceComponent);

	if (ExperienceComponent->IsExperienceLoaded())
	{
		UWorld* World = GameState->GetWorld();
		check(World);

		// The experience happened to be already loaded, but still delay a frame to
		// make sure people don't write stuff that relies on this always being true
		//@TODO: Consider not delaying for dynamically spawned stuff / any time after the loading screen has dropped?
		//@TODO: Maybe just inject a random 0-1s delay in the experience load itself?
		World->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &ThisClass::Step4_BroadcastReady));
	}
	else
	{
		ExperienceComponent->CallOrRegister_OnExperienceLoaded(FOnScWExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::Step3_HandleExperienceLoaded));
	}
}

void UScWAA_ExperienceReady::Step3_HandleExperienceLoaded(const UScWExperience* CurrentExperience)
{
	Step4_BroadcastReady();
}

void UScWAA_ExperienceReady::Step4_BroadcastReady()
{
	OnReady.Broadcast();
	SetReadyToDestroy();
}

