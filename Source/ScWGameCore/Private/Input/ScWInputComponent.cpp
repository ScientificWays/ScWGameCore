// Scientific Ways

#include "Input/ScWInputComponent.h"

#include "EnhancedInputSubsystems.h"
#include "Player/ScWLocalPlayer.h"
#include "Settings/ScWSettingsLocal.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWInputComponent)

class UScWInputConfig;

UScWInputComponent::UScWInputComponent(const FObjectInitializer& InObjectInitializer)
{
}

void UScWInputComponent::AddInputMappings(const UScWInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to add something from your input config if required
}

void UScWInputComponent::RemoveInputMappings(const UScWInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to remove input mappings that you may have added above
}

void UScWInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
