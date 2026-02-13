// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "AbilitySystem/ScWASC_InitInterface.h"

#include "ScWCharacterMovement.generated.h"

#define MODULE_API SCWGAMECORE_API

/**
 *
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Character Movement (Component)"))
class UScWCharacterMovement : public UCharacterMovementComponent, public IScWASC_InitInterface
{
	GENERATED_BODY()
	
public:	
	
	UScWCharacterMovement();
	
//~ Begin Initialize
public:
	virtual void BeginPlay() override; // UActorComponent
	virtual void InitFromASC(class UScWAbilitySystemComponent* InInitASC, AActor* InOwnerActor, AActor* InAvatarActor) override; // IScWASC_InitInterface
//~ End Initialize

//~ Begin Rotation
public:

	//UFUNCTION(Category = "Rotation", BlueprintCallable, meta = (DefaultToSelf = "InSource"))
	//bool HasPhysicsRotationBlockSource(UObject* InSource) const { return PhysicsRotationBlockSourceSet.Contains(InSource); }

	//UFUNCTION(Category = "Rotation", BlueprintCallable, meta = (DefaultToSelf = "InSource"))
	//void AddPhysicsRotationBlockSource(UObject* InSource) { PhysicsRotationBlockSourceSet.Add(InSource); }

	//UFUNCTION(Category = "Rotation", BlueprintCallable, meta = (DefaultToSelf = "InSource"))
	//void RemovePhysicsRotationBlockSource(UObject* InSource) { PhysicsRotationBlockSourceSet.Remove(InSource); }

protected:
	virtual void ApplyRootMotionToVelocity(float InDeltaTime) override; // UCharacterMovementComponent
	virtual void PhysicsRotation(float InDeltaTime) override; // UCharacterMovementComponent

	virtual FRotator ComputeOrientToMovementRotation(const FRotator& InCurrentRotation, float InDeltaTime, FRotator& InDeltaRotation) const;

	//UPROPERTY(Transient)
	//TSet<TObjectPtr<UObject>> PhysicsRotationBlockSourceSet;

	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bOrientRotationToMovement"))
	bool bOrientRotationToRootMotionMovement;
	
	UPROPERTY(Transient)
	FVector LastRootMotionVelocity;
//~ End Rotation

//~ Begin Attributes
public:

protected:
	void OnMaxWalkSpeedAttributeChanged(const FOnAttributeChangeData& InData);
	void OnMaxWalkSpeedCrouchedAttributeChanged(const FOnAttributeChangeData& InData);
	void OnMaxAccelerationAttributeChanged(const FOnAttributeChangeData& InData);
	void OnBrakingDecelerationWalkingAttributeChanged(const FOnAttributeChangeData& InData);
	void OnGravityScaleAttributeChanged(const FOnAttributeChangeData& InData);
	void OnAirControlAttributeChanged(const FOnAttributeChangeData& InData);
	void OnMassAttributeChanged(const FOnAttributeChangeData& InData);

	FDelegateHandle MaxWalkSpeedChangedDelegateHandle;
	FDelegateHandle MaxWalkSpeedCrouchedChangedDelegateHandle;
	FDelegateHandle MaxAccelerationChangedDelegateHandle;
	FDelegateHandle BrakingDecelerationWalkingChangedDelegateHandle;
	FDelegateHandle GravityScaleChangedDelegateHandle;
	FDelegateHandle AirControlChangedDelegateHandle;
	FDelegateHandle MassChangedDelegateHandle;
//~ End Attributes

//~ Begin Tags
protected:
	void OnMovementModeTagNumChanged(const FGameplayTag InCallbackTag, int32 InNewCount);
	void UpdateCharacterMovementModeFromTags();
//~ End Tags

//~ Begin Damage
protected:

	UFUNCTION()
	void HandleDamageApplied(float InDamage, const struct FReceivedDamageData& InData);

	UFUNCTION()
	void HandleDied();
//~ End Damage
};

#undef MODULE_API
