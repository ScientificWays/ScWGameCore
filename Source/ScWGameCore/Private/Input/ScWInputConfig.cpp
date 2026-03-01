// Scientific Ways

#include "Input/ScWInputConfig.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWInputConfig)

UScWInputConfig::UScWInputConfig(const FObjectInitializer& InObjectInitializer)
{

}

const UInputAction* UScWInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bInLogIfNotFound) const
{
	for (const FScWInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}
	if (bInLogIfNotFound)
	{
		UE_LOG(LogScWGameCore, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}

const UInputAction* UScWInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bInLogIfNotFound) const
{
	for (const FScWInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}
	if (bInLogIfNotFound)
	{
		UE_LOG(LogScWGameCore, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
