// Scientific Ways

#pragma once

#include "GameSettingValueDiscrete.h"

#include "ScWSettingValueDiscrete_Language.generated.h"

#define MODULE_API SCWGAMECORE_API

class FText;
class UObject;

UCLASS(MinimalAPI)
class UScWSettingValueDiscrete_Language : public UGameSettingValueDiscrete
{
	GENERATED_BODY()
	
public:

	MODULE_API UScWSettingValueDiscrete_Language();

	/** UGameSettingValue */
	MODULE_API virtual void StoreInitial() override;
	MODULE_API virtual void ResetToDefault() override;
	MODULE_API virtual void RestoreToInitial() override;

	/** UGameSettingValueDiscrete */
	MODULE_API virtual void SetDiscreteOptionByIndex(int32 Index) override;
	MODULE_API virtual int32 GetDiscreteOptionIndex() const override;
	MODULE_API virtual TArray<FText> GetDiscreteOptions() const override;

protected:
	/** UGameSettingValue */
	MODULE_API virtual void OnInitialized() override;
	MODULE_API virtual void OnApply() override;

protected:
	TArray<FString> AvailableCultureNames;
};

#undef MODULE_API
