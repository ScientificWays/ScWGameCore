// Scientific Ways

#pragma once

#include "GameSettingValue.h"

#include "GameSettingValueDiscrete.generated.h"

#define MODULE_API GAMESETTINGS_API

class UObject;
struct FFrame;

UCLASS(MinimalAPI, Abstract)
class UGameSettingValueDiscrete : public UGameSettingValue
{
	GENERATED_BODY()

public:
	MODULE_API UGameSettingValueDiscrete();

	/** UGameSettingValueDiscrete */
	MODULE_API virtual void SetDiscreteOptionByIndex(int32 Index) PURE_VIRTUAL(,);
	
	UFUNCTION(BlueprintCallable)
	MODULE_API virtual int32 GetDiscreteOptionIndex() const PURE_VIRTUAL(,return INDEX_NONE;);

	/** Optional */
	UFUNCTION(BlueprintCallable)
	virtual int32 GetDiscreteOptionDefaultIndex() const { return INDEX_NONE; }

	UFUNCTION(BlueprintCallable)
	MODULE_API virtual TArray<FText> GetDiscreteOptions() const PURE_VIRTUAL(,return TArray<FText>(););

	MODULE_API virtual FString GetAnalyticsValue() const;
};

#undef MODULE_API
