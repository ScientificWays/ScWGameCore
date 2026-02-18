// Scientific Ways

#pragma once

#include "GameSettingValueScalar.h"

#include "GameSettingValueScalarDynamic.generated.h"

#define MODULE_API GAMESETTINGS_API

struct FNumberFormattingOptions;

class FGameSettingDataSource;
class UObject;

//////////////////////////////////////////////////////////////////////////
// UGameSettingValueScalarDynamic
//////////////////////////////////////////////////////////////////////////

typedef TFunction<FText(double SourceValue, double NormalizedValue)> FSettingScalarFormatFunction;

UCLASS(MinimalAPI)
class UGameSettingValueScalarDynamic : public UGameSettingValueScalar
{
	GENERATED_BODY()

public:
	static MODULE_API FSettingScalarFormatFunction Raw;
	static MODULE_API FSettingScalarFormatFunction RawOneDecimal;
	static MODULE_API FSettingScalarFormatFunction RawTwoDecimals;
	static MODULE_API FSettingScalarFormatFunction ZeroToOnePercent;
	static MODULE_API FSettingScalarFormatFunction ZeroToOnePercent_OneDecimal;
	static MODULE_API FSettingScalarFormatFunction SourceAsPercent1;
	static MODULE_API FSettingScalarFormatFunction SourceAsPercent100;
	static MODULE_API FSettingScalarFormatFunction SourceAsInteger;
private:
	static const FNumberFormattingOptions& GetOneDecimalFormattingOptions();
	
public:
	MODULE_API UGameSettingValueScalarDynamic();

	/** UGameSettingValue */
	MODULE_API virtual void Startup() override;
	MODULE_API virtual void StoreInitial() override;
	MODULE_API virtual void ResetToDefault() override;
	MODULE_API virtual void RestoreToInitial() override;

	/** UGameSettingValueScalar */
	MODULE_API virtual TOptional<double> GetDefaultValue() const override;
	MODULE_API virtual void SetValue(double Value, EGameSettingChangeReason Reason = EGameSettingChangeReason::Change) override;
	MODULE_API virtual double GetValue() const override;
	MODULE_API virtual TRange<double> GetSourceRange() const override;
	MODULE_API virtual double GetSourceStep() const override;
	MODULE_API virtual FText GetFormattedText() const override;

	/** UGameSettingValueDiscreteDynamic */
	MODULE_API void SetDynamicGetter(const TSharedRef<FGameSettingDataSource>& InGetter);
	MODULE_API void SetDynamicSetter(const TSharedRef<FGameSettingDataSource>& InSetter);
	MODULE_API void SetDefaultValue(double InValue);

	/**  */
	MODULE_API void SetDisplayFormat(FSettingScalarFormatFunction InDisplayFormat);
	
	/**  */
	MODULE_API void SetSourceRangeAndStep(const TRange<double>& InRange, double InSourceStep);
	
	/**
	 * The SetSourceRangeAndStep defines the actual range the numbers could move in, but often
	 * the true minimum for the user is greater than the minimum source range, so for example, the range
	 * of some slider might be 0..100, but you want to restrict the slider so that while it shows 
	 * a bar that travels from 0 to 100, the user can't set anything lower than some minimum, e.g. 1.
	 * That is the Minimum Limit.
	 */
	MODULE_API void SetMinimumLimit(const TOptional<double>& InMinimum);

	/**
	 * The SetSourceRangeAndStep defines the actual range the numbers could move in, but rarely
	 * the true maximum for the user is less than the maximum source range, so for example, the range
	 * of some slider might be 0..100, but you want to restrict the slider so that while it shows
	 * a bar that travels from 0 to 100, the user can't set anything lower than some maximum, e.g. 95.
	 * That is the Maximum Limit.
	 */
	MODULE_API void SetMaximumLimit(const TOptional<double>& InMaximum);
	
protected:
	/** UGameSettingValue */
	MODULE_API virtual void OnInitialized() override;

	MODULE_API void OnDataSourcesReady();

protected:

	TSharedPtr<FGameSettingDataSource> Getter;
	TSharedPtr<FGameSettingDataSource> Setter;

	TOptional<double> DefaultValue;
	double InitialValue = 0;

	TRange<double> SourceRange = TRange<double>(0, 1);
	double SourceStep = 0.01;
	TOptional<double> Minimum;
	TOptional<double> Maximum;

	FSettingScalarFormatFunction DisplayFormat;
};

#undef MODULE_API
