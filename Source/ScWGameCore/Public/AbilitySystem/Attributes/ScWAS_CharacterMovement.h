// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "ScWAS_CharacterMovement.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Character Movement Attributes"))
class UScWAS_CharacterMovement : public UAttributeSet
{
	GENERATED_BODY()

public:

	UScWAS_CharacterMovement();

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

	UPROPERTY(ReplicatedUsing = "OnRep_WalkSpeed", BlueprintReadOnly)
	FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(ThisClass, WalkSpeed)
		
	UPROPERTY(ReplicatedUsing = "OnRep_WalkSpeedMax", BlueprintReadOnly)
	FGameplayAttributeData WalkSpeedMax;
	ATTRIBUTE_ACCESSORS(ThisClass, WalkSpeedMax)

	UPROPERTY(ReplicatedUsing = "OnRep_WalkSpeedMulCrouched", BlueprintReadOnly)
	FGameplayAttributeData WalkSpeedMulCrouched;
	ATTRIBUTE_ACCESSORS(ThisClass, WalkSpeedMulCrouched)
		
	UPROPERTY(ReplicatedUsing = "OnRep_Acceleration", BlueprintReadOnly)
	FGameplayAttributeData Acceleration;
	ATTRIBUTE_ACCESSORS(ThisClass, Acceleration)

	UPROPERTY(ReplicatedUsing = "OnRep_BrakingDecelerationWalking", BlueprintReadOnly)
	FGameplayAttributeData BrakingDecelerationWalking;
	ATTRIBUTE_ACCESSORS(ThisClass, BrakingDecelerationWalking)

	UPROPERTY(ReplicatedUsing = "OnRep_GravityScale", BlueprintReadOnly)
	FGameplayAttributeData GravityScale;
	ATTRIBUTE_ACCESSORS(ThisClass, GravityScale)

	UPROPERTY(ReplicatedUsing = "OnRep_AirControl", BlueprintReadOnly)
	FGameplayAttributeData AirControl;
	ATTRIBUTE_ACCESSORS(ThisClass, AirControl)

	UPROPERTY(ReplicatedUsing = "OnRep_Mass", BlueprintReadOnly)
	FGameplayAttributeData Mass;
	ATTRIBUTE_ACCESSORS(ThisClass, Mass)

	UPROPERTY(ReplicatedUsing = "OnRep_RotationRateYaw", BlueprintReadOnly)
	FGameplayAttributeData RotationRateYaw;
	ATTRIBUTE_ACCESSORS(ThisClass, RotationRateYaw)
//~ End Attributes

//~ Begin Replication
protected:

	UFUNCTION()
	virtual void OnRep_WalkSpeed(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_WalkSpeedMax(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_WalkSpeedMulCrouched(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_Acceleration(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_BrakingDecelerationWalking(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_GravityScale(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_AirControl(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_Mass(const FGameplayAttributeData& InPrevValue);

	UFUNCTION()
	virtual void OnRep_RotationRateYaw(const FGameplayAttributeData& InPrevValue);
//~ End Replication
};
