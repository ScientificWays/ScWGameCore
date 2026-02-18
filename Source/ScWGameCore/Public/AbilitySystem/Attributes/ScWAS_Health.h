// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWAS_Health.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Health Attributes"))
class UScWAS_Health : public UAttributeSet
{
	GENERATED_BODY()

public:

	UScWAS_Health();

//~ Begin Replication
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; // UObject
//~ End Replication

//~ Begin Change
protected:
	virtual void PreAttributeChange(const FGameplayAttribute& InAttribute, float& InOutNewValue) override; // UAttributeSet
	virtual void PostAttributeChange(const FGameplayAttribute& InAttribute, float InPrevValue, float InNewValue) override; // UAttributeSet
//~ End Change

//~ Begin Attributes
public:

	UPROPERTY(ReplicatedUsing = "OnRep_Health", BlueprintReadOnly)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ThisClass, Health)

	UPROPERTY(ReplicatedUsing = "OnRep_HealthMax", BlueprintReadOnly)
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(ThisClass, HealthMax)
//~ End Attributes

//~ Begin Replication
protected:

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_HealthMax(const FGameplayAttributeData& InPrevValue);
//~ End Replication
};
