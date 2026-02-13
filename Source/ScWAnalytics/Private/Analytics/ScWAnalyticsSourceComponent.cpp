// Scientific Ways

#include "Analytics/ScWAnalyticsSourceComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWAnalyticsSourceComponent)

UScWAnalyticsSourceComponent::ScWAnalyticsSourceComponent()
{
	DesignEventsId = TEXT("GenericEventId");
	SourceName = TEXT("GenericSource");
}

void UScWAnalyticsSourceComponent::BeginPlay()
{
	

	Super::BeginPlay();
}

void UScWAnalyticsSourceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	

	Super::EndPlay(EndPlayReason);
}

//~ Begin Events
void UScWAnalyticsSourceComponent::BP_SendDesignEvent_Implementation(const FString& InEventName, const FGACustomFields InAdditionalFields) const
{
	UGameAnalytics* GameAnalytics = FGameAnalyticsModule::Get().GetInstance();
	ensureReturn(GameAnalytics);

	auto CustomFields = FGACustomFields();
	CustomFields.Set(TEXT("SourceName"), SourceName);
	CustomFields.Set(TEXT("EventName"), InEventName);

	for (const auto& SampleFieldValue : InAdditionalFields.Values)
	{
		CustomFields.Values.Add(SampleFieldValue);
	}
	GameAnalytics->AddDesignEvent(EventsId, CustomFields);
}
//~ End Events
