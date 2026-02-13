// Scientific Ways

#pragma once

#include "CommonActivatableWidget.h"
#include "CommonMessagingSubsystem.h"

#include "CommonGameDialog.generated.h"

#define MODULE_API COMMONGAME_API

USTRUCT(BlueprintType)
struct FConfirmationDialogAction
{
	GENERATED_BODY()

public:
	/** Required: The dialog option to provide. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECommonMessagingResult Result = ECommonMessagingResult::Unknown;

	/** Optional: Display Text to use instead of the action name associated with the result. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionalDisplayText;

	bool operator==(const FConfirmationDialogAction& Other) const
	{
		return Result == Other.Result &&
			OptionalDisplayText.EqualTo(Other.OptionalDisplayText);
	}
};

UCLASS(MinimalAPI)
class UCommonGameDialogDescriptor : public UObject
{
	GENERATED_BODY()
	
public:
	static MODULE_API UCommonGameDialogDescriptor* CreateConfirmationOk(const FText& Header, const FText& Body);
	static MODULE_API UCommonGameDialogDescriptor* CreateConfirmationOkCancel(const FText& Header, const FText& Body);
	static MODULE_API UCommonGameDialogDescriptor* CreateConfirmationYesNo(const FText& Header, const FText& Body);
	static MODULE_API UCommonGameDialogDescriptor* CreateConfirmationYesNoCancel(const FText& Header, const FText& Body);

public:
	/** The header of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Header;
	
	/** The body of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Body;

	/** The confirm button's input action to use. */
	UPROPERTY(BlueprintReadWrite)
	TArray<FConfirmationDialogAction> ButtonActions;
};


UCLASS(MinimalAPI, Abstract)
class UCommonGameDialog : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	MODULE_API UCommonGameDialog();
	
	MODULE_API virtual void SetupDialog(UCommonGameDialogDescriptor* Descriptor, FCommonMessagingResultDelegate ResultCallback);

	MODULE_API virtual void KillDialog();
};

#undef MODULE_API
