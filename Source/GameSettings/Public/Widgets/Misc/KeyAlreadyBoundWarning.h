// Scientific Ways

#pragma once

#include "GameSettingPressAnyKey.h"
#include "KeyAlreadyBoundWarning.generated.h"

#define MODULE_API GAMESETTINGS_API

class UTextBlock;

/**
 * UKeyAlreadyBoundWarning
 * Press any key screen with text blocks for warning users when a key is already bound
 */
UCLASS(MinimalAPI, Abstract)
class UKeyAlreadyBoundWarning : public UGameSettingPressAnyKey
{
	GENERATED_BODY()

public:
	MODULE_API void SetWarningText(const FText& InText);

	MODULE_API void SetCancelText(const FText& InText);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> WarningText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> CancelText;
};

#undef MODULE_API
