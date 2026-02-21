// Scientific Ways

#include "Character/ScWPawnData.h"

#include "Character/ScWPawnDataFragment.h"
#include "Character/ScWPawnExtensionComponent.h"

#include "Components/GameFrameworkComponentManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWPawnData)

const FName UScWPawnData::NAME_PawnDataInitialized("PawnDataInitialized");
const FName UScWPawnData::NAME_PawnDataUninitialized("PawnDataUninitialized");

UScWPawnData::UScWPawnData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

APawn* UScWPawnData::SpawnPawnActorAndInitWithPawnData(
	const UObject* InWCO,
	const FTransform& InTransform,
	AActor* InOwner,
	APawn* InInstigator,
	ESpawnActorCollisionHandlingMethod InCollisionHandlingOverride,
	ESpawnActorScaleMethod InTransformScaleMethod
) const
{
	ensureReturn(PawnClass, nullptr);
	ensureReturn(InWCO, nullptr);

	UWorld* World = InWCO->GetWorld();
	ensureReturn(World, nullptr);

	APawn* OutPawn = World->SpawnActorDeferred<APawn>(PawnClass, InTransform, InOwner, InInstigator, InCollisionHandlingOverride, InTransformScaleMethod);
	ensureReturn(OutPawn, nullptr);

	UScWPawnExtensionComponent* PawnExtComponent = UScWPawnExtensionComponent::GetPawnExtensionComponent(OutPawn);
	ensureReturn(PawnExtComponent, nullptr);
	PawnExtComponent->SetPawnData(this);

	OutPawn->FinishSpawning(InTransform);
	return OutPawn;
}

const UScWPawnDataFragment* UScWPawnData::GetFragmentByClass(TSubclassOf<UScWPawnDataFragment> InTypeClass) const
{
	for (const UScWPawnDataFragment* SampleFragment : Fragments)
	{
		ensureContinue(SampleFragment);

		if (SampleFragment->IsA(InTypeClass))
		{
			return SampleFragment;
		}
	}
	return nullptr;
}

void UScWPawnData::InitializePawn(UScWPawnExtensionComponent* InPawnExtComponent) const
{
	ensureReturn(InPawnExtComponent);
	ensureReturn(InPawnExtComponent->GetScWAbilitySystemComponent());

	for (const UScWPawnDataFragment* SampleFragment : Fragments)
	{
		ensureContinue(SampleFragment);
		SampleFragment->BP_InitializePawn(InPawnExtComponent);
	}
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(InPawnExtComponent->GetOwner(), NAME_PawnDataInitialized);
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(InPawnExtComponent->GetScWAbilitySystemComponent()->GetOwner(), NAME_PawnDataInitialized);
}

void UScWPawnData::UninitializePawn(UScWPawnExtensionComponent* InPawnExtComponent) const
{
	ensureReturn(InPawnExtComponent);
	ensureReturn(InPawnExtComponent->GetScWAbilitySystemComponent());

	for (const UScWPawnDataFragment* SampleFragment : Fragments)
	{
		ensureContinue(SampleFragment);
		SampleFragment->BP_UninitializePawn(InPawnExtComponent);
	}
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(InPawnExtComponent->GetOwner(), NAME_PawnDataUninitialized);
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(InPawnExtComponent->GetScWAbilitySystemComponent()->GetOwner(), NAME_PawnDataUninitialized);
}
