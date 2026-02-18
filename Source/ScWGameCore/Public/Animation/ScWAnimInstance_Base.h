// Scientific Ways

#pragma once

#include "ScWGameCore.h"

#include "Animation/ScWTypes_Animation.h"

#include "ScWAnimInstance_Base.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, Abstract)
class UScWAnimInstance_Base : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UScWAnimInstance_Base();
	
//~ Begin Editor
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override; // UObject
#endif // WITH_EDITOR	
//~ End Editor
	
//~ Begin Initialize
protected:
	virtual void NativeInitializeAnimation() override; // UAnimInstance
	virtual void NativeUpdateAnimation(float InDeltaSeconds) override; // UAnimInstance

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override; // UObject
#endif // WITH_EDITOR
public:

	UFUNCTION()
	virtual void InitializeFromOwnerAbilitySystem(UAbilitySystemComponent* InASC);
//~ End Initialize

//~ Begin Owner
protected:

	UPROPERTY(Category = "Owner", BlueprintReadOnly)
	TObjectPtr<class ACharacter> OwnerCharacter;
//~ End Owner
	
//~ Begin Static
public:
	virtual void ResetToDefaultStaticAnimationData() {}
	void SetUseHolsterStaticAnimationData(const bool bInUseHolster, const float InBlendTime);
	void SetUseAlternativeBasePose(const bool bInUseAlternative, const float InBlendTime);
	void SetEnableIdleAnimation(const bool bInEnable);
	
	UFUNCTION(Category = "Static", BlueprintImplementableEvent, meta = (DisplayName = "OnCurrentStaticAnimationDataChanged"))
	void BP_OnCurrentStaticAnimationDataChanged();
	
	UFUNCTION(Category = "Static", BlueprintImplementableEvent, meta = (DisplayName = "OnDefaultStaticAnimationDataChanged"))
	void BP_OnDefaultStaticAnimationDataChanged();
	
	UFUNCTION(Category = "Static", BlueprintImplementableEvent, meta = (DisplayName = "OnEnableHolsterStaticAnimationDataChanged"))
	void BP_OnUseHolsterStaticAnimationDataChanged();
	
	UFUNCTION(Category = "Static", BlueprintImplementableEvent, meta = (DisplayName = "OnUseAlternativeBasePoseChanged"))
	void BP_OnUseAlternativeBasePoseChanged();
	
	UFUNCTION(Category = "Static", BlueprintImplementableEvent, meta = (DisplayName = "OnEnableIdleAnimationChanged"))
	void BP_OnEnableIdleAnimationChanged();
	
protected:

	UPROPERTY(Category = "Static", BlueprintReadOnly, EditAnywhere)
	bool bUseHolsterStaticAnimationData;
	
	UPROPERTY(Category = "Static", BlueprintReadOnly, EditAnywhere)
	float CurrentHolsterStaticAnimationDataBlendTime;

	UPROPERTY(Category = "Static", BlueprintReadOnly, EditAnywhere)
	bool bUseAlternativeBasePose;

	UPROPERTY(Category = "Static", BlueprintReadOnly, EditAnywhere)
	float CurrentAlternativeBasePoseBlendTime;

	UPROPERTY(Category = "Static", BlueprintReadOnly, EditAnywhere)
	bool bEnableIdleAnimation;
//~ End Static

//~ Begin Gameplay Tags
public:

	// Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are added or removed.
	// These should be used instead of manually querying for the gameplay tags.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Tags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
//~ End Gameplay Tags
};
