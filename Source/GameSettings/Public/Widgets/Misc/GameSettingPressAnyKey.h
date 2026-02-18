// Scientific Ways

#pragma once

#include "CommonActivatableWidget.h"

#include "GameSettingPressAnyKey.generated.h"

#define MODULE_API GAMESETTINGS_API

struct FKey;

class UObject;

/**
 * 
 */
UCLASS(MinimalAPI, Abstract)
class UGameSettingPressAnyKey : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	MODULE_API UGameSettingPressAnyKey(const FObjectInitializer& Initializer);

	DECLARE_EVENT_OneParam(UGameSettingPressAnyKey, FOnKeySelected, FKey);
	FOnKeySelected OnKeySelected;

	DECLARE_EVENT(UGameSettingPressAnyKey, FOnKeySelectionCanceled);
	FOnKeySelectionCanceled OnKeySelectionCanceled;

protected:
	MODULE_API virtual void NativeOnActivated() override;
	MODULE_API virtual void NativeOnDeactivated() override;

	MODULE_API void HandleKeySelected(FKey InKey);
	MODULE_API void HandleKeySelectionCanceled();

	MODULE_API void Dismiss(TFunction<void()> PostDismissCallback);

private:
	bool bKeySelected = false;
	TSharedPtr<class FSettingsPressAnyKeyInputPreProcessor> InputProcessor;
};

#undef MODULE_API
