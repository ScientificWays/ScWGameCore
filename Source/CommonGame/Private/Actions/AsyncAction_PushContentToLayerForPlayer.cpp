// Scientific Ways

#include "Actions/AsyncAction_PushContentToLayerForPlayer.h"

#include "Engine/Engine.h"
#include "PrimaryGameLayout.h"
#include "UObject/Stack.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AsyncAction_PushContentToLayerForPlayer)

UAsyncAction_PushContentToLayerForPlayer::UAsyncAction_PushContentToLayerForPlayer(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{

}

UAsyncAction_PushContentToLayerForPlayer* UAsyncAction_PushContentToLayerForPlayer::PushContentToLayerForPlayer(APlayerController* InOwningPlayer, TSoftClassPtr<UCommonActivatableWidget> InWidgetClass, FGameplayTag InLayerTag, bool bInSuspendInputUntilComplete)
{
	if (InWidgetClass.IsNull())
	{
		FFrame::KismetExecutionMessage(TEXT("PushContentToLayerForPlayer was passed a null WidgetClass"), ELogVerbosity::Error);
		return nullptr;
	}

	if (UWorld* World = GEngine->GetWorldFromContextObject(InOwningPlayer, EGetWorldErrorMode::LogAndReturnNull))
	{
		UAsyncAction_PushContentToLayerForPlayer* Action = NewObject<UAsyncAction_PushContentToLayerForPlayer>();
		Action->WidgetClass = InWidgetClass;
		Action->OwningPlayerPtr = InOwningPlayer;
		Action->LayerTag = InLayerTag;
		Action->bSuspendInputUntilComplete = bInSuspendInputUntilComplete;
		Action->RegisterWithGameInstance(World);

		return Action;
	}
	return nullptr;
}

void UAsyncAction_PushContentToLayerForPlayer::Cancel()
{
	Super::Cancel();

	if (StreamingHandle.IsValid())
	{
		StreamingHandle->CancelHandle();
		StreamingHandle.Reset();
	}
}

void UAsyncAction_PushContentToLayerForPlayer::Activate()
{
	if (UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayout(OwningPlayerPtr.Get()))
	{
		TWeakObjectPtr<UAsyncAction_PushContentToLayerForPlayer> WeakThis = this;
		StreamingHandle = RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(LayerTag, bSuspendInputUntilComplete, WidgetClass, [this, WeakThis](EAsyncWidgetLayerState State, UCommonActivatableWidget* Widget) {
			if (WeakThis.IsValid())
			{
				switch (State)
				{
					case EAsyncWidgetLayerState::Initialize:
						BeforePush.Broadcast(Widget);
						break;
					case EAsyncWidgetLayerState::AfterPush:
						AfterPush.Broadcast(Widget);
						SetReadyToDestroy();
						break;
					case EAsyncWidgetLayerState::Canceled:
						SetReadyToDestroy();
						break;
				}
			}
			SetReadyToDestroy();
		});
	}
	else
	{
		SetReadyToDestroy();
	}
}

