// Scientific Ways

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/DataAsset.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateBrush.h"

#include "SubtitleDisplayOptions.generated.h"

#define MODULE_API GAMESUBTITLES_API

UENUM()
enum class ESubtitleDisplayTextSize : uint8
{
	ExtraSmall,
	Small,
	Medium,
	Large,
	ExtraLarge,
	ESubtitleDisplayTextSize_MAX
};

UENUM()
enum class ESubtitleDisplayTextColor : uint8
{
	White,
	Yellow,
	ESubtitleDisplayTextColor_MAX
};

UENUM()
enum class ESubtitleDisplayTextBorder : uint8
{
	None,
	Outline,
	DropShadow,
	ESubtitleDisplayTextBorder_MAX
};

UENUM()
enum class ESubtitleDisplayBackgroundOpacity : uint8
{
	Clear,
	Low,
	Medium,
	High,
	Solid,
	ESubtitleDisplayBackgroundOpacity_MAX
};

/**
 * 
 */
UCLASS(MinimalAPI, BlueprintType)
class USubtitleDisplayOptions : public UDataAsset
{
	GENERATED_BODY()

public:
	USubtitleDisplayOptions() { }

public:
	UPROPERTY(Category = "Display Info", EditDefaultsOnly)
	FSlateFontInfo Font;

	UPROPERTY(Category = "Display Info", EditDefaultsOnly)
	int32 DisplayTextSizes[(int32)ESubtitleDisplayTextSize::ESubtitleDisplayTextSize_MAX];

	UPROPERTY(Category = "Display Info", EditDefaultsOnly)
	FLinearColor DisplayTextColors[(int32)ESubtitleDisplayTextColor::ESubtitleDisplayTextColor_MAX];

	UPROPERTY(Category = "Display Info", EditDefaultsOnly)
	float DisplayBorderSize[(int32)ESubtitleDisplayTextBorder::ESubtitleDisplayTextBorder_MAX];

	UPROPERTY(Category = "Display Info", EditDefaultsOnly)
	float DisplayBackgroundOpacity[(int32)ESubtitleDisplayBackgroundOpacity::ESubtitleDisplayBackgroundOpacity_MAX];

	UPROPERTY(Category = "Display Info", EditDefaultsOnly)
	FSlateBrush BackgroundBrush;
};

#undef MODULE_API
