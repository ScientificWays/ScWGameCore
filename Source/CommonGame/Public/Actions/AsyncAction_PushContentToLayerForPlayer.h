// Scientific Ways

#pragma once

#include "Engine/CancellableAsyncAction.h"
#include "GameplayTagContainer.h"
#include "UObject/SoftObjectPtr.h"

#include "AsyncAction_PushContentToLayerForPlayer.generated.h"

#define MODULE_API COMMONGAME_API

class APlayerController;
class UCommonActivatableWidget;
class UObject;
struct FFrame;
struct FStreamableHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPushContentToLayerForPlayerAsyncDelegate, UCommonActivatableWidget*, UserWidget);

/**
 * 
 */
UCLASS(MinimalAPI, BlueprintType)
class UAsyncAction_PushContentToLayerForPlayer : public UCancellableAsyncAction
{
	GENERATED_UCLASS_BODY()

public:
	MODULE_API virtual void Cancel() override;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (DefaultToSelf = "OwningPlayer", DisplayName = "Push Content to Layer for Player (Async)", BlueprintInternalUseOnly = "true"))
	static MODULE_API UAsyncAction_PushContentToLayerForPlayer* PushContentToLayerForPlayer(APlayerController* InOwningPlayer, UPARAM(meta = (AllowAbstract=false)) TSoftClassPtr<UCommonActivatableWidget> InWidgetClass, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag InLayerTag, bool bInSuspendInputUntilComplete = true);

	MODULE_API virtual void Activate() override;

public:

	UPROPERTY(BlueprintAssignable)
	FPushContentToLayerForPlayerAsyncDelegate BeforePush;

	UPROPERTY(BlueprintAssignable)
	FPushContentToLayerForPlayerAsyncDelegate AfterPush;

private:

	FGameplayTag LayerTag;
	bool bSuspendInputUntilComplete = false;
	TWeakObjectPtr<APlayerController> OwningPlayerPtr;
	TSoftClassPtr<UCommonActivatableWidget> WidgetClass;

	TSharedPtr<FStreamableHandle> StreamingHandle;
};

#undef MODULE_API
