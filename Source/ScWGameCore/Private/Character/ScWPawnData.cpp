// Scientific Ways

#include "Character/ScWPawnData.h"

#include "Character/ScWPawnExtensionComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWPawnData)

UScWPawnData::UScWPawnData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PawnClass = nullptr;
	InputConfig = nullptr;
	//DefaultCameraMode = nullptr;
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
