// Scientific Ways

#include "Animation/ScWAnimInstance_Base.h"

#include "Character/ScWCharacter.h"
#include "AbilitySystem/AsyncTask_WaitForAbilitySystem.h"

#include "Misc/DataValidation.h"

UScWAnimInstance_Base::UScWAnimInstance_Base()
{
	bUseHolsterStaticAnimationData = false;

	CurrentHolsterStaticAnimationDataBlendTime = 0.1f;

	bUseAlternativeBasePose = false;

	CurrentAlternativeBasePoseBlendTime = 0.1f;

	bEnableIdleAnimation = true;
}

//~ Begin Editor
#if WITH_EDITOR
void UScWAnimInstance_Base::PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) // UObject
{
	Super::PostEditChangeProperty(InPropertyChangedEvent);

	if (InPropertyChangedEvent.Property)
	{
		const FName& PropertyName = InPropertyChangedEvent.Property->GetFName();

		if (PropertyName == FName(TEXT("DefaultStaticAnimationData")))
		{
			ResetToDefaultStaticAnimationData();
		}
	}
}
#endif // WITH_EDITOR
//~ End Editor

//~ Begin Initialize
void UScWAnimInstance_Base::NativeInitializeAnimation() // UAnimInstance
{
	Super::NativeInitializeAnimation();

	AActor* OwningActor = GetOwningActor();
	ensureReturn(OwningActor);

	UAsyncTask_WaitForAbilitySystem* WaitForASC = UAsyncTask_WaitForAbilitySystem::WaitForAbilitySystem(OwningActor);
	WaitForASC->OnFound.AddDynamic(this, &ThisClass::InitializeFromOwnerAbilitySystem);
}

void UScWAnimInstance_Base::NativeUpdateAnimation(float InDeltaSeconds)
{
	Super::NativeUpdateAnimation(InDeltaSeconds);

	/*const AScWCharacter* Character = Cast<AScWCharacter>(GetOwningActor());
	if (!Character)
	{
		return;
	}
	UScWCharacterMovementComponent* CharMoveComp = CastChecked<UScWCharacterMovementComponent>(Character->GetCharacterMovement());
	const FScWCharacterGroundInfo& GroundInfo = CharMoveComp->GetGroundInfo();
	GroundDistance = GroundInfo.GroundDistance;*/
}

void UScWAnimInstance_Base::InitializeFromOwnerAbilitySystem(UAbilitySystemComponent* InASC)
{
	ensureReturn(InASC);
	GameplayTagPropertyMap.Initialize(this, InASC);
}
//~ End Initialize

#if WITH_EDITOR
EDataValidationResult UScWAnimInstance_Base::IsDataValid(FDataValidationContext& Context) const
{
	Super::IsDataValid(Context);
	GameplayTagPropertyMap.IsDataValid(this, Context);
	return ((Context.GetNumErrors() > 0) ? EDataValidationResult::Invalid : EDataValidationResult::Valid);
}
#endif // WITH_EDITOR

//~ Begin Static
void UScWAnimInstance_Base::SetUseHolsterStaticAnimationData(const bool bInUseHolster, const float InBlendTime)
{
	bUseHolsterStaticAnimationData = bInUseHolster;
	CurrentHolsterStaticAnimationDataBlendTime = InBlendTime;

	BP_OnUseHolsterStaticAnimationDataChanged();
}

void UScWAnimInstance_Base::SetUseAlternativeBasePose(const bool bInUseAlternative, const float InBlendTime)
{
	bUseAlternativeBasePose = bInUseAlternative;
	CurrentAlternativeBasePoseBlendTime = InBlendTime;

	BP_OnUseAlternativeBasePoseChanged();
}

void UScWAnimInstance_Base::SetEnableIdleAnimation(const bool bInEnable)
{
	bEnableIdleAnimation = bInEnable;

	BP_OnEnableIdleAnimationChanged();
}
//~ End Static
