// Scientific Ways

#pragma once

#include "GameSettingValueDiscrete.h"

#include "GameSettingValueDiscreteDynamic.generated.h"

#define MODULE_API GAMESETTINGS_API

class FGameSettingDataSource;
enum class EGameSettingChangeReason : uint8;

struct FContentControlsRules;

//////////////////////////////////////////////////////////////////////////
// UGameSettingValueDiscreteDynamic
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UGameSettingValueDiscreteDynamic : public UGameSettingValueDiscrete
{
	GENERATED_BODY()
	
public:
	MODULE_API UGameSettingValueDiscreteDynamic();

	/** UGameSettingValue */
	MODULE_API virtual void Startup() override;
	MODULE_API virtual void StoreInitial() override;
	MODULE_API virtual void ResetToDefault() override;
	MODULE_API virtual void RestoreToInitial() override;

	/** UGameSettingValueDiscrete */
	MODULE_API virtual void SetDiscreteOptionByIndex(int32 Index) override;
	MODULE_API virtual int32 GetDiscreteOptionIndex() const override;
	MODULE_API virtual int32 GetDiscreteOptionDefaultIndex() const override;
	MODULE_API virtual TArray<FText> GetDiscreteOptions() const override;

	/** UGameSettingValueDiscreteDynamic */
	MODULE_API void SetDynamicGetter(const TSharedRef<FGameSettingDataSource>& InGetter);
	MODULE_API void SetDynamicSetter(const TSharedRef<FGameSettingDataSource>& InSetter);
	MODULE_API void SetDefaultValueFromString(FString InOptionValue);
	MODULE_API void AddDynamicOption(FString InOptionValue, FText InOptionText);
	MODULE_API void RemoveDynamicOption(FString InOptionValue);
	MODULE_API const TArray<FString>& GetDynamicOptions();

	MODULE_API bool HasDynamicOption(const FString& InOptionValue);

	MODULE_API FString GetValueAsString() const;
	MODULE_API void SetValueFromString(FString InStringValue);

protected:
	MODULE_API void SetValueFromString(FString InStringValue, EGameSettingChangeReason Reason);

	/** UGameSettingValue */
	MODULE_API virtual void OnInitialized() override;

	MODULE_API void OnDataSourcesReady();

	MODULE_API bool AreOptionsEqual(const FString& InOptionA, const FString& InOptionB) const;

protected:
	TSharedPtr<FGameSettingDataSource> Getter;
	TSharedPtr<FGameSettingDataSource> Setter;

	TOptional<FString> DefaultValue;
	FString InitialValue;

	TArray<FString> OptionValues;
	TArray<FText> OptionDisplayTexts;
};

//////////////////////////////////////////////////////////////////////////
// UGameSettingValueDiscreteDynamic_Bool
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UGameSettingValueDiscreteDynamic_Bool : public UGameSettingValueDiscreteDynamic
{
	GENERATED_BODY()

public:
	MODULE_API UGameSettingValueDiscreteDynamic_Bool();

public:
	MODULE_API void SetDefaultValue(bool Value);

	MODULE_API void SetTrueText(const FText& InText);
	MODULE_API void SetFalseText(const FText& InText);

#if !UE_BUILD_SHIPPING
	void SetTrueText(const FString& Value) { SetTrueText(FText::FromString(Value)); }
	void SetFalseText(const FString& Value) { SetFalseText(FText::FromString(Value)); }
#endif
};

//////////////////////////////////////////////////////////////////////////
// UGameSettingValueDiscreteDynamic_Number
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UGameSettingValueDiscreteDynamic_Number : public UGameSettingValueDiscreteDynamic
{
	GENERATED_BODY()

public:
	MODULE_API UGameSettingValueDiscreteDynamic_Number();

public:
	template<typename NumberType>
	void SetDefaultValue(NumberType InValue)
	{
		SetDefaultValueFromString(LexToString(InValue));
	}

	template<typename NumberType>
	void AddOption(NumberType InValue, const FText& InOptionText)
	{
		AddDynamicOption(LexToString(InValue), InOptionText);
	}

	template<typename NumberType>
	NumberType GetValue() const
	{
		const FString ValueString = GetValueAsString();

		NumberType OutValue;
		LexFromString(OutValue, *ValueString);

		return OutValue;
	}

	template<typename NumberType>
	void SetValue(NumberType InValue)
	{
		SetValueFromString(LexToString(InValue));
	}

protected:
	/** UGameSettingValue */
	MODULE_API virtual void OnInitialized() override;
};

//////////////////////////////////////////////////////////////////////////
// UGameSettingValueDiscreteDynamic_Enum
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UGameSettingValueDiscreteDynamic_Enum : public UGameSettingValueDiscreteDynamic
{
	GENERATED_BODY()

public:
	MODULE_API UGameSettingValueDiscreteDynamic_Enum();

public:
	template<typename EnumType>
	void SetDefaultValue(EnumType InEnumValue)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		SetDefaultValueFromString(StringValue);
	}

	template<typename EnumType>
	void AddEnumOption(EnumType InEnumValue, const FText& InOptionText)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		AddDynamicOption(StringValue, InOptionText);
	}

	template<typename EnumType>
	EnumType GetValue() const
	{
		const FString Value = GetValueAsString();
		return (EnumType)StaticEnum<EnumType>()->GetValueByNameString(Value);
	}

	template<typename EnumType>
	void SetValue(EnumType InEnumValue)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		SetValueFromString(StringValue);
	}

protected:
	/** UGameSettingValue */
	MODULE_API virtual void OnInitialized() override;
};

//////////////////////////////////////////////////////////////////////////
// UGameSettingValueDiscreteDynamic_Color
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UGameSettingValueDiscreteDynamic_Color : public UGameSettingValueDiscreteDynamic
{
	GENERATED_BODY()

public:
	MODULE_API UGameSettingValueDiscreteDynamic_Color();

public:
	void SetDefaultValue(FLinearColor InColor)
	{
		SetDefaultValueFromString(InColor.ToString());
	}

	void AddColorOption(FLinearColor InColor)
	{
		const FColor SRGBColor = InColor.ToFColor(true);
		AddDynamicOption(InColor.ToString(), FText::FromString(FString::Printf(TEXT("#%02X%02X%02X"), SRGBColor.R, SRGBColor.G, SRGBColor.B)));
	}

	FLinearColor GetValue() const
	{
		const FString Value = GetValueAsString();
		
		FLinearColor ColorValue;
		bool bSuccess = ColorValue.InitFromString(Value);
		ensure(bSuccess);

		return ColorValue;
	}

	void SetValue(FLinearColor InColor)
	{
		SetValueFromString(InColor.ToString());
	}
};

//////////////////////////////////////////////////////////////////////////
// UGameSettingValueDiscreteDynamic_Vector2D
//////////////////////////////////////////////////////////////////////////

UCLASS(MinimalAPI)
class UGameSettingValueDiscreteDynamic_Vector2D : public UGameSettingValueDiscreteDynamic
{
	GENERATED_BODY()

public:

	UGameSettingValueDiscreteDynamic_Vector2D() { }

	void SetDefaultValue(const FVector2D& InValue)
	{	
		SetDefaultValueFromString(InValue.ToString());
	}

	FVector2D GetValue() const
	{
		FVector2D ValueVector;
		ValueVector.InitFromString(GetValueAsString());
		return ValueVector;
	}

	void SetValue(const FVector2D& InValue)
	{
		SetValueFromString(InValue.ToString());
	}
};

#undef MODULE_API
