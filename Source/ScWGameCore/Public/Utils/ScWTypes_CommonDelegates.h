// Scientific Ways

#pragma once

#include "Utils/ScWUtils.h"

#include "ScWTypes_CommonDelegates.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FDefaultCallbackSignature);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDefaultEventSignature);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoolSignature, bool, bInValue);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSuccessSignature, bool, bInSuccess);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWasCancelledSignature, bool, bInWasCancelled);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedSignature, const FGameplayAttribute&, InAttribute, float, InPrevValue, float, InNewValue);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTeamNameSignature, const FName&, InTeamName);

USTRUCT(BlueprintType)
struct FDelegateHandle_BlueprintWrapper
{
	GENERATED_BODY()

	FDelegateHandle Handle;

	operator FDelegateHandle() { return Handle; }
};
