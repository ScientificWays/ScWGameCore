// Scientific Ways

#pragma once

#include "Subsystems/LocalPlayerSubsystem.h"

#include "CommonMessagingSubsystem.generated.h"

#define MODULE_API COMMONGAME_API

class FSubsystemCollectionBase;
class UCommonGameDialogDescriptor;
class UObject;

/** Possible results from a dialog */
UENUM(BlueprintType)
enum class ECommonMessagingResult : uint8
{
	/** The "yes" button was pressed */
	Confirmed,
	/** The "no" button was pressed */
	Declined,
	/** The "ignore/cancel" button was pressed */
	Cancelled,
	/** The dialog was explicitly killed (no user input) */
	Killed,
	Unknown UMETA(Hidden)
};

DECLARE_DELEGATE_OneParam(FCommonMessagingResultDelegate, ECommonMessagingResult /* Result */);

/**
 * 
 */
UCLASS(MinimalAPI, config = Game)
class UCommonMessagingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UCommonMessagingSubsystem() { }

	MODULE_API virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	MODULE_API virtual void Deinitialize() override;
	MODULE_API virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	MODULE_API virtual void ShowConfirmation(UCommonGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate());
	MODULE_API virtual void ShowError(UCommonGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate());

private:

};

#undef MODULE_API
