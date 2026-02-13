// Scientific Ways

#include "Input/ScWInputFunctionLibrary.h"

//~ Begin Input
bool UScWInputFunctionLibrary::AddEnhancedInputMappingContextTo(APlayerController* InPlayerController, const UInputMappingContext* InMappingContext, int32 InPriority, const FModifyContextOptions& InOptions)
{
	if (InPlayerController && InMappingContext)
	{
		if (ULocalPlayer* LocalPlayer = InPlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(InMappingContext, InPriority, InOptions);
				return true;
			}
		}
	}
	return false;
}

bool UScWInputFunctionLibrary::RemoveEnhancedInputMappingContextFrom(APlayerController* InPlayerController, const UInputMappingContext* InMappingContext, const FModifyContextOptions& InOptions)
{
	if (InPlayerController && InMappingContext)
	{
		if (ULocalPlayer* LocalPlayer = InPlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->RemoveMappingContext(InMappingContext, InOptions);
				return true;
			}
		}
	}
	return false;
}

bool UScWInputFunctionLibrary::GetActionMappedKeyDisplayName(APlayerController* InPlayerController, const UInputAction* InInputAction, const bool bInLongDisplayName, FText& OutDisplayName)
{
	OutDisplayName = FText::GetEmpty();

	if (InPlayerController && InInputAction)
	{
		if (ULocalPlayer* LocalPlayer = InPlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				TArray<FKey> MappedKeys = Subsystem->QueryKeysMappedToAction(InInputAction);

				if (MappedKeys.Num() > 0)
				{
					OutDisplayName = MappedKeys[0].GetDisplayName(bInLongDisplayName);
					return true;
				}
			}
		}
	}
	return false;
}
//~ End Input
