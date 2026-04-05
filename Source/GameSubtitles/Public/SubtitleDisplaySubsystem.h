// Scientific Ways

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "SubtitleDisplayOptions.h"

#include "SubtitleDisplaySubsystem.generated.h"

#define MODULE_API GAMESUBTITLES_API

class FSubsystemCollectionBase;
class ULocalPlayer;
class UObject;

USTRUCT(BlueprintType)
struct FSubtitleFormat
{
	GENERATED_BODY()

public:
	FSubtitleFormat()
		: SubtitleTextSize(ESubtitleDisplayTextSize::Medium)
		, SubtitleTextColor(ESubtitleDisplayTextColor::White)
		, SubtitleTextBorder(ESubtitleDisplayTextBorder::None)
		, SubtitleBackgroundOpacity(ESubtitleDisplayBackgroundOpacity::Medium)
	{
	}

public:
	UPROPERTY(Category = "Display Info", EditAnywhere)
	ESubtitleDisplayTextSize SubtitleTextSize;

	UPROPERTY(Category = "Display Info", EditAnywhere)
	ESubtitleDisplayTextColor SubtitleTextColor;

	UPROPERTY(Category = "Display Info", EditAnywhere)
	ESubtitleDisplayTextBorder SubtitleTextBorder;

	UPROPERTY(Category = "Display Info", EditAnywhere)
	ESubtitleDisplayBackgroundOpacity SubtitleBackgroundOpacity;
};

UCLASS(MinimalAPI, DisplayName = "Subtitle Display")
class USubtitleDisplaySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	DECLARE_EVENT_OneParam(USubtitleDisplaySubsystem, FDisplayFormatChangedEvent, const FSubtitleFormat& /*DisplayFormat*/);
	FDisplayFormatChangedEvent DisplayFormatChangedEvent;

public:
	static MODULE_API USubtitleDisplaySubsystem* Get(const ULocalPlayer* LocalPlayer);

public:
	MODULE_API USubtitleDisplaySubsystem();

	// Begin USubsystem
	MODULE_API virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	MODULE_API virtual void Deinitialize() override;
	// End USubsystem

	MODULE_API void SetSubtitleDisplayOptions(const FSubtitleFormat& InOptions);
	MODULE_API const FSubtitleFormat& GetSubtitleDisplayOptions() const;

private:
	UPROPERTY()
	FSubtitleFormat SubtitleFormat;
};

#undef MODULE_API
