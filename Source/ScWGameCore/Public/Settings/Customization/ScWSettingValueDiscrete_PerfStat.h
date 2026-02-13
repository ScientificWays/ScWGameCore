// Scientific Ways

#pragma once

#include "GameSettingValueDiscrete.h"

#include "ScWSettingValueDiscrete_PerfStat.generated.h"

enum class EScWDisplayablePerformanceStat : uint8;
enum class EScWStatDisplayMode : uint8;

class UObject;

UCLASS()
class UScWSettingValueDiscrete_PerfStat : public UGameSettingValueDiscrete
{
	GENERATED_BODY()
	
public:

	UScWSettingValueDiscrete_PerfStat();

	void SetStat(EScWDisplayablePerformanceStat InStat);

	// UGameSettingValue
	virtual void StoreInitial() override;
	virtual void ResetToDefault() override;
	virtual void RestoreToInitial() override;

	// UGameSettingValueDiscrete
	virtual void SetDiscreteOptionByIndex(int32 Index) override;
	virtual int32 GetDiscreteOptionIndex() const override;
	virtual TArray<FText> GetDiscreteOptions() const override;

protected:
	// UGameSettingValue
	virtual void OnInitialized() override;
	
	void AddMode(FText&& Label, EScWStatDisplayMode Mode);
protected:
	TArray<FText> Options;
	TArray<EScWStatDisplayMode> DisplayModes;

	EScWDisplayablePerformanceStat StatToDisplay;
	EScWStatDisplayMode InitialMode;
};
