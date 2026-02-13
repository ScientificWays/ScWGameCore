// Scientific Ways

#pragma once

#include "CoreMinimal.h"

#include "GameAnalytics.h"
#include "GameAnalyticsModule.h"

#include "ScWAnalyticsSourceComponent.generated.h"

#define MODULE_API SCWANALYTICS_API

class UObject;

/**
 *	Component that can be added to any actor to send analytics events to GameAnalytics. It is designed to be used as a source of analytics events, and can be used in conjunction with other components that send events to it.
 */
UCLASS(MinimalAPI, Blueprintable, BlueprintType)
class UScWAnalyticsSourceComponent : public UActorComponent
{
	GENERATED_BODY()

//~ Begin Initialize
protected:
	MODULE_API virtual void BeginPlay() override; // UActorComponent
	MODULE_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; // UActorComponent
//~ End Initialize

//~ Begin Identifiers
public:

	UPROPERTY(Category = "Identifiers", EditAnywhere, BlueprintReadWrite)
	FString DesignEventsId;

	UPROPERTY(Category = "Identifiers", EditAnywhere, BlueprintReadWrite)
	FString SourceName;
//~ End Identifiers

//~ Begin Events
public:

	UFUNCTION(Category = "Events", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Send Design Event"))
	MODULE_API void BP_SendDesignEvent(const FString& InEventName, const FGACustomFields InAdditionalFields = FGACustomFields()) const;
//~ End Events
};

#undef MODULE_API
