// Scientific Ways

#pragma once

#include "GameSettingDataSource.h"
#include "PropertyPathHelpers.h"

#define MODULE_API GAMESETTINGS_API

class ULocalPlayer;

//--------------------------------------
// FGameSettingDataSourceDynamic
//--------------------------------------

class FGameSettingDataSourceDynamic : public FGameSettingDataSource
{
public:
	MODULE_API FGameSettingDataSourceDynamic(const TArray<FString>& InDynamicPath);

	MODULE_API virtual bool Resolve(ULocalPlayer* InLocalPlayer) override;

	MODULE_API virtual FString GetValueAsString(ULocalPlayer* InLocalPlayer) const override;

	MODULE_API virtual void SetValue(ULocalPlayer* InLocalPlayer, const FString& Value) override;

	MODULE_API virtual FString ToString() const override;

private:
	FCachedPropertyPath DynamicPath;
};

#undef MODULE_API
