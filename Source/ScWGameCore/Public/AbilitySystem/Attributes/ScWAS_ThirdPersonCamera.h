// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWAS_ThirdPersonCamera.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Third Person Camera Attributes"))
class UScWAS_ThirdPersonCamera : public UAttributeSet
{
	GENERATED_BODY()

public:

	UScWAS_ThirdPersonCamera();

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

	UPROPERTY(ReplicatedUsing = "OnRep_RotationPitch", BlueprintReadOnly)
	FGameplayAttributeData RotationPitch;
	ATTRIBUTE_ACCESSORS(ThisClass, RotationPitch)

	UPROPERTY(ReplicatedUsing = "OnRep_RotationYaw", BlueprintReadOnly)
	FGameplayAttributeData RotationYaw;
	ATTRIBUTE_ACCESSORS(ThisClass, RotationYaw)

	UPROPERTY(ReplicatedUsing = "OnRep_RotationRoll", BlueprintReadOnly)
	FGameplayAttributeData RotationRoll;
	ATTRIBUTE_ACCESSORS(ThisClass, RotationRoll)

	UPROPERTY(ReplicatedUsing = "OnRep_SpringArmLength", BlueprintReadOnly)
	FGameplayAttributeData SpringArmLength;
	ATTRIBUTE_ACCESSORS(ThisClass, SpringArmLength)

	UPROPERTY(ReplicatedUsing = "OnRep_FieldOfView", BlueprintReadOnly)
	FGameplayAttributeData FieldOfView;
	ATTRIBUTE_ACCESSORS(ThisClass, FieldOfView)
//~ End Attributes

//~ Begin Replication
protected:

	UFUNCTION()
	virtual void OnRep_RotationPitch(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_RotationYaw(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_RotationRoll(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_SpringArmLength(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_FieldOfView(const FGameplayAttributeData& InPrevValue);
//~ End Replication
};
